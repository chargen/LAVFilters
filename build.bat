@ECHO OFF

call "%VS120COMNTOOLS%vsvars32.bat"

sh build_ffmpeg.sh x86 || EXIT /B 1
cd libde265
cmd /c build.bat x86
cd ..
pexports libde265\libde265\libde265.dll > libde265\libde265\libde265.def
dlltool -d libde265\libde265\libde265.def -l libde265\libde265\libde265.a
copy /y libde265\bin_x86\libde265.dll bin_Win32
copy /y libde265\bin_x86\libde265.dll bin_Win32d
MSBuild.exe LAVFilters.sln /nologo /m /t:Rebuild /property:Configuration=Release;Platform=Win32
IF %ERRORLEVEL% NEQ 0 EXIT /B 1

sh build_ffmpeg.sh x64 || EXIT /B 1
cd libde265
cmd /c build.bat x64
cd ..
pexports libde265\libde265\libde265.dll > libde265\libde265\libde265.def
dlltool -d libde265\libde265\libde265.def -l libde265\libde265\libde265.a
copy /y libde265\bin_x64\libde265.dll bin_x64
copy /y libde265\bin_x64\libde265.dll bin_x64d
MSBuild.exe LAVFilters.sln /nologo /m /t:Rebuild /property:Configuration=Release;Platform=x64
IF %ERRORLEVEL% NEQ 0 EXIT /B 1

PAUSE
