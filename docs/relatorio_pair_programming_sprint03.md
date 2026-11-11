# Relatório de Programação em Pares (*Pair Programming*) — Sprint 03 / Entrega 05
## Projeto: AI Safety — Alinhamento Ético da AURA-67
### Squad E7 | CESAR School — Projeto Integrador 2 (PI2)

> **Sprint de referência:** Sprint 03 - U2 (`Week 15 e 16` — ID 116 no Jira, 09/11/2026 a 23/11/2026)
> **Card:** [PI2-242](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-242) (subtarefa de [PI2-240 — Sustentabilidade](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-240))
> **Responsável pela consolidação:** Theo Monteiro Pinho
> **Padrão exigido:** Quem · Onde · Quando · O quê · E daí

---

## 1. Resumo das duplas (Quem)

Duplas montadas a partir dos responsáveis pelos cards do Sprint 03 no Jira.

| Dupla | Integrantes | Foco | Cards no Jira |
| :---: | :--- | :--- | :--- |
| **Dupla 1** | **João Gabriel** & **Caio Brayner** | Motor em C — identidade visual, áudio, certificado e execução no Windows | `PI2-217` (US16), `PI2-221`, `PI2-220` (US19), `PI2-246` (US20), `PI2-247`, `PI2-254` |
| **Dupla 2** | **Matheus Chaves** & **Julio Cesar** | Interface (IHC) — tutorial, widescreen e comprovação de usabilidade | `PI2-218` (US17), `PI2-215`, `PI2-219` (US18), `PI2-216`, `PI2-248`, `PI2-249`, `PI2-250`, `PI2-251`, `PI2-252`, `PI2-253` |
| **Dupla 3** | **Theo Monteiro** & **Larissa Almeida** | Qualidade (FDS/LMC) — validação lógica, testes finais e produto em produção | `PI2-31` (LMC), `PI2-235`, `PI2-236`, `PI2-237`, `PI2-238`, `PI2-239` |
| **Facilitação** | **Mateus Lacerda** | Scrum Master — board, sustentabilidade e apresentação final | `PI2-233`, `PI2-234`, `PI2-240`, `PI2-241`, `PI2-243` |

> **Jhorge Araújo** não teve card próprio no Sprint 03 e atuou como consultor de arquitetura e lógica, revisando as regras do relatório LMC da Dupla 3.

---

## 2. Detalhamento por dupla

### 2.1. Dupla 1 — João Gabriel & Caio Brayner

