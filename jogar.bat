@echo off
setlocal EnableExtensions
title AI Safety - Alinhamento da AURA-67
cd /d "%~dp0"

echo ========================================================
echo   AI Safety: Alinhamento da AURA-67
echo   CESAR School - Projeto Integrador 2 (PI2)
echo ========================================================
echo.

set "EXE=bin\jogo.exe"
set "CC="


set "SRCS=src\main.c src\player.c src\boss.c src\bullet.c src\typing_engine.c src\ui.c src\save.c src\game_state.c src\ranking.c"


where x86_64-w64-mingw32-gcc >nul 2>nul
if not errorlevel 1 set "CC=x86_64-w64-mingw32-gcc"
if not defined CC (
    where gcc >nul 2>nul
    if not errorlevel 1 set "CC=gcc"
)
if not defined CC for %%D in ("C:\raylib\w64devkit\bin" "C:\w64devkit\bin" "C:\msys64\mingw64\bin" "C:\TDM-GCC-64\bin" "%ProgramFiles%\w64devkit\bin") do if not defined CC call :tentar "%%~D"

if not defined CC goto :tentar_wsl


echo [1/2] Compilador encontrado: %CC%. Compilando...
if not exist bin mkdir bin
%CC% -Wall -Wextra -std=c99 -pedantic -Iinclude -Isrc %SRCS% -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -o "%EXE%"
if errorlevel 1 goto :falha_compilacao
goto :executar

:falha_compilacao
echo.
echo [AVISO] A compilacao falhou.
if exist "%EXE%" (
    echo [AVISO] Usando o executavel ja existente.
    goto :executar
)
goto :sem_exe


:tentar_wsl
where wsl >nul 2>nul
if errorlevel 1 goto :checar_exe
echo [INFO] Nenhum compilador no Windows. Tentando compilar via WSL...
set "WSL_PATH="
for /f "tokens=*" %%a in ('wsl wslpath -u "%CD%" 2^>nul') do set "WSL_PATH=%%a"
if not defined WSL_PATH goto :checar_exe
wsl bash -c "cd '%WSL_PATH%' && make windows" >nul 2>nul


:checar_exe
if exist "%EXE%" goto :executar
:sem_exe
echo.
echo [ERRO] %EXE% nao foi encontrado e nao ha compilador disponivel.
echo        Baixe o repositorio completo (bin\jogo.exe e bin\raylib.dll)
echo        ou instale o w64devkit/MSYS2/TDM-GCC para compilar.
goto :fim

:executar
if not exist "bin\raylib.dll" if exist "lib\raylib.dll" copy /y "lib\raylib.dll" "bin\" >nul
if not exist "bin\raylib.dll" (
    echo [ERRO] bin\raylib.dll nao encontrado.
    goto :fim
)
echo [2/2] Iniciando o jogo...
start "" /wait "%EXE%"

:fim
echo.
echo ========================================================
echo   Sessao finalizada.
echo ========================================================
pause
exit /b

:tentar
if not exist "%~1\gcc.exe" exit /b
set "PATH=%~1;%PATH%"
set "CC=gcc"
exit /b