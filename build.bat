@ECHO OFF

call "%VS120COMNTOOLS%vsvars32.bat"

cd libde265
cmd /c build.bat x86
cd ..
pexports libde265\libde265\libde265.dll > libde265\libde265\libde265.def
dlltool -d libde265\libde265\libde265.def -l libde265\libde265\libde265.a
sh build_ffmpeg.sh x86
copy /y libde265\bin_x86\libde265.dll bin_Win32
copy /y libde265\bin_x86\libde265.dll bin_Win32d
devenv LAVFilters.sln /Rebuild "Release|Win32"

cd libde265
cmd /c build.bat x64
cd ..
pexports libde265\libde265\libde265.dll > libde265\libde265\libde265.def
dlltool -d libde265\libde265\libde265.def -l libde265\libde265\libde265.a
sh build_ffmpeg.sh x64
copy /y libde265\bin_x64\libde265.dll bin_x64
copy /y libde265\bin_x64\libde265.dll bin_x64d
devenv LAVFilters.sln /Rebuild "Release|x64"

PAUSE
