@echo off
title Filmora Editor Pro - Video Editing Suite
color 0A

echo.
echo ╔════════════════════════════════════════════════════════════╗
echo ║                                                             ║
echo ║        🎬 FILMORA EDITOR PRO - VIDEO EDITING SUITE         ║
echo ║                                                             ║
echo ║              Iniciando aplicación...                       ║
echo ║                                                             ║
echo ╚════════════════════════════════════════════════════════════╝
echo.

REM Buscar navegador predeterminado
for /f "tokens=2*" %%A in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.html\UserChoice" /v Progid 2^>nul') do set "BROWSER=%%B"

REM Si no lo encontró, usar Edge o Chrome
if "%BROWSER%"=="" (
    if exist "C:\Program Files\Microsoft\Edge\Application\msedge.exe" (
        start "" "C:\Program Files\Microsoft\Edge\Application\msedge.exe" "%~dp0index.html"
    ) else if exist "C:\Program Files\Google\Chrome\Application\chrome.exe" (
        start "" "C:\Program Files\Google\Chrome\Application\chrome.exe" "%~dp0index.html"
    ) else if exist "C:\Program Files (x86)\Mozilla Firefox\firefox.exe" (
        start "" "C:\Program Files (x86)\Mozilla Firefox\firefox.exe" "%~dp0index.html"
    ) else (
        start "" "%~dp0index.html"
    )
) else (
    start "" "%~dp0index.html"
)

echo ✓ Filmora Editor está en tu navegador predeterminado
echo.
echo 📌 Funciones disponibles:
echo    ✓ Importar videos (MP4, AVI, MOV)
echo    ✓ Timeline interactivo
echo    ✓ +50 efectos profesionales
echo    ✓ Transiciones suaves
echo    ✓ Exportación 4K
echo    ✓ Sistema de suscripción ($100/mes)
echo.
echo 💡 Plan Premium incluye:
echo    ✓ Exportación sin límites
echo    ✓ Acceso a todos los efectos
echo    ✓ Soporte prioritario
echo    ✓ Uso comercial
echo.
echo Presiona Ctrl+C para cerrar
echo.

pause
