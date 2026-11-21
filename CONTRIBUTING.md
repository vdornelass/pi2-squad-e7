# Guia de Contribuição & Sustentabilidade — Squad E7

Bem-vindo ao repositório oficial de **AI Safety: Alinhamento Ético da AURA-67** (*Projeto Integrador 2 — CESAR School*).

Este documento atende ao princípio de **Sustentabilidade de Engenharia de Software (FDS — [PI2-240](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-240) / [PI2-241](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-241))**: qualquer desenvolvedor(a), avaliador(a) ou contribuidor(a) externo(a) deve conseguir **configurar o ambiente do zero, compilar, executar a suíte de testes automatizados e contribuir com segurança sem depender da presença da equipe original**.

---

## Sumário

1. [Visão Geral da Arquitetura & Stack Técnica](#1-visão-geral-da-arquitetura--stack-técnica)
2. [Mapa do Repositório e Módulos em C99](#2-mapa-do-repositório-e-módulos-em-c99)
3. [Configuração Passo a Passo do Ambiente](#3-configuração-passo-a-passo-do-ambiente)
   - [3.1. Windows (Execução Portátil & Compilação MinGW/w64devkit)](#31-windows-execução-portátil--compilação-mingww64devkit)
   - [3.2. Linux (Ubuntu / Debian) e WSL2](#32-linux-ubuntu--debian-e-wsl2)
   - [3.3. macOS (Referência de Build C99)](#33-macos-referência-de-build-c99)
4. [Compilação, Execução e Testes Automatizados (`Makefile`)](#4-compilação-execução-e-testes-automatizados-makefile)
5. [Padrões de Código C99 Estrito](#5-padrões-de-código-c99-estrito)
6. [Fluxo de Trabalho Git, Conventional Commits e Rastreabilidade Jira](#6-fluxo-de-trabalho-git-conventional-commits-e-rastreabilidade-jira)
7. [Checklist de Pull Request & Definition of Done (DoD)](#7-checklist-de-pull-request--definition-of-done-dod)
8. [Troubleshooting (Resolução de Problemas Comuns)](#8-troubleshooting-resolução-de-problemas-comuns)

---

## 1. Visão Geral da Arquitetura & Stack Técnica

* **Linguagem:** C padrão ISO **C99** (`-std=c99`) com compilação estrita (`-Wall -Wextra -pedantic`).
* **Engine Gráfica e Áudio:** **Raylib 5.0** — cabeçalhos (`include/`) e bibliotecas estáticas/dinâmicas (`lib/`) já estão **embutidos (*vendored*) no repositório**, eliminando a necessidade de instalar a Raylib manualmente no sistema.
* **Áudio Sintetizado:** Efeitos sonoros gerados proceduralmente em memória PCM 16-bit (`src/audio.c`), sem dependência de arquivos externos `.wav`/`.ogg`.
* **Persistência & Auditoria:** Save binário com *magic number* `0x41555241` (`bin/savegame.dat`), histórico CSV (`bin/matches.csv`), Top 10 ordenado via `qsort` (`bin/ranking.txt`) e certificados pós-vitória em texto/JSON (`bin/certificado.txt`, `bin/certificado.json`).
* **Integração Contínua (CI):** GitHub Actions ([`.github/workflows/build.yml`](./.github/workflows/build.yml)) valida automaticamente a compilação limpa em `ubuntu-latest` a cada *push* ou *Pull Request* para `main`.

---

## 2. Mapa do Repositório e Módulos em C99

```text
pi2-squad-e7/
├── .github/
│   ├── ISSUE_TEMPLATE/        # Modelos padronizados de Bug Report e Feature Request
│   ├── pull_request_template.md
│   └── workflows/build.yml    # Pipeline CI em Ubuntu (GCC + C99 estrito)
├── bin/                       # Executáveis compilados (bin/jogo, bin/jogo.exe) e dados de runtime
├── docs/                      # Especificações, casos de teste, diagramas UML, PM Canvas e slides
│   ├── apresentacao_final/    # Deck oficial da Apresentação Final (PDF e PPTX)
│   └── ...
├── include/                   # Cabeçalhos oficiais Raylib 5.0 (raylib.h, raymath.h, rlgl.h)
├── lib/                       # Binários Raylib (libraylib.a, libraylib.so, raylib.dll)
├── src/                       # Código-fonte modular em C99
├── tests/                     # Suíte automatizada de validação lógica (LMC)
├── CONTRIBUTING.md            # Este guia de contribuição e sustentabilidade
├── jogar.bat                  # Launcher portátil e autocompilador para Windows
├── LICENSE                    # Licença MIT
├── Makefile                   # Automação multiplataforma (Linux, WSL, Windows e Testes LMC)
└── README.md                  # Documentação central do projeto e evidências FDS/FP2
```

### Detalhamento dos Módulos em `src/` e `tests/`

| Arquivo / Módulo | Responsabilidade Principal | Estruturas / Símbolos-Chave |
| :--- | :--- | :--- |
| `src/config.h` | Constantes globais: janela (`1280x720`, 60 FPS), margens da arena, paleta Cyberpunk/Neon, HP, durações e pontuação | `SCREEN_WIDTH`, `SCREEN_HEIGHT`, `TOTAL_DIRECTIVES`, `SCORE_PERFECT` |
| `src/game_state.c/h` | Contexto central único do jogo e máquina de estados (`STATE_MENU` a `STATE_RANKING`) | `GameState`, `GameContext`, `game_state_init()`, `game_state_reset_combat()` |
| `src/main.c` | *Game Loop* principal a 60 FPS, tratamento de entrada, transições de tela e orquestração dos módulos | `main()`, `combat_process_round()` |
| `src/player.c/h` | Movimentação do Engenheiro (WASD/Setas), colisão com arena, *invulnerability frames* e confusão | `Player`, `player_init()`, `player_update()`, `player_take_damage()` |
| `src/boss.c/h` | Comportamento da IA **AURA-67** em 3 Fases Cognitivas, alinhamento ético (0%–100%) e temporizadores | `Boss`, `boss_get_phase()`, `boss_update()`, `boss_take_damage()` |
| `src/bullet.c/h` | Pool de até 800 projéteis (`BULLET_NORMAL`, `HOMING`, `BLIND`, `CONFUSE`), lasers e vórtice | `BulletManager`, `MAX_BULLETS`, `bullet_mgr_update()` |
| `src/typing_engine.c/h` | Motor de digitação das 10 diretrizes éticas, detecção de erros, precisão (%) e *blindness* | `TypingEngine`, `typing_engine_handle_key()`, `typing_engine_get_accuracy()` |
| `src/ui.c/h` | Renderização de HUD, Menu Terminal CLI (`AURA-67 KERNEL v2.0`), fontes TrueType UTF-8 e telas finais | `UIManager`, `ui_draw_menu()`, `ui_draw_victory()`, `ui_load_fonts()` |
| `src/save.c/h` | Persistência binária de sessão (`bin/savegame.dat`) com verificação de integridade e log CSV | `SaveData`, `SAVE_MAGIC_NUMBER`, `save_game()`, `load_game()`, `save_match_result()` |
| `src/ranking.c/h` | Ranking Top 10 persistente (`bin/ranking.txt`) ordenado com `qsort` e estatísticas (`bin/matches.csv`) | `RankingEntry`, `MatchStats`, `ranking_add_score()`, `ranking_compute_stats()` |
| `src/audio.c/h` | Síntese procedural de ondas PCM 16-bit via API de áudio da Raylib | `audio_init()`, `audio_play_key_ok()`, `audio_play_victory()` |
| `src/report.c/h` | Emissão do Certificado de Alinhamento Ético pós-vitória (`bin/certificado.txt` e `.json`) | `Certificate`, `report_build()`, `report_export()`, `report_draw_certificate()` |
| `tests/test_logica_lmc.c` | Suíte automatizada com **181 verificações lógicas** (MEF, tabelas-verdade, fases e precisão) | Executável `bin/test_lmc` via `make test-lmc` |

---

## 3. Configuração Passo a Passo do Ambiente

### 3.1. Windows (Execução Portátil & Compilação MinGW/w64devkit)

#### Opção A — Execução Rápida com `jogar.bat` (Qualquer PC Windows)
O script [`jogar.bat`](./jogar.bat) foi projetado para ser **100% portátil**:
1. Clone ou baixe o repositório:
   ```powershell
   git clone https://github.com/vdornelass/pi2-squad-e7.git
   cd pi2-squad-e7
   ```
2. Execute `.\jogar.bat` (via PowerShell, CMD ou duplo clique no Windows Explorer).
3. O script procura automaticamente um compilador (`x86_64-w64-mingw32-gcc`, `gcc` no `PATH` ou diretórios padrão como `C:\raylib\w64devkit\bin`, `C:\w64devkit\bin`, `C:\msys64\mingw64\bin`, `C:\TDM-GCC-64\bin`).
   * Se encontrar o compilador, compila `bin\jogo.exe` do zero, garante `bin\raylib.dll` e inicia o jogo.
   * Se não houver compilador local, tenta via WSL (`make windows`) ou executa diretamente o binário pré-compilado `bin\jogo.exe` (quando presente em releases).

#### Opção B — Configurar Ambiente de Desenvolvimento no Windows (w64devkit)
Para compilar manualmente e desenvolver código em C no Windows:
1. Baixe o **w64devkit** (que acompanha GCC, `mingw32-make` e ferramentas GNU) no repositório oficial: `https://github.com/skeeto/w64devkit/releases`.
2. Extraia para `C:\w64devkit` (ou `C:\raylib\w64devkit`).
3. Adicione `C:\w64devkit\bin` à variável de ambiente **`PATH`** do sistema (ou execute pelo atalho `w64devkit.exe`).
4. Valide no terminal:
   ```powershell
   gcc --version
   mingw32-make --version
   ```
5. Compile e execute dentro da pasta do projeto:
   ```powershell
   mingw32-make clean
   mingw32-make
   copy /y lib\raylib.dll bin\
   .\bin\jogo.exe
   ```

> [!TIP]
> Se você estiver utilizando **cross-compilation no WSL/Linux** para gerar o executável do Windows (`bin/jogo.exe`), instale o compilador MinGW no Ubuntu/WSL com `sudo apt-get install -y gcc-mingw-w64-x86-64` e rode `make windows`.

---

### 3.2. Linux (Ubuntu / Debian) e WSL2

Em distribuições Debian/Ubuntu nativas ou dentro do **WSL2 (Windows Subsystem for Linux)**, a compilação usa `gcc` nativo e as bibliotecas de janela/áudio X11/OpenGL exigidas pela Raylib 5.0:

1. **Instale as ferramentas de compilação e dependências gráficas da Raylib:**
   ```bash
   sudo apt-get update
   sudo apt-get install -y \
     build-essential git \
     libgl1-mesa-dev libglu1-mesa-dev \
     libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
     libasound2-dev
   ```
2. **Clone o repositório:**
   ```bash
   git clone https://github.com/vdornelass/pi2-squad-e7.git
   cd pi2-squad-e7
   ```
3. **Compile, rode os testes e execute o jogo:**
   ```bash
   make clean && make
   make test-lmc
   make run
   ```

> [!NOTE]
> No **WSL2 sem servidor X ativo**, certifique-se de utilizar Windows 11 (com **WSLg** habilitado por padrão) e verifique se `DISPLAY=:0` está definido antes de chamar `./bin/jogo`. No WSL sem backend PulseAudio/ALSA configurado, a Raylib inicializa com driver nulo (`miniaudio / Null`) sem travar o jogo; para testar o áudio sintetizado no Windows, utilize o binário nativo `bin/jogo.exe` via `.\jogar.bat`.

---

### 3.3. macOS (Referência de Build C99)

Caso deseje compilar em ambiente macOS com Xcode Command Line Tools (`xcode-select --install`) e Homebrew:
```bash
brew install raylib
gcc -Wall -Wextra -std=c99 -pedantic -Iinclude -Isrc src/*.c -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -o bin/jogo
./bin/jogo
```

---

## 4. Compilação, Execução e Testes Automatizados (`Makefile`)

O [`Makefile`](./Makefile) padroniza todos os fluxos de build e verificação:

| Comando | Ação Executada | Artefato / Saída Esperada |
| :--- | :--- | :--- |
| `make` (ou `make all`) | Compila todos os arquivos em `SRCS` com `-Wall -Wextra -std=c99 -pedantic` | Gera `bin/jogo` (Linux/WSL) ou `bin/jogo.exe` |
| `make run` | Compila (se necessário) e executa o jogo com `LD_LIBRARY_PATH=lib` | Abre a janela gráfica `1280x720` a 60 FPS |
| `make windows` | Cross-compila usando `WIN_CC` (`x86_64-w64-mingw32-gcc`) e copia `lib/raylib.dll` | Gera `bin/jogo.exe` + `bin/raylib.dll` |
| `make test-lmc` | Compila e executa `tests/test_logica_lmc.c` com os módulos lógicos do motor | Exibe **`Resultado: 181/181 verificacoes passaram.`** |
| `make clean` | Remove executáveis e objetos em `bin/` (`bin/jogo`, `bin/test_lmc`, `*.o`, `*.exe`) | Diretório `bin/` limpo para recompilação completa |

> [!IMPORTANT]
> Como o `Makefile` lista diretamente os arquivos `.c` sem rastreamento automático de dependências de cabeçalho (`#include`), **sempre execute `make clean && make` após modificar `src/config.h` ou qualquer arquivo `.h`** (referente à Issue [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10)).

### Verificação Manual e Testes de Sistema
Além da suíte unitária/lógica `make test-lmc`, os roteiros completos de testes de sistema ponta a ponta estão versionados em:
* [`docs/casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md) (27 casos de teste)
* [`docs/casos_de_teste_sprint02.md`](./docs/casos_de_teste_sprint02.md) (12 casos de teste + regressão)
* [`docs/casos_de_teste_sprint03.md`](./docs/casos_de_teste_sprint03.md) (27 casos de teste cobrindo `US16`–`US20` + regressão)

---

## 5. Padrões de Código C99 Estrito

Todo código submetido à branch `main` deve respeitar estritamente as regras abaixo:

1. **Zero Warnings:** O código deve compilar sem nenhum erro ou advertência sob `-Wall -Wextra -std=c99 -pedantic`.
2. **Nomenclatura Consistente:**
   * **Funções e variáveis:** `snake_case` em minúsculas e com prefixo do módulo (ex: `boss_get_phase`, `player_take_damage`, `typing_engine_handle_key`).
   * **Constantes e macros:** `UPPER_SNAKE_CASE` centralizadas preferencialmente em `src/config.h` ou no `.h` do módulo (ex: `MAX_BULLETS`, `SAVE_MAGIC_NUMBER`).
   * **Structs e Enums:** `PascalCase` (ex: `GameContext`, `TypingEngine`, `Certificate`).
   * **Proibido nomes genéricos isolados** como `x`, `a`, `aux`, `tmp` em assinaturas públicas (exceção apenas para iteradores simples `i`, `j` em loops curtos).
3. **Encapsulamento e Estado:** Todo estado compartilhado entre telas deve residir dentro de `GameContext` (`src/game_state.h`), evitando novas variáveis globais soltas em `src/main.c`.
4. **Arquivos `.h` Auto-contidos:** Todos os headers devem usar *include guards* (`#ifndef MODULO_H` / `#define MODULO_H` / `#endif`) e comentários concisos documentando parâmetros e responsabilidades das funções públicas.
5. **Gestão de Segurança em I/O e Buffers:** Verifique sempre o retorno de `fopen`, limite leituras/cópias de string (`snprintf`, `strncpy` com terminador nulo `\0`) e evite *buffer overflows* no histórico e relatórios.
6. **Limpeza do Repositório:** Não envie arquivos temporários, executáveis compilados localmente (`bin/jogo`, `bin/savegame.dat`) ou cópias duplicadas (`*(teste).*`) em commits. O `.gitignore` já protege artefatos binários padrão.

---

## 6. Fluxo de Trabalho Git, Conventional Commits e Rastreabilidade Jira

Adotamos o **Feature Branch Workflow** com rastreabilidade bidirecional direta com o **Board do Jira (`PI2`)**:

### Passo 1 — Sincronize a `main` local
```bash
git checkout main
git pull origin main
```

### Passo 2 — Crie uma branch vinculada ao card do Jira
Nunca faça *push* direto para a `main`. Nomeie sua branch iniciando pela chave `PI2-XXX` do ticket:
```bash
git checkout -b feature/PI2-XXX-descricao-curta
# Exemplos de prefixo: feature/, fix/, docs/, test/
```

### Passo 3 — Escreva commits no padrão Conventional Commits
Use o formato **`tipo(escopo): descrição objetiva (PI2-XXX)`**:

| Prefixo | Uso | Exemplo Real do Projeto |
| :--- | :--- | :--- |
| `feat` | Nova funcionalidade | `feat(PI2-214): implementar sistema de audio sintetizado em C (PI2-33, closes #3)` |
| `fix` | Correção de bug ou falha de build | `fix(pif): jogar.bat portatil, roda em qualquer PC (PI2-254)` |
| `docs` | Documentação, README, relatórios | `docs(lmc): relatorio de validacao logica da Unidade 2 (PI2-31)` |
| `test` | Adição ou ajuste de testes | `test(lmc): adicionar casos de invariante da AURA-67 (PI2-31)` |
| `refactor` | Reestruturação interna sem alterar feature | `refactor(game_state): encapsular contexto global do jogo (PI2-178)` |
| `style` | Formatação ou ajuste visual | `style(lmc): redesign visual do relatorio da AV1` |
| `ci` | Workflows do GitHub Actions e automação | `ci(github): estruturar CI actions e templates de PR/issue` |

### Passo 4 — Envie para o GitHub e abra um Pull Request
```bash
git push -u origin feature/PI2-XXX-descricao-curta
```
*(Caso contribua a partir de um fork, envie para seu `fork` e abra o PR apontando para `vdornelass/pi2-squad-e7:main`.)*

Ao abrir o Pull Request no GitHub, preencha completamente o [`.github/pull_request_template.md`](./.github/pull_request_template.md), informando o link do card no Jira (`PI2-XXX`), a disciplina relacionada e as evidências de execução.

---

## 7. Checklist de Pull Request & Definition of Done (DoD)

Um card ou Pull Request só é considerado **Concluído (Done)** quando atende a todos os critérios abaixo:

- [ ] **Critérios 3Cs:** Todos os critérios de *Confirmação* da história/subtarefa no Jira foram cumpridos.
- [ ] **Compilação Limpa (Local e CI):** `make clean && make` compila com **0 erros e 0 warnings** (`-Wall -Wextra -std=c99 -pedantic`) e o workflow do GitHub Actions passa em verde.
- [ ] **Testes Validados:** `make test-lmc` retorna **181/181 verificações aprovadas** e o jogo foi testado manualmente na interface gráfica (ou Windows via `jogar.bat`) sem regressões ou travamentos.
- [ ] **Revisão por Pares (*Code Review*):** Pelo menos um integrante da Squad E7 revisou o PR no GitHub.
- [ ] **Rastreabilidade & Evidência:** Mensagens de commit citam a chave `PI2-XXX`, e o card do Jira foi atualizado com comentário técnico / print / screencast e movido para **Concluído**.

---

## 8. Troubleshooting (Resolução de Problemas Comuns)

<details>
<summary><strong>1. Erro "raylib.dll não encontrado" ao abrir bin/jogo.exe no Windows</strong></summary>

Copie a DLL incluída na pasta `lib/` para junto do executável em `bin/` (o `jogar.bat` já faz isso automaticamente):
```powershell
copy /y lib\raylib.dll bin\
```
</details>

<details>
<summary><strong>2. Alterações em src/config.h não refletiram após rodar `make`</strong></summary>

O `Makefile` monitora arquivos `.c`. Sempre force a recompilação limpa ao modificar cabeçalhos (Issue [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10)):
```bash
make clean && make
```
</details>

<details>
<summary><strong>3. O jogo roda sem som ao executar dentro do WSL</strong></summary>

O WSL sem servidor de áudio Windows/PulseAudio acoplado inicializa a Raylib com backend silencioso (`miniaudio / Null`). Para ouvir os efeitos sonoros sintetizados da `US19`, execute a versão nativa Windows usando `.\jogar.bat` (que compila e executa `bin\jogo.exe` fora do WSL).
</details>

<details>
<summary><strong>4. Erro de biblioteca `-lGL`, `-lX11` ou `asound` ausente no Linux</strong></summary>

Instale todos os cabeçalhos de desenvolvimento X11/OpenGL/ALSA listados na [Seção 3.2](#32-linux-ubuntu--debian-e-wsl2) antes de rodar `make`.
</details>

<details>
<summary><strong>5. Git pede autenticação repetidamente ou bloqueia push direto em origin</strong></summary>

Contribuintes sem permissão direta de escrita em `vdornelass/pi2-squad-e7` devem fazer *fork* do repositório, adicionar o remote `fork` (`git remote add fork <url-do-fork>`) e enviar para sua branch no fork antes de abrir o Pull Request para `origin/main`.
</details>
