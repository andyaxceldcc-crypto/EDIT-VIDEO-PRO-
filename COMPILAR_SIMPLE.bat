@echo off
setlocal enabledelayedexpansion
cd /d "%~dp0"

cls
echo.
echo FILMORA EDITOR PRO - COMPILACION
echo.
echo Buscando Qt...

REM Buscar Qt
set "QT_FOUND=0"
for /d %%Q in (C:\Qt\6.*) do (
    if exist "%%Q\bin\qmake.exe" (
        set "QT_PATH=%%Q\bin"
        set "QT_FOUND=1"
        echo Qt encontrado en: %%Q
        goto found_qt
    )
)

:found_qt
if %QT_FOUND% equ 0 (
    echo.
    echo Qt no encontrado. Descargando...
    powershell -Command "Start-Process 'https://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe'"
    echo Completa la instalacion manualmente
    pause
    exit /b 1
)

set "PATH=!QT_PATH!;!PATH!"

echo Compilando Filmora Editor Pro...
echo.

if exist "build" rmdir /s /q build
mkdir build
cd build

qmake ..\FilmoraEditor.pro -spec win32-msvc CONFIG+=release

if errorlevel 1 (
    echo ERROR: qmake fallo
    cd ..
    pause
    exit /b 1
)

echo.
echo Compilando con nmake...
nmake /NOLOGO

if errorlevel 1 (
    echo ERROR: Compilacion fallo
    cd ..
    pause
    exit /b 1
)

cd ..

if exist "build\release\FilmoraEditor.exe" (
    echo.
    echo ========================================
    echo EXITO - Compilacion completada
    echo ========================================
    echo.
    echo Ejecutable: build\release\FilmoraEditor.exe
    echo.
    echo Iniciando aplicacion...
    start "" "build\release\FilmoraEditor.exe"
) else (
    echo ERROR: El ejecutable no se genero
    pause
    exit /b 1
)
