@echo off
REM Compilar Filmora Editor con Qt

echo ======================================
echo Compilando Filmora Editor Pro
echo ======================================

REM Verificar si Qt está instalado
if not exist "C:\Qt" (
    echo ERROR: Qt no está instalado
    echo Descargue Qt desde: https://www.qt.io/download
    pause
    exit /b 1
)

REM Buscar la versión de Qt más reciente
for /d %%D in (C:\Qt\*) do (
    set QT_PATH=%%D
)

echo Qt encontrado en: %QT_PATH%

REM Compilar con qmake
echo.
echo Generando archivos de proyecto...
%QT_PATH%\bin\qmake.exe FilmoraEditor.pro

echo.
echo Compilando...
nmake /NOLOGO

if errorlevel 1 (
    echo ERROR: La compilación falló
    pause
    exit /b 1
)

echo.
echo ======================================
echo Compilación completada exitosamente!
echo Ejecutable: build/release/FilmoraEditor.exe
echo ======================================
pause
