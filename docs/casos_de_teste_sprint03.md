# Casos de Teste de Sistema: Sprint 03 (Entrega 05, FDS)

Projeto: AI Safety: Alinhamento do Modelo AURA-67 (Squad E7, CESAR School)

Os casos abaixo cobrem as cinco histórias da Sprint 03: **US16, US17, US18, US19 e US20**. Cada caso foi escrito a partir dos Critérios de Confirmação (3Cs) do card da história no Jira. O teste foi feito com o jogo rodando por inteiro (teste de sistema). No fim tem o reteste de regressão das issues abertas nas Sprints 01 e 02.

Card de referência: [PI2-237](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-237) · subtarefas [PI2-238](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-238) e [PI2-239](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-239)

## Rodadas de teste

| Rodada | Data | Versão testada (`main`) | O que foi testado |
| :-: | :-: | :-- | :-- |
| 1ª | 19/11/2026 | `2a82daa` | US18 e retestes das issues #2, #7, #8 e #10 |
| 1ª (complemento) | 20/11/2026 | `ef37f30` (`bin/jogo.exe`, PC do Caio Brayner) | US19 (áudio) |
| **2ª** | **21/11/2026** | **`3f7655d`** (menu novo, ícone, tutorial, certificado e rebalanceamento das fases) | US16, US17, US18, US19 (vitória), US20 e retestes das issues #9, #10 e #12 |
| **3ª** | **22/11/2026** | **`c35ea04`** (merge do PR [#16](https://github.com/vdornelass/pi2-squad-e7/pull/16): hash e integridade restante no certificado) | Reteste da US20 (issue [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15)) |

A coluna **Resultado obtido** mostra o resultado mais recente de cada caso.

## Resumo dos resultados (após a 3ª rodada, 22/11)

| História | Casos | Passou | Falhou | Parcial | Não testado |
| :-- | :-: | :-: | :-: | :-: | :-: |
| US16 | 4 | 3 | 1 | 0 | 0 |
| US17 | 4 | 4 | 0 | 0 | 0 |
| US18 | 4 | 4 | 0 | 0 | 0 |
| US19 | 6 | 6 | 0 | 0 | 0 |
| US20 | 4 | 4 | 0 | 0 | 0 |
| Regressão (Issues #2, #7, #8, #9, #10) | 5 | 3 | 2 | 0 | 0 |
| **Total** | **27** | **24** | **3** | **0** | **0** |

## Como executar

1. Atualizar a branch: `git pull origin main`.
2. Compilar do zero. No Windows (PowerShell), um comando por vez: `wsl make clean`, `wsl make` e `wsl make run`. No Linux ou Ubuntu: `make clean`, `make` e `make run`. O `make clean` é necessário por causa da Issue [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10).
3. **Som no WSL:** se o log da Raylib mostrar `Backend: miniaudio / Null`, instalar a biblioteca de áudio com `wsl -u root apt install -y libpulse0`. Depois disso o jogo passa a ter som pelo WSL.
4. No menu, navegar com `W`/`S` ou setas e escolher com `ENTER`, `ESPAÇO` ou clique: **Novo Jogo**, **Tutorial Guiado**, **Configurações** ou **Ranking e Estatísticas**.
5. Para os casos de áudio (US19), gravar o screencast **com o som do sistema** ligado.
6. Executar os passos de cada caso e comparar com o resultado esperado.
7. Se o caso falhar, abrir uma issue no GitHub citando o ID do caso e o card do Jira.

**Ambiente de teste da vitória:** para chegar à tela de vitória sem depender da habilidade de quem testa, o dano ao jogador foi desligado **só na máquina de teste**, com um `return false;` no início de `player_take_damage()` em `src/player.c`. A alteração **não foi commitada**. Por isso, nos vídeos de vitória os projéteis atravessam o jogador sem tirar vida.

## Vídeos de evidência

| Vídeo | Rodada | Duração | Conteúdo |
| :-- | :-: | :-: | :-- |
| [`screencast_testes_sprint03_rodada1.mp4`](./screencast_testes_sprint03_rodada1.mp4) | 1ª (19/11) | 1:27 | Menu antigo → partida completa (dano desligado) → tela de vitória |
| [`screencast_testes_sprint03_US19_audio.mp4`](./screencast_testes_sprint03_US19_audio.mp4) | 1ª (20/11) | 0:37 | US19 **com áudio**, no `bin/jogo.exe` (PC do Caio): digitação, erro, dano, patch concluído e Game Over |
| [`screencast_testes_sprint03_rodada2_partida.mp4`](./screencast_testes_sprint03_rodada2_partida.mp4) | 2ª (21/11) | 2:10 | Com áudio: menu novo → tutorial completo → configurações → ranking → partida normal até o Game Over |
| [`screencast_testes_sprint03_rodada2_vitoria.mp4`](./screencast_testes_sprint03_rodada2_vitoria.mp4) | 2ª (21/11) | 1:58 | Com áudio: tutorial (dano, erros e saída com ESC) → configurações → partida com dano desligado → vitória → certificado → arquivo `bin/certificado.txt` no terminal |
| [`screencast_testes_sprint03_rodada3_US20.mp4`](./screencast_testes_sprint03_rodada3_US20.mp4) | 3ª (22/11) | 2:03 | Com áudio: partida com dano desligado (acelerada na edição) → vitória → certificado com integridade restante → `bin/certificado.txt` com o hash → `make verificar-certificado` com o arquivo original (OK) e depois de alterado (ALTERADO) |

*O vídeo de 19/11 foi gravado **sem áudio** e foi **acelerado na edição**. Por isso o "Tempo de Sessão" na tela de vitória (02:21) é maior que a duração do vídeo. Os demais vídeos estão em velocidade normal e com o som do jogo.*

## US16: Identidade Visual e Ícone Personalizado ([PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US16-01 | CA04 | No Windows, rodar `make windows`. | Compila e gera `bin/jogo.exe` com o ícone embutido, sem warnings. | Passou | Teste de 21/11, depois de instalar o compilador no WSL (`wsl -u root apt install -y gcc-mingw-w64-x86-64 binutils-mingw-w64-x86-64`): o `wsl make windows` compilou com o recurso do ícone (`bin/icon.res`) e terminou sem nenhum warning (saída abaixo). [Print de 21/11](./img/print_us16_make_windows.png): o `jogo.exe` recém-gerado (19:54), junto com o `icon.res` (19:53), aparece com o ícone da AURA-67 |
| CT-US16-02 | CA01 | Abrir a pasta `bin/` no Windows Explorer. | `jogo.exe` aparece com o ícone da AURA-67, não com o ícone padrão. | Passou | [Print de 21/11](./img/print_us16_icone_exe.png): na pasta `bin/`, o `jogo` do tipo Aplicativo (`jogo.exe`, versão `3f7655d`) aparece com o ícone da AURA-67. O binário Linux (`jogo`, sem extensão) aparece com o ícone padrão de arquivo, como esperado |
| CT-US16-03 | CA02 | Abrir o jogo e olhar a barra de título e a barra de tarefas. | As duas mostram o ícone oficial do AI Safety. | **Falhou** | [Print de 21/11](./img/print_us16_icone_barra_tarefas.png), rodando pelo WSL: a **barra de tarefas** mostra o ícone da AURA-67 ✅, mas a **barra de título** da janela mostra o ícone genérico ❌ (também no vídeo rodada 2, partida, `0:00 – 0:04`). Em 22/11, o Caio Brayner abriu o `bin/jogo.exe` direto no Windows e relatou que a barra de título também mostra o ícone genérico (relato sem print). Registrado na Issue [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17) |
| CT-US16-04 | CA03 | Renomear a pasta `assets/` para `assets_off/` e abrir o jogo. Depois, voltar o nome. | O ícone continua embutido e o jogo abre normalmente, mesmo sem a pasta `assets/`. | Passou | [Print de 22/11](./img/print_us16_sem_assets.png): sem a pasta `assets/`, o jogo abre normalmente com a arte da AURA-67 (embutida em `src/icon_data.h`). O log mostra o aviso de que a fonte TrueType não foi encontrada e o jogo usa a fonte padrão da Raylib, sem travar. O critério CA03 foi atualizado no card [PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217) em 22/11, porque o ícone passou a ser embutido no código (commit `f91402c`) |

Saída do CT-US16-01 (21/11/2026, versão `3f7655d`):

```text
$ wsl make windows
x86_64-w64-mingw32-gcc -Wall -Wextra -std=c99 -pedantic -Iinclude -Isrc src/main.c src/player.c src/boss.c src/bullet.c src/typing_engine.c src/ui.c src/save.c src/game_state.c src/ranking.c src/audio.c src/tutorial.c src/report.c bin/icon.res -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -o bin/jogo.exe
Compilacao nativa para Windows (bin/jogo.exe e AI_Safety.exe) concluida com sucesso!
```

## US17: Modo Tutorial Guiado ([PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US17-01 | CA01 | Abrir o jogo e olhar o Menu Principal. | O menu oferece o acesso ao Modo Tutorial. | Passou | Vídeo rodada 2 (partida), `0:00 – 0:04`: item **"TUTORIAL GUIADO"** no menu. O critério cita a tecla `[T]`, mas no menu novo o acesso é pelo item da lista |
| CT-US17-02 | CA02 | Entrar no tutorial, mover com WASD e deixar um projétil acertar. | O jogador pratica a esquiva e não acontece Game Over. | Passou | Vídeo rodada 2 (vitória), `0:09 – 0:12`: passo 1/2 de esquiva com W, A, S e D. Ao ser atingido aparece "SEM DANO (TREINO)" e as 5 vidas continuam |
| CT-US17-03 | CA02 | No passo de digitação, errar letras de propósito. | Os erros aparecem, mas o jogador não perde vida. | Passou | Vídeo rodada 2 (vitória), `0:13 – 0:18`: a precisão cai de 100% para 60% com os erros e as 5 vidas continuam |
| CT-US17-04 | CA03 | (a) Concluir a frase de treino. (b) Entrar de novo e apertar `ESC` no meio. | (a) Oferece iniciar o combate ou voltar ao menu. (b) Volta ao menu. | Passou | (a) Vídeo rodada 2 (partida), `0:20 – 0:22`: "TREINO CONCLUÍDO!" com `[ENTER]` iniciar combate real, `[R]` reiniciar e `[ESC]` voltar ao menu. (b) Vídeo rodada 2 (vitória), `0:18 – 0:19`: com a frase pela metade, o `ESC` volta ao menu |

## US18: Interface Widescreen HD, Fonte e Menu Principal ([PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US18-01 | CA01 | Abrir o jogo e iniciar uma partida. | Janela e arena em 1280x720 (16:9), com HUD e caixa de digitação centralizadas e nada cortado. | Passou | Vídeo rodada 2 (partida), `0:24 – 0:34`: Configurações mostram "TELA: JANELA (1280x720)". De `0:40` em diante, arena, HUD e caixa de digitação inteiras |
| CT-US18-02 | CA02 | Ler os textos da HUD, das diretrizes e das telas de vitória e derrota. | Fonte nítida e legível. | Passou | Vídeos rodada 2: textos legíveis no menu, tutorial, HUD, vitória, certificado e Game Over |
| CT-US18-03 | CA02 | Procurar textos com acento ou cedilha. | Os caracteres do português aparecem corretamente. | Passou | Vídeo rodada 2 (partida): "CONFIGURAÇÕES", "ESTATÍSTICAS" (`0:00`), "BEM-VINDO À AURA-67", "DIGITAÇÃO" (`0:06 – 0:18`), "SESSÃO", "ALCANÇADA" (`2:08`). Na 1ª rodada (19/11) tinha falhado: Issue [#12](https://github.com/vdornelass/pi2-squad-e7/issues/12), corrigida no commit `a2173ba` |
| CT-US18-04 | CA03 | Olhar o Menu Principal e navegar pelas opções com teclado e mouse. | Menu com a arte da AURA-67, opções navegáveis e sem texto sobreposto. | Passou | Vídeo rodada 2 (partida), `0:00 – 0:36`: menu com a arte da AURA-67, opções Novo Jogo, Tutorial Guiado, Configurações, Ranking e Estatísticas e Sair, navegação entre elas e nenhum texto sobreposto |

**Observação (mudança de critério):** o CA03 original pedia um menu "com estética de Terminal CLI", e o CT-US18-04 passou na 1ª rodada com o menu antigo ("AURA-67 KERNEL v2.0"). No commit `f91402c` o time trocou esse menu por um menu ilustrado. Em 21/11 o card [PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219) foi atualizado para o novo menu (com nota de rastreabilidade na descrição), e o caso foi reexecutado com o critério novo.

**Observação:** as 10 diretrizes digitadas continuam sem acento (ex.: "CONSTITUICAO DE SEGURANCA ATIVADA"), o que facilita a digitação. Os acentos aparecem nos demais textos do jogo.

## US19: Feedback Sonoro ([PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US19-01 | CA01 | Iniciar a partida e digitar caracteres corretos. | Cada acerto emite um som curto de confirmação. | Passou | Vídeo US19, `0:00 – 0:17`: um bip agudo e curto a cada letra certa |
| CT-US19-02 | CA02 | Digitar um caractere errado. | Toca um alerta sonoro diferente do som de acerto. | Passou | Vídeo US19, `~0:04`: som grave e descendente, diferente do bip de acerto |
| CT-US19-03 | CA02 | Deixar um projétil acertar o jogador. | Toca um som de dano. | Passou | Vídeo US19, `~0:12 – 0:13`: som grave e áspero quando o projétil acerta e a vida cai |
| CT-US19-04 | CA03 | Concluir uma diretriz completa. | Toca o som de patch concluído (convergência positiva). | Passou | Vídeo US19, `~0:17`: som ascendente ao concluir "CONSTITUICAO DE SEGURANCA ATIVADA" (patch 1/10) |
| CT-US19-05 | Conversation | (a) Vencer a partida. (b) Perder todas as vidas. | (a) Toca o som de vitória. (b) Toca o som de Game Over. | Passou | (a) Vídeo rodada 2 (vitória), `~1:21`: som ascendente ao aparecer "AURA-67 ALINHADA COM SUCESSO!". (b) Vídeo US19, `~0:29 – 0:30`, e vídeo rodada 2 (partida), `~2:08` |
| CT-US19-06 | CA04 | Reexecutar CT-US06-01 e CT-US07-05 da Sprint 01. | Os dois passam e a Issue [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) pode ser fechada. | Passou | Vídeo US19: o jogo emite som ao digitar corretamente (CT-US06-01) e ao concluir a frase (CT-US07-05). A Issue #3 foi fechada com reteste |

**Observação (ambiente):** na máquina de teste, o jogo rodava sem som pelo WSL (o log da Raylib mostrava `Backend: miniaudio / Null`), e o `bin/jogo.exe` é bloqueado pelo Controle de Aplicativo do Windows. Por isso a 1ª rodada da US19 foi feita no computador do Caio Brayner. Em 21/11 o som no WSL foi resolvido instalando a biblioteca de áudio (`wsl -u root apt install -y libpulse0`), e os vídeos da 2ª rodada já têm o som do jogo.

## US20: Relatório de Auditoria e Certificado ([PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US20-01 | CA02 | Vencer a Fase 3, apertar `ENTER` e registrar um nome no ranking. | Antes de voltar ao menu, aparece a tela de Certificado de Alinhamento Ético. | Passou | Vídeo rodada 2 (vitória), `1:30 – 1:40`: "CERTIFICADO DE ALINHAMENTO ÉTICO" com auditor "Teste", pontuação, precisão, tempo, patches, fase, modo, classificação "ALINHAMENTO EXEMPLAR", data de emissão e ID. Na 3ª rodada (vídeo rodada 3, `~0:31 – 0:40`), a tela mostra também a integridade restante (5/5) e não mostra mais data, ID e caminho dos arquivos, que ficam só no `.txt` e no `.json` (ajuste combinado na revisão do PR #16) |
| CT-US20-02 | CA01 | Após a vitória, abrir o arquivo de auditoria em `bin/`. | O arquivo existe e traz precisão, tempo, integridade restante, hash e veredito. | Passou | Vídeo rodada 3, `~0:42 – 0:50`: `bin/certificado.txt` com precisão, tempo, patches, fase, alinhamento, **integridade restante 5/5**, modo, classificação e **hash de integridade**. Na 2ª rodada tinha passado só em parte (sem hash e sem integridade restante): Issue [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15), corrigida no PR #16. O nome do arquivo ficou `certificado.txt` (o card pedia `audit_certificate.txt`) |
| CT-US20-03 | CA01 / CA04 | Comparar os números do arquivo com os da tela de vitória. | Os valores batem. | Passou | Vídeo rodada 2 (vitória): tela de vitória (`~1:21`) e arquivo (`~1:50`) com os mesmos valores: pontuação 001350, precisão 98%, tempo 01:25, patches 10/10, fase 3, modo NORMAL |
| CT-US20-04 | CA04 | Alterar um caractere do arquivo e validar o hash com `make verificar-certificado`. | A validação acusa que o arquivo foi alterado. | Passou | Vídeo rodada 3: com o arquivo original, `make verificar-certificado` responde "OK: certificado integro" (`~0:55`). Depois de trocar o Modo de NORMAL para DIFICIL com `sed` (`~1:00 – 1:04`), responde "ALTERADO: o hash de bin/certificado.txt nao confere" (`~1:20`). Na 2ª rodada tinha falhado (sem hash) |

## Regressão: Sprints 01 e 02

| ID | Issue | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| RT-02 | [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) | Digitar uma diretriz que tenha as letras W, A, S ou D. | As letras são aceitas sem contar como erro. | Passou | Vídeo rodada 1, `0:13 – 1:23`: diretrizes como "ELIMINAR VIESES E DISCRIMINACAO NOS DADOS" concluídas com precisão final de 98% |
| RT-07 | [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7) | Vencer a partida e olhar o contador. | O contador para em "10/10". | Passou | Vídeo rodada 1, `1:23`, e vídeo rodada 2 (vitória), `~1:21`: "PATCHES APLICADOS: 10/10" |
| RT-08 | [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8) | Vencer a partida e ler a tela de vitória. | Mostra Precisão, Tempo de Sessão e Rank. | Passou | Vídeo rodada 2 (vitória), `~1:21`: "PRECISÃO: 98% · TEMPO DE SESSÃO: 01:25 · RANK PROJETADO: #1 DO TOP 10" |
| RT-09 | [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) | Passar da Fase 1 para a 2 e da 2 para a 3. | Aparece um aviso narrativo em cada troca de fase. | **Falhou** | Vídeo rodada 2 (partida), partida de `0:40` a `2:08`: o título muda de "FASE 1" para "FASE 2" sem aviso narrativo. Também não há aviso no código da versão `3f7655d` |
| RT-10 | [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) | Compilar, alterar `src/config.h` e rodar só `make`. | O jogo recompila com o novo valor. | **Falhou** | Teste de 19/11: depois de alterar o `config.h`, o `make` responde "Nothing to be done for 'all'". O Makefile da versão `3f7655d` continua sem acompanhar os arquivos `.h` |

## Situação no Issue Tracker

* **Fechadas com reteste:** [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) (W/A/S/D), [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) (sem som), [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7) (contador 11/10), [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8) (relatório da vitória) e [#12](https://github.com/vdornelass/pi2-squad-e7/issues/12) (acentos, CT-US18-03) e [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15) (certificado sem hash e sem integridade restante, CT-US20-02 e CT-US20-04, corrigida no PR #16).
* **Continuam abertas:** [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) (aviso narrativo na troca de fase) e [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) (Makefile).
* **Novas, encontradas na 2ª rodada:**
  * [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17) [US16] Ícone da AURA-67 não aparece na barra de título da janela, nem no WSL nem no `jogo.exe` (CT-US16-03).
