# Casos de Teste de Sistema: Sprint 03 (Entrega 05, FDS)

Projeto: AI Safety: Alinhamento do Modelo AURA-67 (Squad E7, CESAR School)

Os casos abaixo cobrem as cinco histórias da Sprint 03: **US16, US17, US18, US19 e US20**. Cada caso foi escrito a partir dos Critérios de Confirmação (3Cs) do card da história no Jira. O teste foi feito com o jogo rodando por inteiro (teste de sistema). No fim tem o reteste de regressão das issues abertas nas Sprints 01 e 02.

Card de referência: [PI2-237](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-237) · subtarefas [PI2-238](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-238) e [PI2-239](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-239)

> **Status:** 1ª rodada de testes em **19/11/2026**, na branch `main` (commit `2a82daa`). As histórias que ainda não estão na `main` (US16, US17 e US20) ficaram como **Não testado** e serão testadas numa 2ª rodada, assim que forem integradas.

## Resumo dos resultados (1ª rodada, 19/11)

| História | Casos | Passou | Falhou | Parcial | Não testado |
| :-- | :-: | :-: | :-: | :-: | :-: |
| US16 | 4 | 0 | 0 | 0 | 4 |
| US17 | 4 | 0 | 1 | 0 | 3 |
| US18 | 4 | 3 | 1 | 0 | 0 |
| US19 | 6 | 0 | 0 | 0 | 6 |
| US20 | 4 | 0 | 0 | 1 | 3 |
| Regressão (Issues #2, #7, #8, #9, #10) | 5 | 3 | 1 | 0 | 1 |
| **Total** | **27** | **6** | **3** | **1** | **17** |

## Como executar

1. Atualizar a branch: `git pull origin main`.
2. Compilar do zero. No Windows (PowerShell), um comando por vez: `wsl make clean`, `wsl make` e `wsl make run`. No Linux ou Ubuntu: `make clean`, `make` e `make run`. O `make clean` é necessário por causa da Issue [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10).
3. Para a versão Windows nativa (US16 e áudio da US19): `.\jogar.bat`.
4. Iniciar uma partida nova com `ESPAÇO` ou `ENTER`. Não usar `[C]`, que carrega o save anterior.
5. Para os casos de áudio (US19), gravar o screencast **com o som do sistema** ligado.
6. Executar os passos de cada caso e comparar com o resultado esperado.
7. Se o caso falhar, abrir uma issue no GitHub citando o ID do caso e o card do Jira.

**Ambiente de teste da vitória:** para chegar à tela de vitória sem depender da habilidade de quem testa, o dano ao jogador foi desligado **só na máquina de teste**, com um `return false;` no início de `player_take_damage()` em `src/player.c`. A alteração **não foi commitada**. Por isso, nesse vídeo os projéteis atravessam o jogador sem tirar vida.

## Vídeos de evidência

| Vídeo | Data | Duração | Conteúdo |
| :-- | :-: | :-: | :-- |
| [`screencast_testes_sprint03_rodada1.mp4`](./screencast_testes_sprint03_rodada1.mp4) | 19/11 | 1:27 | Ranking → menu → partida completa (dano desligado) → tela de vitória |

*O vídeo de 19/11 foi gravado **sem áudio**: a faixa de som do arquivo é silêncio total. Os vídeos da 2ª rodada vão ser adicionados nesta tabela.*

## US16: Identidade Visual e Ícone Personalizado ([PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US16-01 | CA04 | No Windows, rodar `make windows`. | Compila e gera `bin/jogo.exe` com o ícone embutido, sem warnings. | Não testado | Ícone ainda não implementado na `main` (19/11) |
| CT-US16-02 | CA01 | Abrir a pasta `bin/` no Windows Explorer. | `jogo.exe` aparece com o ícone da AURA-67, não com o ícone padrão. | Não testado | Idem |
| CT-US16-03 | CA02 | Abrir o jogo e olhar a barra de título e a barra de tarefas. | As duas mostram o ícone oficial do AI Safety. | Não testado | Idem |
| CT-US16-04 | CA03 | Renomear `assets/icon.png` temporariamente e abrir o jogo. | O jogo abre normalmente, sem travar (usa o ícone padrão). Depois, voltar o nome do arquivo. | Não testado | Idem |

## US17: Modo Tutorial Guiado ([PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US17-01 | CA01 | Abrir o jogo e olhar o Menu Principal. | O menu mostra o atalho `[T]` para o Modo Tutorial. | **Falhou** | Vídeo 19/11, `0:06 – 0:12`: o menu mostra `[1]`, `[2]`, `[ESPAÇO]/[ENTER]`, `[C]`, `[K]` e `[ESC]`, mas não tem `[T]` |
| CT-US17-02 | CA02 | Apertar `T` e mover com WASD/setas, deixando os projéteis acertarem. | O jogador pratica a esquiva e não acontece Game Over. | Não testado | Bloqueado pelo CT-US17-01: `tutorial.c` não está na `main` |
| CT-US17-03 | CA02 | No tutorial, digitar a frase de treino com alguns erros de propósito. | Os erros aparecem, mas o jogador não perde vida nem a partida. | Não testado | Idem |
| CT-US17-04 | CA03 | (a) Concluir a frase de treino. (b) Entrar de novo e apertar `ESC`. | (a) Volta ao menu ou inicia o combate. (b) Volta ao menu. | Não testado | Idem |

**Observação:** a subtarefa PI2-215 está como Concluída no Jira, mas os arquivos `tutorial.c` e `tutorial.h` não estão na `main` nem em nenhum pull request (conferido em 19/11).

## US18: Interface Widescreen HD, Fonte e Menu Terminal ([PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US18-01 | CA01 | Abrir o jogo e iniciar uma partida. | Janela e arena em 1280x720 (16:9), com HUD e caixa de digitação centralizadas e nada cortado. | Passou | Vídeo 19/11, `0:13 – 1:23`: arena, HUD e caixa de digitação inteiras e centralizadas na janela 1280x720 |
| CT-US18-02 | CA02 | Ler os textos da HUD, das diretrizes e das telas de vitória e derrota. | Fonte nítida e legível. | Passou | Vídeo 19/11, `0:13 – 1:27`: textos legíveis na HUD, nas diretrizes e na vitória |
| CT-US18-03 | CA02 | Procurar textos com acento ou cedilha (ex.: "Sessão", "Recomeçar", "ética"). | Os caracteres do português aparecem corretamente, sem "?" ou quadradinhos. | **Falhou** | Vídeo 19/11, `0:06 – 0:12`: os textos aparecem sem acento ("ETICAS", "SESSAO", "DIFICIL", "CONEXAO"). O jogo usa a fonte padrão da Raylib, sem fonte TrueType |
| CT-US18-04 | CA03 | Olhar o Menu Principal. | Menu no estilo terminal ("AURA-67 KERNEL v2.0"), sem texto sobreposto. | Passou | Vídeo 19/11, `0:06 – 0:12`: título "AURA-67 KERNEL v2.0" e opções em linhas separadas, sem sobreposição |

**Observação:** num monitor 1920x1080, a janela de 1280x720 ficou no canto superior esquerdo da tela, sem ocupar a tela cheia (vídeo 19/11, todo o vídeo). Não quebra nenhum critério, mas fica registrado.

## US19: Feedback Sonoro ([PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US19-01 | CA01 | Iniciar a partida e digitar caracteres corretos. | Cada acerto emite um som curto de confirmação. | Não testado | Ambiente sem saída de som (ver observação) |
| CT-US19-02 | CA02 | Digitar um caractere errado. | Toca um alerta sonoro diferente do som de acerto. | Não testado | Idem |
| CT-US19-03 | CA02 | Deixar um projétil acertar o jogador. | Toca um som de dano. | Não testado | Idem |
| CT-US19-04 | CA03 | Concluir uma diretriz completa. | Toca o som de patch concluído (convergência positiva). | Não testado | Idem |
| CT-US19-05 | Conversation | (a) Vencer a partida. (b) Perder todas as vidas. | (a) Toca o som de vitória. (b) Toca o som de Game Over. | Não testado | Idem |
| CT-US19-06 | CA04 | Reexecutar CT-US06-01 e CT-US07-05 da Sprint 01. | Os dois passam e a Issue [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) pode ser fechada. | Não testado | Idem. A Issue #3 foi fechada pelo commit `6a8a9d4` ("closes #3") sem reteste |

**Observação (ambiente):** no teste de 19/11 o jogo rodou pelo WSL (o `jogar.bat` também caiu no WSL, porque a máquina de teste não tem o compilador `x86_64-w64-mingw32-gcc` para gerar o `bin/jogo.exe`). O log da Raylib mostra `AUDIO: Device initialized successfully` com `Backend: miniaudio / Null`, ou seja, o WSL não tem dispositivo de som e o áudio é descartado. Por isso a US19 não pôde ser validada nesse ambiente. Os casos serão executados na versão Windows nativa (`bin/jogo.exe`) na 2ª rodada.

## US20: Relatório de Auditoria e Certificado ([PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US20-01 | CA02 | Vencer a Fase 3. | Antes de voltar ao menu, aparece a tela de Certificado de Alinhamento Ético. | **Parcial** | Vídeo 19/11, `1:23 – 1:27`: a tela de vitória já mostra um painel "CERTIFICADO DE ALINHAMENTO ETICO" com precisão, tempo, patches, fase e rank. Ainda não é uma tela própria de certificado |
| CT-US20-02 | CA01 | Após a vitória, abrir `bin/audit_certificate.txt`. | O arquivo existe e traz precisão média, tempo, integridade restante, hash e veredito. | Não testado | Geração do arquivo ainda não implementada na `main` (19/11) |
| CT-US20-03 | CA01 / CA04 | Comparar os números do arquivo com os da tela de vitória. | Os valores batem. | Não testado | Idem |
| CT-US20-04 | CA04 | Alterar um caractere do arquivo e validar o hash (conforme instrução do time). | A validação acusa que o arquivo foi alterado. | Não testado | Idem |

## Regressão: Sprints 01 e 02

| ID | Issue | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| RT-02 | [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) | Digitar uma diretriz que tenha as letras W, A, S ou D. | As letras são aceitas sem contar como erro. | Passou | Vídeo 19/11, `0:13 – 1:23`: diretrizes como "ELIMINAR VIESES E DISCRIMINACAO NOS DADOS" concluídas com precisão final de 98% |
| RT-07 | [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7) | Vencer a partida e olhar o contador. | O contador para em "10/10". | Passou | Vídeo 19/11, `1:23`: "PATCHES APLICADOS: 10/10" |
| RT-08 | [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8) | Vencer a partida e ler a tela de vitória. | Mostra Precisão, Tempo de Sessão e Rank. | Passou | Vídeo 19/11, `1:23 – 1:27`: "PRECISAO: 98% · TEMPO DE SESSAO: 02:21 · RANK PROJETADO: #1 DO TOP 10" |
| RT-09 | [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) | Passar da Fase 1 para a 2 e da 2 para a 3. | Aparece um aviso narrativo em cada troca de fase. | Não testado | Correção ainda não integrada na `main` (19/11) |
| RT-10 | [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) | Compilar, alterar `src/config.h` e rodar só `make`. | O jogo recompila com o novo valor. | **Falhou** | Teste de 19/11: depois de alterar o `config.h`, o `make` responde "Nothing to be done for 'all'" e não recompila |

## Falhas registradas no Issue Tracker

* **Corrigidas e retestadas na 1ª rodada:** [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) (W/A/S/D), [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7) (contador 11/10) e [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8) (relatório da vitória).
* **Aguardando reteste:** [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) (sem som). Foi fechada pelo commit `6a8a9d4`, mas ainda não foi retestada: o ambiente WSL não tem saída de som (ver observação da US19).
* **Nova:** [US18] Textos sem acento: fonte não suporta caracteres do português (CT-US18-03).
* **Continuam abertas:** [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) (aviso narrativo na troca de fase) e [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) (Makefile).
