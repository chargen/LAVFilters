@echo off
setlocal

set IS_FILENAME=isetup-5.5.6-unicode.exe

if not exist "C:\Program Files (x86)\Inno Setup 5\ISCC.exe" (
    echo Fetching Inno Setup...
    PowerShell Invoke-WebRequest -Uri http://files.jrsoftware.org/is/5/%IS_FILENAME% -OutFile "C:\Users\vagrant\%IS_FILENAME%"
    echo Installing Inno Setup...
    "C:\Users\vagrant\%IS_FILENAME%" /VERYSILENT /SUPPRESSMSGBOXES /NORESTART
) else (
    echo Inno Setup already installed
)
