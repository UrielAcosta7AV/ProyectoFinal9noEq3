@echo off
del /s /q *.exe
del /s /q *.suo
del /s /q *.pdb
del /s /q *.sdf
del /s /q *.obj
del /s /q *.log
del /s /q *.idb
del /s /q *.tlog
del /s /q *.lastbuildstate
rmdir /s /q Debug
rmdir /s /q Release
pause