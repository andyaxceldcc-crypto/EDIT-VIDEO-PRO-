@echo off
echo ======================================
echo Instalando dependencias de Filmora Editor
echo ======================================

echo Verificando Python...
python --version >nul 2>&1

if errorlevel 1 (
    echo ERROR: Python no está instalado
    echo Descarga Python desde: https://www.python.org/downloads/
    echo Asegúrate de marcar "Add Python to PATH"
    pause
    exit /b 1
)

echo Python encontrado
echo.
echo Instalando PyQt6...
pip install PyQt6 --upgrade

if errorlevel 1 (
    echo ERROR: Falla al instalar PyQt6
    pause
    exit /b 1
)

echo.
echo ======================================
echo Dependencias instaladas exitosamente
echo Ejecutando Filmora Editor...
echo ======================================
echo.

python filmora_editor.py

pause
