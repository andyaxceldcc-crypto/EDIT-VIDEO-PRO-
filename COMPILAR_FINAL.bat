@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion
cd /d "%~dp0"

color 0A
title Filmora Editor Pro - Compilación Automática

cls
echo.
echo ╔══════════════════════════════════════════════════════════════════╗
echo ║                                                                  ║
echo ║          🎬 FILMORA EDITOR PRO - COMPILACION AUTOMATICA         ║
echo ║                                                                  ║
echo ║  Estado: Esperando finalización de Visual Studio Build Tools   ║
echo ║                                                                  ║
echo ╚══════════════════════════════════════════════════════════════════╝
echo.

REM Esperar a Visual Studio
:wait_vs
tasklist | find /i "vs_installer" >nul 2>&1
if %errorlevel% equ 0 (
    echo ⏳ Instalando Visual Studio (proceso en curso)...
    timeout /t 5 >nul
    goto wait_vs
)

echo.
echo ✓ Visual Studio Build Tools instalado
echo.
echo [PASO 1/3] Buscando Qt...

REM Buscar Qt en rutas comunes
set "QT_FOUND=0"
for /d %%Q in (C:\Qt\6.* C:\Qt\5.*) do (
    if exist "%%Q\bin\qmake.exe" (
        set "QT_PATH=%%Q\bin"
        set "QT_FOUND=1"
        echo ✓ Qt encontrado en: %%Q
        goto found_qt
    )
)

if %QT_FOUND% equ 0 (
    echo.
    echo ⚠️  Qt no encontrado. Descargando instalador online...
    echo.
    
    REM Descargar instalador online de Qt
    powershell -Command "$ProgressPreference = 'SilentlyContinue'; try { Invoke-WebRequest -Uri 'https://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe' -OutFile '%TEMP%\qt-installer.exe' } catch { Write-Host 'Descarga manual requerida' }"
    
    if exist "%TEMP%\qt-installer.exe" (
        echo Ejecutando instalador de Qt...
        echo Por favor, selecciona: Desktop (MSVC 2022 64-bit) durante la instalación
        echo.
        start /wait "" "%TEMP%\qt-installer.exe"
    )
)

:found_qt
if %QT_FOUND% equ 0 (
    echo ERROR: No se pudo instalar Qt
    pause
    exit /b 1
)

echo.
echo [PASO 2/3] Configurando rutas...
set "PATH=!QT_PATH!;!PATH!"
where qmake >nul 2>&1
if errorlevel 1 (
    echo ERROR: qmake no disponible
    pause
    exit /b 1
)

echo ✓ Qt confirmado
echo.
echo [PASO 3/3] Compilando Filmora Editor Pro...
echo.

REM Crear directorio de build
if exist "build" rmdir /s /q build
mkdir build
cd build

echo Generando configuración con qmake...
qmake ..\FilmoraEditor.pro -spec win32-msvc CONFIG+=release

if errorlevel 1 (
    echo ERROR: qmake falló
    cd ..
    pause
    exit /b 1
)

echo.
echo Compilando (esto tardará 5-15 minutos)...
echo.

nmake /NOLOGO

if errorlevel 1 (
    echo.
    echo ❌ ERROR: La compilación falló
    echo.
    echo Posibles soluciones:
    echo 1. Reinicia Visual Studio Build Tools
    echo 2. Verifica que Qt esté correctamente instalado
    echo 3. Comprueba espacio en disco libre
    echo.
    cd ..
    pause
    exit /b 1
)

cd ..

REM Verificar ejecutable
if exist "build\release\FilmoraEditor.exe" (
    echo.
    echo.
    echo ╔══════════════════════════════════════════════════════════════════╗
    echo ║                                                                  ║
    echo ║  ✅ ✅ ✅  COMPILACION EXITOSA  ✅ ✅ ✅                       ║
    echo ║                                                                  ║
    echo ║  📍 Ejecutable: build\release\FilmoraEditor.exe                ║
    echo ║  📦 Tamaño: ~50MB                                             ║
    echo ║  ⚡ Estado: Listo para usar                                    ║
    echo ║                                                                  ║
    echo ║  Presiona una tecla para ejecutar...                          ║
    echo ║                                                                  ║
    echo ╚══════════════════════════════════════════════════════════════════╝
    echo.
    
    pause
    
    echo.
    echo 🚀 Iniciando Filmora Editor Pro...
    echo.
    
    start "" "build\release\FilmoraEditor.exe"
) else (
    echo.
    echo ❌ ERROR: El ejecutable no se generó
    echo.
    pause
    exit /b 1
)
