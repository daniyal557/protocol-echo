param([string]$Compiler = "", [string]$RaylibRoot = "C:\raylib")
$ErrorActionPreference = 'Stop'
Set-Location -LiteralPath $PSScriptRoot
if (!$Compiler) {
    $candidates = @('C:\mingw64ucrt\mingw64\bin\g++.exe', 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe', 'C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe')
    $Compiler = $candidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
    if (!$Compiler) { $Compiler = (Get-Command g++.exe -ErrorAction Stop).Source }
}
$env:PATH = (Split-Path -Parent $Compiler) + ';' + $env:PATH
New-Item -ItemType Directory -Path 'bin' -Force | Out-Null
if (!(Test-Path -LiteralPath "$RaylibRoot\include\raylib.h")) { throw "raylib.h not found under $RaylibRoot/include. Set -RaylibRoot to your installation." }
$sources = @(Get-ChildItem -LiteralPath . -Filter '*.cpp' | ForEach-Object { $_.FullName })
& $Compiler -std=c++17 -Wall -Wextra -I "$RaylibRoot/include" @sources -L "$RaylibRoot/lib" -o bin/ProtocolEcho.exe -lraylib -lopengl32 -lgdi32 -lwinmm
if ($LASTEXITCODE -ne 0) { throw "Compilation failed (exit $LASTEXITCODE)." }
Write-Host 'Build complete: bin/ProtocolEcho.exe'
