@echo off
cd /d "%~dp0"
if not exist "bin\ProtocolEcho.exe" (
    echo Build the game first using build.ps1 or Code::Blocks.
    pause
    exit /b 1
)
set "PATH=C:\mingw64ucrt\mingw64\bin;C:\raylib\lib;%PATH%"
"bin\ProtocolEcho.exe"
