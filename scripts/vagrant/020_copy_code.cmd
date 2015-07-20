@echo off
setlocal

if exist LAVFilters (
    rmdir /q /s LAVFilters
    IF %ERRORLEVEL% NEQ 0 EXIT /B 1
)

echo Copy contents of git repository...
robocopy c:\vagrant\ LAVFilters /e /xf *.iso libde265-*.exe *.mkv /np /nfl /ndl /njh /ns /nc /mt
IF %ERRORLEVEL% GEQ 8 EXIT /B 1