| Pergunta | Resposta |
| :--- | :--- |
| **Quem** | João Gabriel e Caio Brayner. Sessão 1: João (driver) e Caio (navigator). Sessão 2: Caio (driver) e João (navigator). |
| **Onde** | Discord com VS Code Live Share |
| **Quando** | Terças e sextas, das 19h às 21h (2h por sessão) |
| **O quê** | Ícone oficial do jogo no `.exe` e na janela (US16 · `PI2-221`); sistema de áudio sintetizado (US19 · commit [`6a8a9d4`](https://github.com/vdornelass/pi2-squad-e7/commit/6a8a9d4), 06/11); relatório e certificado pós-vitória em C (US20 · `PI2-247`); ajuste do `jogar.bat` para rodar em qualquer PC (`PI2-254`). |
| **E daí?** | Gerar o `.exe` do Windows a partir do Linux mostrou que o build depende do ambiente de cada um. Com o navigator acompanhando, a dupla percebeu cedo que o `jogar.bat` só funcionava com WSL e que a release precisa levar o `.exe` já compilado. |

### 2.2. Dupla 2 — Matheus Chaves & Julio Cesar

| Pergunta | Resposta |
| :--- | :--- |
| **Quem** | Matheus Chaves e Julio Cesar. Sessão 1: Matheus (driver) e Julio (navigator), na interface widescreen. Sessão 2: Julio (driver) e Matheus (navigator), no tutorial. |
| **Onde** | Discord, com compartilhamento de tela |
| **Quando** | Quartas e sábados, das 14h às 16h (2h por sessão) |
| **O quê** | Modo Tutorial Guiado (US17 · `PI2-215`, marcado como concluído no Jira, mas ⚠️ o código ainda não está na `main`); tela widescreen 1280×720 e menu estilo terminal (US18 · commit [`a9c8bb4`](https://github.com/vdornelass/pi2-squad-e7/commit/a9c8bb4), 06/11); screencast e relatório de usabilidade (`PI2-249`, `PI2-250`); auditoria visual das telas (`PI2-252`, `PI2-253`). |
| **E daí?** | Mudar a resolução para 1280×720 mexeu em margens, fontes e no menu ao mesmo tempo. Com duas pessoas olhando, os desalinhamentos apareceram na hora, e a lista de telas para revisar (do menu à vitória) virou a base da auditoria visual. |

### 2.3. Dupla 3 — Theo Monteiro & Larissa Almeida

| Pergunta | Resposta |
| :--- | :--- |
| **Quem** | Theo Monteiro (driver na validação LMC) e Larissa Almeida (driver nos testes de sistema). Na validação LMC, Julio Cesar e João Gabriel atuaram como consultores (navigators). |
| **Onde** | Presencial no CESAR School (Recife Antigo) e Discord |
| **Quando** | Segundas e quartas, das 18h30 às 21h (2h30 por sessão) |
| **O quê** | Relatório de validação lógica da Unidade 2 ([`docs/relatorio_lmc_unidade2.md`](./relatorio_lmc_unidade2.md)) com 181 verificações automatizadas (`make test-lmc`) e 4 achados registrados para o time (`PI2-31`); suíte final de testes de sistema e atualização do bug tracker (`PI2-238`, `PI2-239`); empacotamento da release final (`PI2-236`). |
| **E daí?** | Escrever testes automáticos contra o código real mostrou diferenças entre o que estava descrito no Jira (estados S0/S1/S2, arquivo `patch.c`, limiar de 80%) e o que o jogo realmente faz. O olhar de outra pessoa ajuda a não validar só "o que achamos que o código faz". |

### 2.4. Facilitação — Mateus Lacerda

| Pergunta | Resposta |
| :--- | :--- |
| **O quê** | Consolidação das histórias do Sprint 03 no board (`PI2-234`), auditoria de commits e `CONTRIBUTING.md` (`PI2-241`), estrutura da apresentação final (`PI2-243`). |
| **Quando / Onde** | Planejamento na abertura do sprint (09/11) e alinhamentos rápidos no Discord ao longo da semana |

---

## 3. Rastreabilidade de commits por dupla

| Dupla | Arquivos principais | Commits |
| :--- | :--- | :--- |
| Dupla 1 — João & Caio | `src/audio.c/h`, `src/boss.c`, `src/bullet.c`, `jogar.bat`, `Makefile` | [`6a8a9d4`](https://github.com/vdornelass/pi2-squad-e7/commit/6a8a9d4), [`f4c9023`](https://github.com/vdornelass/pi2-squad-e7/commit/f4c9023) |
| Dupla 2 — Matheus & Julio | `src/config.h`, `src/main.c`, `src/ui.c` | [`a9c8bb4`](https://github.com/vdornelass/pi2-squad-e7/commit/a9c8bb4) |
| Dupla 3 — Theo & Larissa | `docs/relatorio_lmc_unidade2.md`, `tests/test_logica_lmc.c`, `docs/casos_de_teste_*.md`, `README.md` | [`aedc993`](https://github.com/theo1996-dot/pi2-squad-e7/commit/aedc993) |
| Mateus Lacerda | `README.md`, `CONTRIBUTING.md` | Board do Jira (cards `PI2-233` a `PI2-245`) |

---

## 4. Reflexão do time (E daí, geral)

A programação em pares ajudou principalmente a achar problemas antes de chegarem à `main`: desalinhamentos de tela, dependência do WSL no build do Windows e diferenças entre o que os cards descreviam e o que o código fazia. O que faríamos diferente: integrar na `main` com mais frequência, porque código parado em máquina local atrasou a release e deixou cards marcados como concluídos sem estar no repositório. No fim, o grupo funcionou como time: cada dupla sabia o que a outra estava fazendo pelo board, e a revisão cruzada virou parte do processo.
