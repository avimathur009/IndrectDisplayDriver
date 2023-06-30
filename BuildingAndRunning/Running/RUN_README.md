# STEPS FOR RUNNING IDD APP AND DRIVER #

This file consists of steps for running IddSampleApp & IddSampleDriver:

* Basic steps to follow
* Steps for installing IddSampleDriver
* Steps for running 'IddSampleApp.exe'


## Basic steps to follow ##

Here is the basic overview of what to do, to run the 'IddSampleApp':

* We may only achieve this if all the steps in 'Configuration' and 'BuildingAndRunning\Building' are followed properly and no errors are found.
* Then we need to install the Idd Driver which is given by a .inf file 
* Once the first two steps are done, we need to run the 'IddSampleApp.exe'


## Steps for installing IddSampleDriver ##

First we need to make sure that all the steps given in 'Configuration' and 'BuildingAndRunning\Building' are followed properly. 
Once they are done: 

* First we need to go to the project directory: %PATH TO REPO%\IndrectDisplayDriver\x64\Debug
* Then we need to locate the .inf file called 'IddSampleDriver.inf' in the given directory
* Select and right - click the .inf file, and click 'Install'

This will install the sample driver that was build earlier in the 'IddSampleDriver' file (specifically 'Driver.cpp')


## Steps for running 'IddSampleApp.exe' ##

First we need to make sure that .inf file is successfully installed, otherwise the 'IddSampleApp.exe' will not work
Once they are done: 

* First we need to go to the project directory: %PATH TO REPO%\IndrectDisplayDriver\x64\Debug
* Then we need to locate the .exe file called 'IddSampleApp.exe' in the given directory
* Select and right - click the .exe file
* IMPORTANT: Select the option 'Run as administrator' and the 'IddSampleApp.exe' will hence run.

NOTE: 'Run as administrator' is the MOST IMPORTANT part of this process as this App will not run otherwise. 
REASON: 'IddSampleApp' file in the 'IddSampleDriver.sln' has a method called 'SwDeviceCreate()' which requires the administrator controll to be run, and otherwise the App will not run
