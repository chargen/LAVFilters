@echo off

set MSYS_FILENAME=MSYS_MinGW-w64_GCC_493_x86-x64.7z
if not exist "C:\MSYS" (
    echo Fetching MSYS/MinGW...
    PowerShell Invoke-WebRequest -Uri http://xhmikosr.1f0.de/tools/msys/%MSYS_FILENAME% -OutFile "C:\Users\vagrant\%MSYS_FILENAME%"
    C:\vagrant\scripts\vagrant\7za.exe x -y -oC:\ "C:\Users\vagrant\%MSYS_FILENAME%" > NUL
    SETX PATH "%PATH%;C:\MSYS\bin;C:\MSYS\mingw\bin" > NUL
    SET "PATH=%PATH%;C:\MSYS\bin;C:\MSYS\mingw\bin" > NUL
) else (
    echo MSYS/MinGW already installed
)
