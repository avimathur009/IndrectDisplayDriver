# CONFIGURATION STEPS FOR IDD SAMPLE APP #

This file consists of configuration steps for running IddSampleApp:

* External Installation: SDK & WDK
* Property Configuration for IddSampleApp

NOTE: This README only gives the configuration steps and does not tell much about IddSampleApp. You can see about it more in the codebase here:
%PATH TO REPO%\IndrectDisplayDriver\IddSampleApp\IddSampleDriver.sln


## External Installation: SDK & WDK ##

The main External installations required for running the IddSampleApp are Windows SDK (Software Development Kit) and WDK (Windows Driver Kit):

* Windows SDK: We need to use Windows SDK (10.0.22621) for Windows 11 which provides the latest headers, libraries, metadata, and tools for building Windows applications
* WDK: We need to use Windows Driver Kit (WDK) 11 which helps build, test, and deploy the drivers. The WDK helps in integrating driver development environment to integrate with Visual Studios.

Installation Links for Windows SDK & WDK:

* Windows SDK: https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/
* WDK: https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk

Along with these installations, it is necessary to install some "Individual Components" using Visual Studios Installer. Here's the list of those components required to be installed:

* MSVC v143 - VS 2022 C++ ARM build tools (Latest) 
* MSVC v143 - VS 2022 C++ x64/x86 Spectre-mitigated libs (Latest)
* Windows Driver Kit (This is optional as WDK may already been installed using external installation)


## Property Configuration for IddSampleApp.sln ##

Now as the external installtions are completed, there are several changes in the Property Configurations that needs to be set. Here are the steps to have the correct Property Configuration:

* Go on the following path in the current repo: $cd %PATH TO REPO%\IndrectDisplayDriver\IddSampleDriver.sln --- OR --- Double click on the 'IddSampleDriver.sln' solution   
* Now we have two .sln files, out of which we focus on 'IddSampleApp'
* Right click on the 'IddSampleApp', and select 'Properties'

Follow this to select on the correct Property settings: 
* Property -> Configuration Properties -> General -> Configuration Type : Choose 'Application (.exe)'
* Property -> Configuration Properties -> General -> Windows SDK Version : Choose '10.0 (latest installed version)'
* Property -> Configuration Properties -> General -> Platform Toolset : Choose 'WindowsUserModeDriver10.0'

Press "Apply" and click "OK" to apply these changes for this .sln file