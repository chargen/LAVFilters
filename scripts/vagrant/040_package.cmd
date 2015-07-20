@echo off
setlocal

cd LAVFilters
if exist libde265-*.exe (
    del /q libde265-*.exe > NUL
)

if exist "C:\vagrant\scripts\vagrant\sign_files.cmd" (
    call "C:\vagrant\scripts\vagrant\sign_files.cmd" "C:\Users\vagrant\LAVFilters\bin_Win32"
    call "C:\vagrant\scripts\vagrant\sign_files.cmd" "C:\Users\vagrant\LAVFilters\bin_x64"
)

"C:\Program Files (x86)\Inno Setup 5\ISCC.exe" LAVFilters.iss

set TODAY=
for /f "skip=1" %%d in ('wmic os get localdatetime') do if not defined TODAY set TODAY=%%d
if not exist "C:\vagrant\build_result\%TODAY:~0,8%-%TODAY:~8,6%" (
    mkdir C:\vagrant\build_result\%TODAY:~0,8%-%TODAY:~8,6%
)
copy /y libde265-*.exe C:\vagrant\build_result\%TODAY:~0,8%-%TODAY:~8,6% >NUL
if exist "C:\vagrant\scripts\vagrant\sign_files.cmd" (
    call "C:\vagrant\scripts\vagrant\sign_files.cmd" "C:\vagrant\build_result\%TODAY:~0,8%-%TODAY:~8,6%"
)

echo Done, installer copied to "build_result\%TODAY:~0,8%-%TODAY:~8,6%"
