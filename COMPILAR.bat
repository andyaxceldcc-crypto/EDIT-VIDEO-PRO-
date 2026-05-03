@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

echo.
echo ╔════════════════════════════════════════════════════════════╗
echo ║         FILMORA EDITOR PRO - DESCARGA E INSTALACION       ║
echo ╚════════════════════════════════════════════════════════════╝
echo.

REM Descargar Qt
echo [1/4] Descargando Qt 6...
powershell -Command "& {$ProgressPreference = 'SilentlyContinue'; try { Invoke-WebRequest -Uri 'https://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe' -OutFile '%TEMP%\qt-installer.exe' } catch { Write-Host 'Usando descarga alternativa...'; Invoke-WebRequest -Uri 'https://mirror.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe' -OutFile '%TEMP%\qt-installer.exe' } }"

if not exist "%TEMP%\qt-installer.exe" (
    echo ERROR: No se pudo descargar Qt
    echo Intenta manualmente: https://www.qt.io/download
    pause
    exit /b 1
)

echo ✓ Qt descargado

REM Instalar Qt
echo.
echo [2/4] Instalando Qt 6 (esto tardará varios minutos)...
start /wait "" "%TEMP%\qt-installer.exe"

REM Verificar qmake
echo.
echo [3/4] Verificando instalación de Qt...
where qmake >nul 2>&1

if errorlevel 1 (
    echo Buscando qmake en rutas comunes...
    
    if exist "C:\Qt\6.0\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.0\msvc2019_64\bin"
    ) else if exist "C:\Qt\6.1\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.1\msvc2019_64\bin"
    ) else if exist "C:\Qt\6.2\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.2\msvc2019_64\bin"
    ) else if exist "C:\Qt\6.3\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.3\msvc2019_64\bin"
    ) else if exist "C:\Qt\6.4\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.4\msvc2019_64\bin"
    ) else if exist "C:\Qt\6.5\msvc2019_64\bin\qmake.exe" (
        set "QT_PATH=C:\Qt\6.5\msvc2019_64\bin"
    ) else (
        echo ERROR: No se encontró qmake
        pause
        exit /b 1
    )
    
    set "PATH=!QT_PATH!;!PATH!"
)

echo ✓ Qt instalado correctamente

REM Compilar
echo.
echo [4/4] Compilando Filmora Editor Pro...
echo.

mkdir build 2>nul
cd build

qmake ..\..\FilmoraEditor.pro -spec win32-msvc CONFIG+=release

if errorlevel 1 (
    echo ERROR: qmake falló
    pause
    exit /b 1
)

nmake /NOLOGO

if errorlevel 1 (
    echo ERROR: Compilación falló
    pause
    exit /b 1
)

echo.
echo ╔════════════════════════════════════════════════════════════╗
echo ║  ✓ COMPILACION EXITOSA                                     ║
echo ║                                                             ║
echo ║  Ejecutable: build\release\FilmoraEditor.exe               ║
echo ║                                                             ║
echo ║  Iniciando aplicación...                                   ║
echo ╚════════════════════════════════════════════════════════════╝
echo.

timeout /t 2
start "" "build\release\FilmoraEditor.exe"

pause
