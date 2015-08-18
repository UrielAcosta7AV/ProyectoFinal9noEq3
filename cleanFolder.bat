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
del /s /q *.apk
del /s /q *.o
del /s /q *.db
for /f "usebackq delims=" %%d in (`"dir /ad/b/s | sort /R"`) do rd "%%d"
rmdir /s /q Debug
rmdir /s /q Release
rmdir /s /q generated
rmdir /s /q intermediates
rmdir /s /q outputs
rmdir /s /q tmp
rmdir /s /q androidTest
rmdir /s /q obj
rmdir /s /q libs
pause