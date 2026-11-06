@echo off
title AI Safety - Alinhamento da AURA-67
cd /d "%~dp0"

echo ========================================================
echo   AI Safety: Alinhamento da AURA-67
echo   CESAR School - Projeto Integrador 2 (PI2)
echo ========================================================
echo.

:: Obtém o caminho da pasta atual convertido dinamicamente para o WSL
for /f "tokens=*" %%a in ('wsl wslpath -u "%CD%" 2^>nul') do set "WSL_PATH=%%a"

:: 1. Compila as alterações para Windows através do WSL
echo [1/2] Verificando compilacao e atualizacoes de codigo...
wsl bash -c "cd '%WSL_PATH%' && make windows" 2>nul

:: 2. Se o executável nativo do Windows existir, executa-o
if exist "bin\jogo.exe" (
    echo [OK] Executavel Windows atualizado: bin\jogo.exe
    if exist "lib\raylib.dll" copy /y "lib\raylib.dll" "bin\" >nul
    echo [2/2] Iniciando jogo nativo na tela...
    start "" "bin\jogo.exe"
    goto fim
)

:: 3. Caso contrário, executa o binário Linux no WSL
echo.
echo [INFO] Executando binario Linux via WSL...
wsl bash -c "cd '%WSL_PATH%' && make && (test -n \"$DISPLAY\" || export DISPLAY=:0) && ./bin/jogo"

:fim
echo.
echo ========================================================
echo Sessao finalizada.
echo ========================================================
pause