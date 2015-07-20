@echo off

rem Disable search indexer
sc config wsearch start= disabled
net stop wsearch || set errorlevel = 0
