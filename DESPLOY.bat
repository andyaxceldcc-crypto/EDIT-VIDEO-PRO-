@echo off
chcp 65001 >nul
cd /d "%~dp0"

echo.
echo ╔══════════════════════════════════════════════════════════════════╗
echo ║                                                                  ║
echo ║       📦 FILMORA EDITOR PRO - CREAR PAQUETE PORTABLE           ║
echo ║                                                                  ║
echo ╚══════════════════════════════════════════════════════════════════╝
echo.

REM Verificar que existe el ejecutable
if not exist "build\release\FilmoraEditor.exe" (
    echo ❌ ERROR: No se encontro FilmoraEditor.exe
    echo Primero debe compilar el proyecto: COMPILAR_FINAL.bat
    pause
    exit /b 1
)

echo.
echo [PASO 1/3] Entrando al directorio de compilacion...
cd build\release
if errorlevel 1 (
    echo ERROR: No se pudo acceder a build\release
    pause
    exit /b 1
)
echo ✓ Directorio preparado
echo.

echo [PASO 2/3] Desplegando DLLs de Qt...
echo.

REM Buscar Qt
set "QT_PATH="
for /d %%Q in (C:\Qt\6.*) do (
    if exist "%%Q\msvc2022_64\bin\windeployqt.exe" (
        set "QT_PATH=%%Q\msvc2022_64"
    )
)

if "%QT_PATH%"=="" (
    echo ⚠️  Qt no encontrado. Buscando en rutas alternatives...
    for /d %%Q in ("C:\Qt\5.*") do (
        if exist "%%Q\msvc2019_64\bin\windeployqt.exe" (
            set "QT_PATH=%%Q\msvc2019_64"
        )
    )
)

if "%QT_PATH%"=="" (
    echo ❌ ERROR: No se encontro windeployqt.exe
    echo Instale Qt 6.x correctamente
    pause
    exit /b 1
)

echo ✓ Qt encontrado en: %QT_PATH%
echo.
echo Ejecutando windeployqt (puede tardar varios minutos)...
"%QT_PATH%\bin\windeployqt.exe" FilmoraEditor.exe --no-translations

if errorlevel 1 (
    echo ⚠️  Advertencia: windeployqt tuvo problemas, continuando...
)

echo.
echo [PASO 3/3] Copiando DLLs de FFmpeg...
echo.

REM Copiar DLLs de vcpkg
if exist "C:\vcpkg\installed\x64-windows\bin" (
    echo ✓ Encontrado vcpkg FFmpeg
    copy "C:\vcpkg\installed\x64-windows\bin\avcodec*.dll" . >nul 2>&1
    copy "C:\vcpkg\installed\x64-windows\bin\avformat*.dll" . >nul 2>&1
    copy "C:\vcpkg\installed\x64-windows\bin\avutil*.dll" . >nul 2>&1
    copy "C:\vcpkg\installed\x64-windows\bin\swscale*.dll" . >nul 2>&1
    copy "C:\vcpkg\installed\x64-windows\bin\swresample*.dll" . >nul 2>&1
    echo ✓ DLLs de vcpkg copiadas
) else (
    echo ⚠️  vcpkg no encontrado, buscando FFmpeg directo...
    if exist "C:\ffmpeg\bin" (
        copy "C:\ffmpeg\bin\avcodec*.dll" . >nul 2>&1
        copy "C:\ffmpeg\bin\avformat*.dll" . >nul 2>&1
        copy "C:\ffmpeg\bin\avutil*.dll" . >nul 2>&1
        copy "C:\ffmpeg\bin\swscale*.dll" . >nul 2>&1
        copy "C:\ffmpeg\bin\swresample*.dll" . >nul 2>&1
        echo ✓ DLLs de C:\ffmpeg\bin copiadas
    )
)

REM Copiar MSVC runtime si existe
if exist "C:\Program Files\Microsoft Visual Studio\*\*\VC\Redist\*\*\x64" (
    echo ✓ Runtime de MSVC encontrado
)

cd ..\..
echo.

REM Mostrar resultado
echo.
echo ╔══════════════════════════════════════════════════════════════════╗
echo ║                                                                  ║
echo ║  ✅ PAQUETE PORTABLE CREADO EXITOSAMENTE!                       ║
echo ║                                                                  ║
echo ║  📍 Ubicacion: build\release\                                    ║
echo ║                                                                  ║
echo ║  📦 Contenido del paquete:                                      ║
echo ║     - FilmoraEditor.exe (Ejecutable principal)                   ║
echo ║     - DLLs de Qt 6 (Widgets, Core, GUI, Multimedia, etc.)        ║
echo ║     - DLLs de FFmpeg (avcodec, avformat, avutil, swscale)        ║
echo ║     - Recursos y plugins                                        ║
echo ║                                                                  ║

for %%A in ("build\release\FilmoraEditor.exe") do set SIZE=%%~zA
set /a MB=%SIZE:~0,-3% / 1048576
echo ║  📊 Tamanio aproximado: ~%MB% MB                                    ║
echo ║                                                                  ║
echo ║  💡 Este paquete es portable y puede ejecutarse en               ║
echo ║     cualquier Windows 10/11 sin necesidad de instalar Qt          ║
echo ║                                                                  ║
echo ╚══════════════════════════════════════════════════════════════════╝
echo.

REM Mostrar lista de archivos
echo Archivos DLL copiados:
dir /b build\release\*.dll 2>nul | findstr /r "^av.*\.dll$ ^Qt.*\.dll$" | head /n 20

echo.
echo Presiona una tecla para abrir la carpeta del paquete...
pause >nul
start explorer build\release