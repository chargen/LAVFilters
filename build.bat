@ECHO OFF

call "%VS120COMNTOOLS%vsvars32.bat"

cd libde265
cmd /c build.bat x86
cd ..
sh build_ffmpeg.sh x86
copy /y libde265\bin_x86\libde265.dll bin_Win32
copy /y libde265\bin_x86\libde265.dll bin_Win32d
devenv LAVFilters.sln /Rebuild "Release|Win32"

cd libde265
cmd /c build.bat x64
cd ..
sh build_ffmpeg.sh x64
copy /y libde265\bin_x64\libde265.dll bin_x64
copy /y libde265\bin_x64\libde265.dll bin_x64d
devenv LAVFilters.sln /Rebuild "Release|x64"

PAUSE
