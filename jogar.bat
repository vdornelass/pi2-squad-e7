@echo off
title AI Safety - Alinhamento da AURA-67
cd /d "%~dp0"

echo ========================================================
echo   AI Safety: Alinhamento da AURA-67
echo   CESAR School - Projeto Integrador 2 (PI2)
echo ========================================================
echo.

for /f "tokens=*" %%a in ('wsl wslpath -u "%CD%" 2^>nul') do set "WSL_PATH=%%a"

if defined WSL_PATH (
    echo [1/2] Atualizando binarios compilados...
    taskkill /f /im jogo.exe >nul 2>&1
    wsl bash -c "cd '%WSL_PATH%' && make && make windows" 2>nul
)

echo.
echo [2/2] Tentando iniciar executavel nativo do Windows (bin\jogo.exe)...
if exist "bin\jogo.exe" (
    "bin\jogo.exe"
    if not errorlevel 1 goto fim
)

echo.
echo [AVISO] O Controle Inteligente de Aplicativos do Windows bloqueou o .exe nao assinado.
echo         Iniciando via WSLg...
wsl bash -c "cd '%WSL_PATH%' && DISPLAY=:0 PULSE_SERVER=unix:/mnt/wslg/PulseServer LD_LIBRARY_PATH=lib ./bin/jogo"

:fim
echo.
echo ========================================================
echo Sessao finalizada.
echo ========================================================
pause
