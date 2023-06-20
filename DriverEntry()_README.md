# DriverEntry(`#1`,`#2`) #

This file consists of a very basic, and working understanding of the code snippe for the DriverEntry() function. Main take aways to be taken from this README are:

* Overview
* Purpose of this function?
* Implementation

NOTE: This file only contains a basic overview, and the whole contect of code is given in the code base, please have a look there. 


## Overview ##

This function, which is the entry point for a Windows Driver Framework (WDF) driver is an essential part of the driver implementation and usage. `DriverEntry()` is called directly by the OS.

## Purpose of this function? ##

This function has three main puposes regarding the driver initialization:

* Initializes the WDF driver configuration.
* Creates the WDF driver object.
* Returns the status of the driver initialization.

The `DriverEntry()` function must be implemented correctly in order for the driver to function properly.

## Implementation ##

Code snippet:

```
_Use_decl_annotations_
extern "C" NTSTATUS DriverEntry(
    PDRIVER_OBJECT  pDriverObject,
    PUNICODE_STRING pRegistryPath
)
{
    WDF_DRIVER_CONFIG Config;
    NTSTATUS Status;

    WDF_OBJECT_ATTRIBUTES Attributes;
    WDF_OBJECT_ATTRIBUTES_INIT(&Attributes);

    WDF_DRIVER_CONFIG_INIT(&Config,
        IddSampleDeviceAdd
    );

    Status = WdfDriverCreate(pDriverObject, pRegistryPath, &Attributes, &Config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    return Status;
}
```

The parameters:

* pDriverObject: A pointer to the driver object
* pRegistryPath: A pointer to the driver's registry path

Here are some general parts of the implmentation that are important:

* `_Use_decl_annotations_` keyword: tells the compiler to use the annotations that are defined in the wdf.h header file
* `WDF_DRIVER_CONFIG` structure: it is used to configure a WDF driver.
* `WDF_OBJECT_ATTRIBUTES` structure: it is used to specify the attributes of a WDF object.
* `WdfDriverCreate()` function: creates the WDF driver object.
* `WDF_DRIVER_CONFIG_INIT()` macro: initializes the WDF_DRIVER_CONFIG structure.
* `NT_SUCCESS()` macro returns TRUE if the status code is successful, and FALSE otherwise.