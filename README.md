# Tracing
Tracing is acheived with the [Inflight Trace Recorder](https://learn.microsoft.com/en-us/windows-hardware/drivers/devtest/using-wpp-recorder).
Tracing can be added to Driver.cpp using `TraceLog`. Example:
```cpp
TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER , "WdfDriverCreate failed, %!STATUS!", ntStatus);
```

Note that the file which includes `TraceEvents` must have the appropriate flags set in the `.vcxproj`:
```xml
<ClCompile Include="Driver.cpp">
<WppEnabled>true</WppEnabled>
<WppRecorderEnabled>true</WppRecorderEnabled>
<WppPreprocessorDefinitions>WPP_MACRO_USE_KM_VERSION_FOR_UM=1</WppPreprocessorDefinitions>
</ClCompile>
```

In order to view the logs, use the TraceView tool included in the windows SDK. For example it might be located here:
```
C:\wdk\Program Files\Windows Kits\10\Tools\10.0.22621.0\x64\traceview.exe
```

Once TraceView is running:

1. File -> Create New Log Session
2. Select "PDB (Debug Information) File" and click "...".
3. (Must build the solution first). Select `IddSampleDriver.pdb` file (located in `x64/Debug/IddSampleDriver.pdb`)
4. Click OK.
5. click Next >
6. Click Finish

Now the drivers log events will appear in the window.