#include <iostream>
#include <vector>

#include <windows.h>
#include <swdevice.h>
#include <conio.h>
#include <wrl.h>
#include <initguid.h>
#include <Devpropdef.h>

// Defines a GUID to uniquely identify the unified property for display configuration.
// See: https://learn.microsoft.com/en-us/windows-hardware/drivers/wdf/accessing-the-unified-device-property-model
// This GUID should match the same one used to query the property in the driver code.
// TODO: This GUID was pulled from sample code. Generate a new unique one.
DEFINE_DEVPROPKEY (DisplayConfigurationProperty, 0xde5c254e, 0xab1c, 0xeffd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8,0x50,0xe0,2);
// Structure which holds data to be transmitted to the driver. The driver code should have an identical structure.
struct DriverProperties {
    DriverProperties(int n) { num_displays = n; }
    int num_displays;
};

VOID WINAPI
CreationCallback(
    _In_ HSWDEVICE hSwDevice,
    _In_ HRESULT hrCreateResult,
    _In_opt_ PVOID pContext,
    _In_opt_ PCWSTR pszDeviceInstanceId
    )
{
    HANDLE hEvent = *(HANDLE*) pContext;

    SetEvent(hEvent);
    UNREFERENCED_PARAMETER(hSwDevice);
    UNREFERENCED_PARAMETER(hrCreateResult);
    UNREFERENCED_PARAMETER(pszDeviceInstanceId);
}

int __cdecl main(int argc, wchar_t *argv[])
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    HSWDEVICE hSwDevice;
    SW_DEVICE_CREATE_INFO createInfo = { 0 };
    PCWSTR description = L"Idd Sample Driver";

    // These match the Pnp id's in the inf file so OS will load the driver when the device is created    
    PCWSTR instanceId = L"IddSampleDriver";
    PCWSTR hardwareIds = L"IddSampleDriver\0\0";
    PCWSTR compatibleIds = L"IddSampleDriver\0\0";

    createInfo.cbSize = sizeof(createInfo);
    createInfo.pszzCompatibleIds = compatibleIds;
    createInfo.pszInstanceId = instanceId;
    createInfo.pszzHardwareIds = hardwareIds;
    createInfo.pszDeviceDescription = description;

    createInfo.CapabilityFlags = SWDeviceCapabilitiesRemovable |
                                 SWDeviceCapabilitiesSilentInstall |
                                 SWDeviceCapabilitiesDriverRequired;

  
  // Set configuration properties to send to the driver.
  DriverProperties p(2);
  DEVPROPERTY properties[1];
  DEVPROPERTY& property = properties[0];
  property.Type = DEVPROP_TYPE_BINARY;
  property.CompKey.Store = DEVPROP_STORE_SYSTEM;
  property.CompKey.Key = DisplayConfigurationProperty;
  property.CompKey.LocaleName = NULL;
  property.BufferSize = sizeof(DriverProperties);
  property.Buffer = &p;

  // Create the device
  HRESULT hr =
      SwDeviceCreate(L"IddSampleDriver", L"HTREE\\ROOT\\0", &createInfo, 1,
                     properties, CreationCallback, &hEvent, &hSwDevice);
    if (FAILED(hr))
    {
        printf("SwDeviceCreate failed with 0x%lx\n", hr);
        return 1;
    }

    // Wait for callback to signal that the device has been created
    printf("Waiting for device to be created....\n");
    DWORD waitResult = WaitForSingleObject(hEvent, 10*1000);
    if (waitResult != WAIT_OBJECT_0)
    {
        printf("Wait for device creation failed\n");
        return 1;
    }
    printf("Device created\n\n");
    
    // Now wait for user to indicate the device should be stopped
    printf("Press 'x' to exit and destory the software device\n");
    bool bExit = false;
    do
    {
        // Wait for key press
        int key = _getch();

        if (key == 'x' || key == 'X')
        {
            bExit = true;
        }
    }while (!bExit);
    
    // Stop the device, this will cause the sample to be unloaded
    SwDeviceClose(hSwDevice);

    return 0;
}