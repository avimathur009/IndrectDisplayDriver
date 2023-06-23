#include <iostream>
#include <vector>

#include <windows.h>
#include <swdevice.h>
#include <conio.h>
#include <wrl.h>

//HSWDEVICE is a typedef for a 'handle' data-type: special type of pointer that is used to interact with Software device in the Windows operating system
//HRESULT is a data type that represents the completion status of a function: 32 bit value (devided into 3 parts)
//PVOID is a pointer to a generic type: typedef for the void * type (used when we don't want to change function, when not sure of the data type to pass)
//PCWSTR is a type that represents a pointer to a constant wide character string: stored using 16-bit characters
//_In_ : Passed by Value and Value can't be changes by function
//_In_opt_ : Passed by Value and Value may also be Null

VOID WINAPI
CreationCallback(
    _In_ HSWDEVICE hSwDevice,
    _In_ HRESULT hrCreateResult,
    _In_opt_ PVOID pContext,
    _In_opt_ PCWSTR pszDeviceInstanceId
    )
{
    //getting the event handle from context pointer by derefrencing
    //event handle for? the event handle for the software device that was created (IDD??)
    HANDLE hEvent = *(HANDLE*) pContext; 

    SetEvent(hEvent);

    //Indicating unused parameters
    UNREFERENCED_PARAMETER(hSwDevice);
    UNREFERENCED_PARAMETER(hrCreateResult);
    UNREFERENCED_PARAMETER(pszDeviceInstanceId);
}
//Using the standard calling convention: __cdecl (Is explicit specification necissary?)
int __cdecl main(int argc, wchar_t *argv[])
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    //creates a handle to an event object (See 4 parameters) 
    HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    //HSWDEVICE type is a handle to a software device object (used to represent hardware devices in the Win os)
    HSWDEVICE hSwDevice;

    //used to provide information about a software device object when it is created (Version, DeviceObjectName, DeviceObjectDescription, etc.)
    SW_DEVICE_CREATE_INFO createInfo = { 0 };

    //PCWSTR type is used to represent strings that are used by Windows APIs (win OS requires arguments to be passed as these types)
    PCWSTR description = L"Idd Sample Driver";

    // These match the Pnp id's in the inf file so OS will load the driver when the device is created    
    // SEE "IddSampleDriver.inf" file, line #20 (it is hard-coded for now, but need to edit that)
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

    // Create the device
    HRESULT hr = SwDeviceCreate(L"IddSampleDriver",
                                L"HTREE\\ROOT\\0",
                                &createInfo,
                                0,
                                nullptr,
                                CreationCallback,
                                &hEvent,
                                &hSwDevice);
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