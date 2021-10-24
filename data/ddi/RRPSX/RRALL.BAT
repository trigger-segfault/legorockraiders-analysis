@echo off
attrib cpe\rrpsxd.cpe -r
psymake /b /f rrgods.mak
psymake /b /f rrpsx.mak
attrib cpe\rrpsxd.cpe +r
attrib cpe\rrpsxd.exe -r
cpe2x /CE cpe\rrpsxd.cpe
attrib cpe\rrpsxd.exe +r
attrib cd_root\xlego.exe -r
copy cpe\rrpsxd.exe cd_root\xlego.exe
attrib cd_root\xlego.exe +r
if "%1"=="r" call runrr.bat
if "%1"=="R" call runrr.bat

