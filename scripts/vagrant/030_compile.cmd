@echo off
setlocal

cd LAVFilters
if exist "bin_Win32" (
    rmdir /s /q bin_Win32
)
if exist "bin_Win32d" (
    rmdir /s /q bin_Win32d
)
if exist "bin_x64" (
    rmdir /s /q bin_x64
)
if exist "bin_x64d" (
    rmdir /s /q bin_x64d
)

echo Compiling LAVFilters...
rem Don't wait for keyboard input after compilation
sed -i 's/^PAUSE$//g' build.bat
call build.bat
