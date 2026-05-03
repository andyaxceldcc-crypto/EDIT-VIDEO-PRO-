@echo off
REM Compilación limpia del Filmora Editor Pro
setlocal enabledelayedexpansion

cd /d "%~dp0"

echo.
echo ======== FILMORA EDITOR PRO - COMPILACION ========
echo.

REM Buscar Qt en rutas comunes
set "QT_FOUND=0"
for /d %%Q in (C:\Qt\6.* C:\Qt\5.*) do (
    if exist "%%Q\bin\qmake.exe" (
        set "QT_PATH=%%Q\bin"
        set "QT_FOUND=1"
        echo Qt encontrado en: %%Q
        goto found_qt
    )
)

:found_qt
if %QT_FOUND% equ 0 (
    echo ERROR: Qt no encontrado
    echo Descargalo desde: https://www.qt.io/download
    pause
    exit /b 1
)

echo.
echo Configurando rutas...
set "PATH=!QT_PATH!;!PATH!"

REM Crear directorio de build
if exist "build" rmdir /s /q build
mkdir build
cd build

echo.
echo Generando configuracion con qmake...
qmake ..\FilmoraEditor.pro -spec win32-msvc CONFIG+=release

if errorlevel 1 (
    echo ERROR: qmake fallo
    cd ..
    pause
    exit /b 1
)

echo.
echo Compilando (esto puede tardar varios minutos)...
echo.

nmake /NOLOGO

if errorlevel 1 (
    echo.
    echo ERROR: La compilacion fallo
    cd ..
    pause
    exit /b 1
)

cd ..

REM Verificar ejecutable
if exist "build\release\FilmoraEditor.exe" (
    echo.
    echo ======== COMPILACION EXITOSA ========
    echo.
    echo Ejecutable: build\release\FilmoraEditor.exe
    echo.
    
    REM Copiar DLLs necesarias
    echo Copiando DLLs...
    for /r "!QT_PATH!\..\..\..\bin" %%F in (*.dll) do (
        if exist "%%F" (
            copy "%%F" "build\release\" >nul 2>&1
        )
    )
    
    echo.
    echo Presiona una tecla para ejecutar...
    pause
    
    start "" "build\release\FilmoraEditor.exe"
) else (
    echo.
    echo ERROR: El ejecutable no se genero
    pause
    exit /b 1
)

endlocal
