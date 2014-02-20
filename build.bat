@ECHO OFF

call "%VS120COMNTOOLS%vsvars32.bat"

sh build_ffmpeg.sh x86 || EXIT /B 1
cd libde265
cmd /c build.bat x86
cd ..
copy /y libde265\bin_x86\libde265.dll bin_Win32
copy /y libde265\bin_x86\lib\libde265.lib bin_Win32\lib
copy /y libde265\bin_x86\libde265.dll bin_Win32d
copy /y libde265\bin_x86\lib\libde265.lib bin_Win32d\lib
copy /y libde265\extra\libde265\de265-version.h libde265\libde265
MSBuild.exe LAVFilters.sln /nologo /m /t:Rebuild /property:Configuration=Release;Platform=Win32

sh build_ffmpeg.sh x64 || EXIT /B 1
cd libde265
cmd /c build.bat x64
cd ..
copy /y libde265\bin_x64\libde265.dll bin_x64
copy /y libde265\bin_x64\lib\libde265.lib bin_x64\lib
copy /y libde265\bin_x64\libde265.dll bin_x64d
copy /y libde265\bin_x64\lib\libde265.lib bin_x64d\lib
copy /y libde265\extra\libde265\de265-version.h libde265\libde265
MSBuild.exe LAVFilters.sln /nologo /m /t:Rebuild /property:Configuration=Release;Platform=x64
IF %ERRORLEVEL% NEQ 0 EXIT /B 1

PAUSE
