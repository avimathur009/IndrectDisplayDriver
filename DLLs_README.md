# dynamic-link library - DLL #

This file consists of a very basic, and working understanding of the dynamic-link library (DLL) for this project. These are the major and high-level points to look out for in this README.

* What is DLL?
* An overview of why we need it in this project with device drivers.
* Use case in the project. How is it used?

NOTE: This README only gives a working understanding of DLL for this project, however if you are curious about DLL you may look it up here:
https://learn.microsoft.com/en-us/troubleshoot/windows-client/deployment/dynamic-link-library


## What is DLL? ##

Dynamic-link library is a library that contains code and data that can be used by "more than one program at the same time":

* DLLs are loaded by the operating system when they are needed, and they are unloaded when they are no longer needed.
* Allows for efficient memory usage and code reuse.

Example:
DLLs are commonly used to implement shared functionality in Windows applications. 
A DLL might contain code for handling common dialog boxes, such as the Open dialog box or the Print dialog box. This code can be shared by multiple applications, which saves the need to re-implement the code in each application.


## An overview of why we need it in this project with device drivers ##

DLLs are used to implement device drivers in Windows: 

* Device drivers are software that allows applications to communicate with hardware devices.
* DLLs can be used to implement the code for a device driver, which can then be shared by multiple applications.

## Use case in the project. How is it used? ##

Code snippet:

```
extern "C" BOOL WINAPI DllMain(
    _In_ HINSTANCE hInstance,
    _In_ UINT dwReason,
    _In_opt_ LPVOID lpReserved)
{
    // Mark the parameters as unused.
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(lpReserved);
    UNREFERENCED_PARAMETER(dwReason);

    // Return TRUE to indicate that the DLL was loaded or unloaded successfully.
    return TRUE;
}
```

Here the main parts we need to take out of this: 

* It is a preprocessor predicate: This means that this peice of code will be implemented before the code space it is written is compiled.
* `DllMain()` function: it is the entry point of dll library in the code space where this snippet is written 
* `WINAPI` keyword: tells the compiler that the DllMain() function is a Windows API function, and that the function will be visible to other applications that use the DLL.
* `extern "C"` keyword: tells the compiler that this code snippet needs to be compiled in C language as the OS understands this implementation in C only.
* `BOOL` return type: this signifies that this function returns TRUE when OS is successfully be able to get all the DLLs required and FALSE if not 

