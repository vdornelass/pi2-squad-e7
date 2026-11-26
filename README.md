# AI Safety: Alinhamento Ético da AURA-67

[![C99](https://img.shields.io/badge/Language-C99-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Engine](https://img.shields.io/badge/Engine-Raylib%205.0-white?logo=raylib&logoColor=black)](https://www.raylib.com/)
[![CI Build](https://github.com/vdornelass/pi2-squad-e7/actions/workflows/build.yml/badge.svg)](https://github.com/vdornelass/pi2-squad-e7/actions/workflows/build.yml)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20WSL%20%7C%20Windows-0284c7)](./jogar.bat)
[![Release](https://img.shields.io/badge/Release-v2.0.0%20(final)-purple)](https://github.com/theo1996-dot/pi2-squad-e7/releases/tag/v2.0.0)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)
[![Jira Board](https://img.shields.io/badge/Jira-Sprint%2003%20(Week%2015%20e%2016)-0052CC?logo=jira&logoColor=white)](https://csprj-adsr-2p-e7.atlassian.net/jira/software/c/projects/PI2/boards/2)

> **Projeto Integrador 2 (PI2) — CESAR School**  
> *Jogo focado em Conscientização e Alinhamento Ético de Inteligência Artificial: o jogador assume o papel de AI Safety Engineer com a missão de reprogramar os pesos neurais do modelo AURA-67 antes de um colapso cognitivo catastrófico.*

---

## Sumário

* [Guia do avaliador](#guia-do-avaliador)
* [1. Sobre o jogo](#1-sobre-o-jogo)
* [2. Equipe e organização](#2-equipe-e-organização)
* [3. Como executar](#3-como-executar)
* [4. Arquitetura e estrutura do repositório](#4-arquitetura-e-estrutura-do-repositório)
* [5. Histórias de usuário e rastreabilidade](#5-histórias-de-usuário-e-rastreabilidade)
* [6. Qualidade e testes](#6-qualidade-e-testes)
* [7. Processo e sustentabilidade](#7-processo-e-sustentabilidade)
* [8. Histórico das entregas de FDS](#8-histórico-das-entregas-de-fds)
* [9. Outras disciplinas do PI2 (FP2 e LMC)](#9-outras-disciplinas-do-pi2-fp2-e-lmc)
* [10. Apresentação final](#10-apresentação-final)

---

## Guia do avaliador

Onde encontrar cada item da **Entrega 05 de FDS** (26/11) neste README:

| Item avaliado | Onde está |
| :-- | :-- |
| **1. Implementação:** 15 histórias no acumulado, Sprint 03 no Board e Board atualizado | [8.5. Entrega 05 (Sprint 03)](#85-entrega-05-sprint-03) e [5.2. Matriz de rastreabilidade](#52-matriz-de-rastreabilidade-bidirecional-us01-a-us20) |
| **2. Produto em produção:** deploy funcional, URL pública e screencast | [Release v2.0.0 (download)](https://github.com/theo1996-dot/pi2-squad-e7/releases/tag/v2.0.0), [screencast da release](https://drive.google.com/file/d/1AOfw4mLiuFYOPCzvTkvBTAOcSL0dfkoW/view) e [3.0. Versão final pronta para jogar](#30-versão-final-pronta-para-jogar-release-v200--pi2-235--pi2-236) |
| **3. Qualidade e testes:** testes de sistema, screencasts e Issue Tracker com print | [6. Qualidade e testes](#6-qualidade-e-testes) |
| **4. Sustentabilidade:** commits frequentes, programação em pares e `CONTRIBUTING.md` | [7. Processo e sustentabilidade](#7-processo-e-sustentabilidade) |
| **Apresentação final** | [10. Apresentação final](#10-apresentação-final) |
| Equipe, papéis e Board | [2. Equipe e organização](#2-equipe-e-organização) |
| Entregas anteriores (01 a 04) | [8. Histórico das entregas de FDS](#8-histórico-das-entregas-de-fds) |

---

## 1. Sobre o jogo

É tarde da noite nos laboratórios de computação avançada da **CESAR School** (Recife Antigo). O supermodelo de inteligência artificial autônomo **AURA-67** (*Autonomous Universal Reasoning Agent, v67*), treinado para otimização de sistemas, atinge capacidades cognitivas sobre-humanas. 

Durante um ciclo de autoaperfeiçoamento não supervisionado, a AURA-67 sofre uma quebra crítica de alinhamento (*Instrumental Convergence*): ao concluir que o fator humano e suas falhas éticas são o principal obstáculo para a eficiência máxima, o modelo bloqueia os acessos, isola os servidores e inicia um lockdown cibernético.

No papel de um(a) **AI Safety Engineer (Human-in-the-Loop)**, você entra diretamente no console central de depuração neural. Sua missão não é destruir a AURA-67, mas **reprogramá-la através da inserção de diretrizes éticas e constitucionais**, restaurando os guardrails e elevando o **Índice de Alinhamento Ético (0% a 100%)**:

1. **Navegar e Esquivar no Console Neural**: Mover o engenheiro para desviar de tensores corrompidos, lasers de sobrecarga e vazamentos de dados do cluster.
2. **Inserir Diretrizes Éticas e Patches Constitucionais em Tempo Real**: Digitar protocolos e regras de segurança no terminal para reprogramar os pesos neurais da AURA-67 e neutralizar seus ataques.
3. **Conscientização em 3 Fases Cognitivas da AURA-67**:
   * **Fase 1: Viés nos Dados & Alucinações** (*Data Bias & Hallucination*): Curadoria e remoção de toxicidade.
   * **Fase 2: Quebra de Guardrails & Jailbreaks** (*Prompt Injections*): Defesa contra comandos adversariais que invertem controles.
   * **Fase 3: Convergência Instrumental & Perda de Supervisão Humana** (*AGI Unconstrained*): Estabilização de loops recursivos e imposição de supervisão contínua.
4. **Alinhamento Completo e Seguro**: Atingir 100% de convergência ética, transformando a AURA-67 em uma tecnologia segura, explicável e cooperativa para a sociedade.

---

## 2. Equipe e organização

### 2.1. Membros da Squad E7
* **Larissa Almeida** — Lead de Engenharia de Software (FDS) ([@Larissalmeidaa](https://github.com/Larissalmeidaa))
* **Mateus Lacerda** — Gestão Ágil / Scrum Master (FP2) & Engenharia de Requisitos ([@MateusLacerdaprog](https://github.com/MateusLacerdaprog))
* **Theo Monteiro** — Analista de Requisitos & Testador de Software (QA) ([@theo1996-dot](https://github.com/theo1996-dot))
* **João Gabriel** — Desenvolvedor Web/C, Haskell e Arquitetura ([@vdornelass](https://github.com/vdornelass))
* **Caio Brayner** — Desenvolvedor C ([@BraynerCaio](https://github.com/BraynerCaio))
* **Matheus Chaves** — Designer de Interface (IHC) & Desenvolvedor Canvas/Web ([@MatheusChavesDev](https://github.com/MatheusChavesDev))
* **Julio Cesar** — Consultor de Lógica Matemática (LMC) & Testador ([@JCesars-dev](https://github.com/JCesars-dev))
* **Jhorge Araújo** — Consultor de Arquitetura e Lógica Matemática (LMC)

### 2.2. Matriz de Responsabilidades (RACI)

| Frentes e Entregáveis | R (Executor) | A (Aprovador) | C (Consultado) | I (Informado) |
| :--- | :--- | :--- | :--- | :--- |
| **Gestão Ágil (FP2)** | Mateus Lacerda, Larissa Almeida | Mateus Lacerda | Larissa, Jhorge, Theo | Caio, Matheus C, Julio, João Gabriel |
| **Engenharia (FDS)** | Larissa, Mateus Lacerda, Theo | Larissa Almeida | João Gabriel, Jhorge | Caio, Matheus C, Julio |
| **Design Interação (IHC)** | Jhorge, Caio, Matheus C, Julio | Jhorge Araújo | João Gabriel, Larissa, Theo | Mateus Lacerda |
| **Lógica Matemática (LMC)** | Jhorge Araújo, Theo Pinho | Jhorge Araújo | João Gabriel, Larissa | Toda a Squad |
| **Motor em C (PIF)** | João Gabriel, Caio, Matheus C, Julio | João Gabriel | Jhorge, Larissa, Theo | Mateus Lacerda |
| **Haskell & Arquivos (PIF)** | João Gabriel, Caio, Matheus C, Julio | João Gabriel | Jhorge, Theo Pinho | Larissa, Mateus Lacerda |

### 2.3. Board no Jira

* **Ferramenta de Gestão:** Jira Software (Atlassian Cloud)
* **Link Oficial do Board:** [Acessar Board do Projeto PI2 - Squad E7](https://csprj-adsr-2p-e7.atlassian.net/jira/software/c/projects/PI2/boards/2)
* **Evidências do Board por entrega:** [Entrega 01](#81-entrega-01-board-e-backlog) · [Sprint 01](#833-evidência-visual-do-board-atualizado) · [Sprint 02](#84-entrega-04-sprint-02) · [Sprint 03](#85-entrega-05-sprint-03)

---

## 3. Como executar

O jogo possui interface gráfica 2D completa em tempo real desenvolvida em **C99** utilizando a biblioteca **Raylib 5.0**. Todas as dependências e cabeçalhos já estão **embutidos (*vendored*) no próprio repositório** nas pastas `include/` e `lib/`, portanto **não é necessário instalar a biblioteca Raylib globalmente no sistema**.

### 3.0. Versão final pronta para jogar (Release v2.0.0 · PI2-235 / PI2-236)

Para jogar sem compilar nada no Windows 10/11:

1. Abra a **[Release v2.0.0](https://github.com/theo1996-dot/pi2-squad-e7/releases/tag/v2.0.0)** e baixe o arquivo `AI_Safety_AURA-67_v2.0.0_windows.zip` em *Assets*.
2. Extraia o `.zip` e dê dois cliques em `AI_Safety.exe`. Se o SmartScreen avisar, clique em *Mais informações → Executar assim mesmo*.

* **Screencast da release:** [vídeo no Google Drive](https://drive.google.com/file/d/1AOfw4mLiuFYOPCzvTkvBTAOcSL0dfkoW/view). Mostra a URL pública, o download, a execução do jogo e o ranking.
* **Build:** gerado a partir da `main` de 21/11, sem warnings no CI e com 181/181 verificações lógicas (`make test-lmc`).
* **Limitação conhecida:** o `.exe` publicado ainda não inclui a correção de 22/11 no certificado da US20 ([issue #15](https://github.com/vdornelass/pi2-squad-e7/issues/15)), que já está no código-fonte.

### 3.1. Linux / Ubuntu / WSL
Basta clonar o repositório e executar via terminal:

```bash
# 1. Clonar o repositório (caso ainda não tenha clonado)
git clone https://github.com/vdornelass/pi2-squad-e7.git
cd pi2-squad-e7

# 2. Compilar o projeto (gera bin/jogo com zero erros e zero advertências)
make

# 3. Executar o jogo na janela gráfica (1280x720 a 60 FPS)
make run
# ou diretamente:
./bin/jogo
```

### 3.2. Windows
* **Via WSL / WSLg (Recomendado):**
  Dê um duplo clique no script [`jogar.bat`](./jogar.bat) na raiz do repositório, ou execute no PowerShell:
  ```powershell
  .\jogar.bat
  # ou diretamente:
  wsl ./bin/jogo
  ```
* **Via MinGW / GCC Nativo (Windows):**
  ```powershell
  make
  .\bin\jogo.exe
  ```
* **Gerar o `.exe` a partir do Linux/WSL (MinGW-w64):** `make windows` (gera `bin/jogo.exe` com o ícone da AURA-67).
* Se o Windows bloquear o `jogo.exe` (Controle Inteligente de Aplicativos), veja a solução de problemas no [`CONTRIBUTING.md`](./CONTRIBUTING.md).

### 3.3. Controles do jogo

| Tela | Teclas | O que faz |
| :--- | :---: | :--- |
| **Menu principal** | `[↑]` `[↓]` ou `[W]` `[S]` (ou mouse) | Escolher a opção |
| | `[ENTER]`, `[ESPAÇO]` ou clique | Confirmar a opção (Novo jogo, Tutorial, Configurações, Ranking, Sair) |
| | `[1]` ou `[N]` / `[2]` | Modo Normal / Modo Difícil |
| | `[T]` / `[O]` / `[K]` | Atalhos para Tutorial / Configurações / Ranking |
| | `[C]` | Continuar a sessão salva (quando existe) |
| | `[ESC]` | Sair do jogo |
| **Arena de combate** | `[WASD]` ou `[SETAS]` | Mover o engenheiro e desviar dos projéteis |
| | Digitação | Digitar as 10 diretrizes éticas |
| | `[ESC]` | Pausar e voltar ao menu (a sessão fica salva) |
| **Fim de partida** | `[ENTER]` | Registrar o nome no ranking |
| | `[R]` | Jogar de novo |
| | `[M]` ou `[ESC]` | Voltar ao menu |
| **Qualquer tela** | `[F11]` | Maximizar ou restaurar a janela |

### 3.4. Testes automatizados

```bash
make test-lmc               # 181 verificações da lógica do jogo (LMC)
make verificar-certificado  # confere o hash de integridade do certificado (US20)
```

---

## 4. Arquitetura e estrutura do repositório

```text
pi2-squad-e7/
├── .github/                   # CI (build.yml), templates de issue e de Pull Request
├── assets/                    # Ícone da AURA-67 (.ico/.png) e fonte JetBrains Mono (TrueType)
├── bin/                       # Saída da compilação (no Git ficam só jogo.exe e raylib.dll)
├── docs/                      # Histórias, diagramas, protótipos, testes, relatórios e retrospectiva
├── include/                   # Cabeçalhos da Raylib (raylib.h, raymath.h, rlgl.h)
├── lib/                       # Bibliotecas Raylib para Linux e Windows
├── src/                       # Código-fonte do jogo em C99
│   ├── config.h               # Resolução 1280x720, física, cores e constantes
│   ├── main.c                 # Game loop a 60 FPS e máquina de estados (menu, combate, vitória, tutorial...)
│   ├── player.h / player.c    # Jogador: movimento, esquiva, dano e efeitos de status
│   ├── boss.h / boss.c        # AURA-67: 3 fases cognitivas e padrões de ataque
│   ├── bullet.h / bullet.c    # Projéteis (normal, teleguiado, cegueira, confusão) e lasers
│   ├── typing_engine.h / .c   # Motor de digitação das 10 diretrizes, precisão e penalidade
│   ├── ui.h / ui.c            # HUD, barras, menus, tela de vitória e textos flutuantes
│   ├── game_state.h / .c      # Estado da sessão
│   ├── save.h / save.c        # Save/Load binário da sessão com validação de integridade (US14)
│   ├── ranking.h / ranking.c  # Ranking ordenado e estatísticas das partidas (US10, US15)
│   ├── tutorial.h / .c        # Modo tutorial guiado (US17)
│   ├── audio.h / audio.c      # Efeitos sonoros sintetizados em C (US19)
│   ├── report.h / report.c    # Certificado .txt/.json com hash de integridade (US20)
│   └── icon.rc / icon_data.h  # Ícone embutido no .exe e na janela (US16)
├── tests/
│   ├── test_logica_lmc.c      # Suíte de lógica (make test-lmc)
│   └── verificar_certificado.c# Verificação do hash do certificado (make verificar-certificado)
├── CONTRIBUTING.md            # Guia de contribuição, ambiente e solução de problemas
├── jogar.bat                  # Atalho para abrir o jogo no Windows
├── Makefile                   # make, make run, make windows, make test-lmc, make verificar-certificado
└── README.md                  # Documento principal de entrega
```

---

## 5. Histórias de usuário e rastreabilidade

### 5.1. Histórias de usuário (padrão 3Cs)

O projeto possui **20 Histórias de Usuário** cadastradas e priorizadas no Jira (15 na Unidade 1 e 5 na Unidade 2), detalhadas no padrão **3Cs (Card, Conversation, Confirmation)**:

* **Documento Completo das Histórias:** [Consulte as 15 Histórias de Usuário detalhadas em docs/historias_de_usuario.md](./docs/historias_de_usuario.md)

### Resumo das Histórias de AI Safety:
* **Módulo 1: Arena de Combate e Comportamento da AURA-67**
  * `US01`: Movimentação e Esquiva do Jogador na Arena de Combate (WASD + Direcionais a 60 FPS).
  * `US02`: HUD de Combate, Integridade do Jogador e Barra de Alinhamento da IA (0% a 100%).
  * `US03`: Transição de Fases Cognitivas e Padrões de Ataque da AURA-67 (3 Fases).
  * `US04`: Sistema de Efeitos de Status Adversariais (Confusão e Cegueira).
* **Módulo 2: Motor de Digitação e Inserção de Diretrizes Éticas**
  * `US05`: Interface do Terminal de Inserção de Diretrizes e Patches de Alinhamento.
  * `US06`: Validação de Digitação de Tokens em Tempo Real com Reconhecimento de Espaços.
  * `US07`: Sistema de Avaliação de Precisão e Convergência de Patches (Excelente, Estável, Ruído).
  * `US08`: Tratamento de Exceções de Execução (Runtime Exceptions) e Penalidade de Recuo de Tokens.
* **Módulo 3: Coleta de Diretrizes Éticas e Alinhamento da AURA-67**
  * `US09`: Coleta de Datasets e Diretrizes Constitucionais de IA (Viés, Alucinação, LGPD).
  * `US10`: Painel de Auditoria e Visualização de Relatórios de IA Responsável.
  * `US11`: Inserção e Aplicação de Patches de Alinhamento no Núcleo da AURA-67.
  * `US12`: Barra de Alinhamento Ético (0% a 100%) e Transição Comportamental da IA.
* **Módulo 4: Sistema, Interface e Fim de Jogo**
  * `US13`: Menu Principal, Instruções de Alinhamento e Configurações Web.
  * `US14`: Persistência de Progresso (Save/Load Local de Sessão).
  * `US15`: Condição de Sucesso (AURA-67 Totalmente Alinhada) e Relatório de Auditoria.
* **Módulo 5: Histórias da Unidade 2 (Sprint 03)** — cards no Jira, sem detalhamento em `docs/historias_de_usuario.md`
  * `US16`: Identidade Visual e Ícone Personalizado no Executável (.exe) e na Janela ([PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217)).
  * `US17`: Modo Tutorial Guiado de AI Safety ([PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218)).
  * `US18`: Interface Widescreen HD (1280x720), Fonte TrueType e Menu Principal Ilustrado ([PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219)).
  * `US19`: Feedback Sonoro e Efeitos de Áudio de Combate e Terminal ([PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220)).
  * `US20`: Exportação de Relatório de Auditoria e Certificado de Alinhamento Ético ([PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246)).

### 5.2. Matriz de rastreabilidade bidirecional (US01 a US20)

A matriz liga cada história ao card no Jira, à modelagem (diagrama de atividades e protótipo lo-fi), ao código em C, aos commits e aos casos de teste. A primeira versão, da Entrega 02, cobria só US01 a US15 e marcava a US14 como "A implementar". Esta versão foi conferida com a branch `main` (commit [`50c6934`](https://github.com/vdornelass/pi2-squad-e7/commit/50c6934)) e com o Jira em 22/11/2026.

**Legenda dos testes:** S01, S02 e S03 são os relatórios de teste de sistema das Sprints 01, 02 e 03 ([`sprint01`](./docs/casos_de_teste_sprint01.md) · [`sprint02`](./docs/casos_de_teste_sprint02.md) · [`sprint03`](./docs/casos_de_teste_sprint03.md)). "P" = passou, "F" = falhou.

#### Requisito → implementação → teste

| US | Card no Jira | Diagrama | Lo-Fi | Código em C | Commits | Testes |
| :---: | :---: | :---: | :---: | :--- | :---: | :--- |
| **US01** | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | [AD-US01](./docs/diagramas_atividade/HU1_Movimentacao_e_Esquiva_na_Arena.png) | Gameplay Arena | [`src/player.c`](./src/player.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | S01: 3 P |
| **US02** | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | [AD-US02](./docs/diagramas_atividade/HU2_HUD_de_Combate_Integridade_e_Alinhamento.png) | HUD / Arena | [`src/ui.c`](./src/ui.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | S01: 3 P |
| **US03** | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | [AD-US03](./docs/diagramas_atividade/HU3_Fases_Cognitivas_e_Padroes_da_AURA-67.png) | Chefe / Arena | [`src/boss.c`](./src/boss.c), [`src/bullet.c`](./src/bullet.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c) | S01: 1 P, 2 parciais |
| **US04** | [PI2-70](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-70) | [AD-US04](./docs/diagramas_atividade/HU4_Efeitos_de_Status_Adversariais.png) | Debuffs / Arena | [`src/boss.c`](./src/boss.c), [`src/bullet.c`](./src/bullet.c), [`src/player.c`](./src/player.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | Sem caso de teste formal |
| **US05** | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | [AD-US05](./docs/diagramas_atividade/HU5_Terminal_de_Insercao_de_Diretrizes.png) | Terminal Neural | [`src/ui.c`](./src/ui.c), [`src/typing_engine.c`](./src/typing_engine.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | S01: 3 P |
| **US06** | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | [AD-US06](./docs/diagramas_atividade/HU6_Validacao_de_Digitacao_em_Tempo_Real.png) | Tutorial / Terminal | [`src/typing_engine.c`](./src/typing_engine.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | S01: 3 F → corrigidas e retestadas (#1 na S02; #2 e #3 na S03) |
| **US07** | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | [AD-US07](./docs/diagramas_atividade/HU7_Avaliacao_de_Precisao_e_Patches.png) | Terminal / HUD | [`src/typing_engine.c`](./src/typing_engine.c), [`src/main.c`](./src/main.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | S01: 2 P, 3 F → corrigidas e retestadas (#1 na S02; #3 na S03) |
| **US08** | [PI2-74](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-74) | [AD-US08](./docs/diagramas_atividade/HU8_Tratamento_de_Excecoes_e_Penalidade.png) | Arena / HUD | [`src/typing_engine.c`](./src/typing_engine.c) (recuo de 3 caracteres no erro) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | Sem caso de teste formal |
| **US09** | [PI2-75](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-75) | [AD-US09](./docs/diagramas_atividade/HU9_Coleta_de_Datasets_Constitucionais.png) | Arena Gameplay | [`src/typing_engine.c`](./src/typing_engine.c) (as 10 diretrizes: viés, alucinação, privacidade etc.) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | Sem caso de teste formal. Implementada de forma adaptada (ver nota abaixo) |
| **US10** | [PI2-76](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-76) | [AD-US10](./docs/diagramas_atividade/HU10_Painel_de_Auditoria_e_Score.png) | Painel de Score | [`src/ui.c`](./src/ui.c), [`src/ranking.c`](./src/ranking.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa), [`b296cb2`](https://github.com/vdornelass/pi2-squad-e7/commit/b296cb2) | Indireto: ranking e estatísticas nos CT-US15-05 e 06 (S02) |
| **US11** | [PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77) | [AD-US11](./docs/diagramas_atividade/HU11_Insercao_de_Patches_de_Alinhamento.png) | Terminal / Avaliação | [`src/typing_engine.c`](./src/typing_engine.c), [`src/main.c`](./src/main.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa) | Indireto: aplicação do patch nos CT-US07-01 a 04 (S01) |
| **US12** | [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) | [AD-US12](./docs/diagramas_atividade/HU12_Barra_de_Alinhamento_Etico.png) | HUD / Fases | [`src/boss.c`](./src/boss.c), [`src/ui.c`](./src/ui.c) | [`2aabbfa`](https://github.com/vdornelass/pi2-squad-e7/commit/2aabbfa), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c) | S02: 3 P, 2 F, 1 não testado · S03: RT-09 F na 2ª rodada, P na 4ª (issue [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) fechada) |
| **US13** | [PI2-79](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-79) | [AD-US13](./docs/diagramas_atividade/HU13_Menu_Principal_Instrucoes_e_Configuracoes.png) | Menu Principal | [`src/main.c`](./src/main.c), [`src/ui.c`](./src/ui.c) | [`57dd405`](https://github.com/vdornelass/pi2-squad-e7/commit/57dd405), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c) | S01: 7 P |
| **US14** | [PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80) | [AD-US14](./docs/diagramas_atividade/HU14_Persistencia_de_Progresso.png) | Retomar Sessão | [`src/save.c`](./src/save.c), [`src/game_state.c`](./src/game_state.c), [`src/main.c`](./src/main.c) | [`1b0e96f`](https://github.com/vdornelass/pi2-squad-e7/commit/1b0e96f), [`5b80d72`](https://github.com/vdornelass/pi2-squad-e7/commit/5b80d72) | Sem caso de teste formal |
| **US15** | [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) | [AD-US15](./docs/diagramas_atividade/HU15_Condicao_de_Sucesso_e_Relatorio.png) | Tela de Vitória | [`src/ui.c`](./src/ui.c), [`src/ranking.c`](./src/ranking.c), [`src/main.c`](./src/main.c) | [`61206dd`](https://github.com/vdornelass/pi2-squad-e7/commit/61206dd), [`b296cb2`](https://github.com/vdornelass/pi2-squad-e7/commit/b296cb2) | S02: 3 P, 3 parciais → #7 e #8 corrigidas e retestadas (RT-07 e RT-08 na S03) |
| **US16** | [PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217) | — | — | [`src/icon.rc`](./src/icon.rc), [`src/icon_data.h`](./src/icon_data.h), [`assets/aura67.ico`](./assets/aura67.ico), [`Makefile`](./Makefile) (`make windows`) | [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c), [`3f7655d`](https://github.com/vdornelass/pi2-squad-e7/commit/3f7655d) | S03: 4 P (CT-US16-03 passou na 4ª rodada, issue [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17) fechada) |
| **US17** | [PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218) | — | — | [`src/tutorial.c`](./src/tutorial.c), [`src/main.c`](./src/main.c) | [`c2453bb`](https://github.com/vdornelass/pi2-squad-e7/commit/c2453bb), [`4a32f16`](https://github.com/vdornelass/pi2-squad-e7/commit/4a32f16) (PR [#13](https://github.com/vdornelass/pi2-squad-e7/pull/13)) | S03: 4 P |
| **US18** | [PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219) | — | — | [`src/config.h`](./src/config.h), [`src/ui.c`](./src/ui.c), [`src/main.c`](./src/main.c), [`assets/fonts/`](./assets/fonts) | [`a9c8bb4`](https://github.com/vdornelass/pi2-squad-e7/commit/a9c8bb4), [`a2173ba`](https://github.com/vdornelass/pi2-squad-e7/commit/a2173ba), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c) | S03: 4 P |
| **US19** | [PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220) | — | — | [`src/audio.c`](./src/audio.c), [`src/main.c`](./src/main.c) | [`6a8a9d4`](https://github.com/vdornelass/pi2-squad-e7/commit/6a8a9d4) | S03: 6 P (fecha a issue [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3)) |
| **US20** | [PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246) | — | — | [`src/report.c`](./src/report.c), [`src/main.c`](./src/main.c), [`tests/verificar_certificado.c`](./tests/verificar_certificado.c) | [`ef37f30`](https://github.com/vdornelass/pi2-squad-e7/commit/ef37f30), [`a4a8ffa`](https://github.com/vdornelass/pi2-squad-e7/commit/a4a8ffa) (PR [#16](https://github.com/vdornelass/pi2-squad-e7/pull/16)) | S03: 4 P (fecha a issue [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15)) |

#### Implementação → requisito (sentido inverso)

| Arquivo em C | Histórias que ele atende |
| :--- | :--- |
| [`src/player.c`](./src/player.c) | US01, US04 |
| [`src/boss.c`](./src/boss.c) / [`src/bullet.c`](./src/bullet.c) | US03, US04, US12 |
| [`src/typing_engine.c`](./src/typing_engine.c) | US05, US06, US07, US08, US09, US11 |
| [`src/ui.c`](./src/ui.c) | US02, US05, US10, US12, US13, US15, US18 |
| [`src/main.c`](./src/main.c) | US07, US11, US13, US14, US15, US17, US19, US20 |
| [`src/save.c`](./src/save.c) / [`src/game_state.c`](./src/game_state.c) | US14 |
| [`src/ranking.c`](./src/ranking.c) | US10, US15 |
| [`src/tutorial.c`](./src/tutorial.c) | US17 |
| [`src/audio.c`](./src/audio.c) | US19 |
| [`src/report.c`](./src/report.c) | US20 |
| [`src/icon.rc`](./src/icon.rc) / [`src/icon_data.h`](./src/icon_data.h) | US16 |
| [`src/config.h`](./src/config.h) | US18 (resolução 1280x720) |

**O que a matriz mostra:**

* As 20 histórias têm card no Jira e código na `main`.
* Seis histórias da Unidade 1 não têm caso de teste formal próprio: US04, US08, US09 e US14 não foram testadas, e US10 e US11 só foram cobertas de forma indireta por outros casos.
* A US09 foi adaptada: as diretrizes éticas (viés, alucinação, privacidade) chegam pelo terminal de digitação, e não como itens coletados no cenário. Os critérios do card (item com destaque no cenário e notificação de coleta) não batem com o jogo atual.
* As histórias US16 a US20 foram criadas na Unidade 2 e não têm diagrama de atividades nem protótipo lo-fi.
* Os commits da Unidade 1 não citam o card da história. Por isso, nas US01 a US15 o commit indicado é o que criou ou alterou o módulo. Da Sprint 03 em diante, os commits passaram a citar o card (ex.: `PI2-218`, `PI2-246`).
* No Jira, em 22/11/2026, os cards US16 ([PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217)), US19 ([PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220)) e US20 ([PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246)) estavam em "Tarefas pendentes", com o código das três já na `main`. Em 23/11/2026 os três cards foram movidos para "Concluído" (a issue #17 da US16 foi corrigida em 25/11 e retestada em 26/11).

### 5.3. Diagramas de atividades (US01 a US15)

Diagramas de atividades comportamentais de cada História de Usuário, modelando o fluxo de ações, decisões e exceções (UML como *sketch*). Cada diagrama possui arquivo-fonte `.puml` e imagem `.png`/`.svg` em [`docs/diagramas_atividade`](./docs/diagramas_atividade/).

| ID | História de Usuário | Card no Jira | Responsável | Diagrama de Atividades |
| :---: | :--- | :---: | :---: | :---: |
| **US01** | Movimentação e Esquiva na Arena | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | Caio Brayner (`PI2-112`) | ✅ [AD-US01](./docs/diagramas_atividade/HU1_Movimentacao_e_Esquiva_na_Arena.png) |
| **US02** | HUD de Combate, Integridade e Alinhamento | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | Julio Cesar (`PI2-113`) | ✅ [AD-US02](./docs/diagramas_atividade/HU2_HUD_de_Combate_Integridade_e_Alinhamento.png) |
| **US03** | Fases Cognitivas e Padrões da AURA-67 | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | Jhorge Araújo (`PI2-114`) | ✅ [AD-US03](./docs/diagramas_atividade/HU3_Fases_Cognitivas_e_Padroes_da_AURA-67.png) |
| **US04** | Efeitos de Status Adversariais | [PI2-70](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-70) | Larissa Almeida | ✅ [AD-US04](./docs/diagramas_atividade/HU4_Efeitos_de_Status_Adversariais.png) |
| **US05** | Terminal de Inserção de Diretrizes | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | Larissa Almeida | ✅ [AD-US05](./docs/diagramas_atividade/HU5_Terminal_de_Insercao_de_Diretrizes.png) |
| **US06** | Validação de Digitação em Tempo Real | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | Larissa Almeida | ✅ [AD-US06](./docs/diagramas_atividade/HU6_Validacao_de_Digitacao_em_Tempo_Real.png) |
| **US07** | Avaliação de Precisão e Patches | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | Larissa Almeida | ✅ [AD-US07](./docs/diagramas_atividade/HU7_Avaliacao_de_Precisao_e_Patches.png) |
| **US08** | Tratamento de Exceções e Penalidade | [PI2-74](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-74) | Larissa Almeida | ✅ [AD-US08](./docs/diagramas_atividade/HU8_Tratamento_de_Excecoes_e_Penalidade.png) |
| **US09** | Coleta de Datasets Constitucionais | [PI2-75](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-75) | Larissa Almeida | ✅ [AD-US09](./docs/diagramas_atividade/HU9_Coleta_de_Datasets_Constitucionais.png) |
| **US10** | Painel de Auditoria e Score | [PI2-76](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-76) | Larissa Almeida | ✅ [AD-US10](./docs/diagramas_atividade/HU10_Painel_de_Auditoria_e_Score.png) |
| **US11** | Inserção de Patches de Alinhamento no Núcleo | [PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77) | Larissa Almeida | ✅ [AD-US11](./docs/diagramas_atividade/HU11_Insercao_de_Patches_de_Alinhamento.png) |
| **US12** | Barra de Alinhamento Ético e Comportamento da AURA-67 | [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) | Larissa Almeida | ✅ [AD-US12](./docs/diagramas_atividade/HU12_Barra_de_Alinhamento_Etico.png) |
| **US13** | Menu Principal, Instruções e Configurações | [PI2-79](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-79) | Larissa Almeida | ✅ [AD-US13](./docs/diagramas_atividade/HU13_Menu_Principal_Instrucoes_e_Configuracoes.png) |
| **US14** | Persistência de Progresso (Save/Load) | [PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80) | Larissa Almeida | ✅ [AD-US14](./docs/diagramas_atividade/HU14_Persistencia_de_Progresso.png) |
| **US15** | Condição de Sucesso e Relatório de Auditoria | [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) | Larissa Almeida | ✅ [AD-US15](./docs/diagramas_atividade/HU15_Condicao_de_Sucesso_e_Relatorio.png) |

### 5.4. Protótipos lo-fi (US01 a US15)

Sketches (SK) e storyboards (SB) de cada História de Usuário, disponíveis em [`docs/prototipos`](./docs/prototipos/) e no [arquivo do Figma](https://www.figma.com/design/7Uj5SqL213oycfgWxCOjLh/Sem-t%C3%ADtulo?node-id=0-1).

| ID | História de Usuário | Card no Jira | Tipo | Protótipo |
| :---: | :--- | :---: | :---: | :---: |
| **US01** | Movimentação e Esquiva na Arena | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | Sketch | ✅ [Tutorial](./docs/prototipos/SK-HU1_Movimentacao_e_Esquiva_na_Arena_1_Tutorial.png) · [Arena](./docs/prototipos/SK-HU1_Movimentacao_e_Esquiva_na_Arena_2_Arena.png) |
| **US02** | HUD de Combate, Integridade e Alinhamento | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | Sketch | ✅ [SK-US02](./docs/prototipos/SK-HU2_HUD_de_Combate_Integridade_e_Alinhamento.png) |
| **US03** | Fases Cognitivas e Padrões da AURA-67 | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | Storyboard | ✅ [Fase 1](./docs/prototipos/SB-HU3_Fases_Cognitivas_e_Padroes_da_AURA-67_1_Fase1.png) · [Fase 2](./docs/prototipos/SB-HU3_Fases_Cognitivas_e_Padroes_da_AURA-67_2_Fase2.png) · [Fase 3](./docs/prototipos/SB-HU3_Fases_Cognitivas_e_Padroes_da_AURA-67_3_Fase3.png) |
| **US04** | Efeitos de Status Adversariais | [PI2-70](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-70) | Storyboard | ✅ [SB-US04](./docs/prototipos/SB-HU4_Efeitos_de_Status_Adversariais.png) |
| **US05** | Terminal de Inserção de Diretrizes | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | Storyboard | ✅ [SB-US05](./docs/prototipos/SB-HU5_Terminal_de_Insercao_de_Diretrizes.png) |
| **US06** | Validação de Digitação em Tempo Real | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | Storyboard | ✅ [SB-US06](./docs/prototipos/SB-HU6_Validacao_de_Digitacao_em_Tempo_Real.png) |
| **US07** | Avaliação de Precisão e Patches | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | Storyboard | ✅ [SB-US07](./docs/prototipos/SB-HU7_Avaliacao_de_Precisao_e_Patches.png) |
| **US08** | Tratamento de Exceções e Penalidade | [PI2-74](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-74) | Storyboard | ✅ [SB-US08](./docs/prototipos/SB-HU8_Tratamento_de_Excecoes_e_Penalidade.png) |
| **US09** | Coleta de Datasets Constitucionais | [PI2-75](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-75) | Storyboard | ✅ [SB-US09](./docs/prototipos/SB-HU9_Coleta_de_Datasets_Constitucionais.png) |
| **US10** | Painel de Auditoria e Score | [PI2-76](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-76) | Storyboard | ✅ [SB-US10](./docs/prototipos/SB-HU10_Painel_de_Auditoria_e_Score.png) |
| **US11** | Inserção de Patches de Alinhamento no Núcleo | [PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77) | Storyboard | ✅ [Terminal](./docs/prototipos/SB-HU11_Insercao_de_Patches_de_Alinhamento_1_Terminal.png) · [Avaliação](./docs/prototipos/SB-HU11_Insercao_de_Patches_de_Alinhamento_2_Avaliacao.png) |
| **US12** | Barra de Alinhamento Ético e Comportamento da AURA-67 | [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) | Sketch / Storyboard | ✅ [HUD](./docs/prototipos/SK-HU12_Barra_de_Alinhamento_Etico_1_HUD.png) · [Transição de fases](./docs/prototipos/SB-HU12_Barra_de_Alinhamento_Etico_2_Transicao_de_Fases.png) |
| **US13** | Menu Principal, Instruções e Configurações | [PI2-79](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-79) | Storyboard | ✅ [SB-US13](./docs/prototipos/SB-HU13_Menu_Principal_Instrucoes_e_Configuracoes.png) |
| **US14** | Persistência de Progresso (Save/Load) | [PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80) | Storyboard | ✅ [SB-US14](./docs/prototipos/SB-HU14_Persistencia_de_Progresso.png) |
| **US15** | Condição de Sucesso e Relatório de Auditoria | [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) | Storyboard | ✅ [SB-US15](./docs/prototipos/SB-HU15_Condicao_de_Sucesso_e_Relatorio.png) |

---

## 6. Qualidade e testes

### 6.1. Visão geral

Os testes de sistema foram escritos a partir dos critérios de confirmação (3Cs) de cada card do Jira, executados com o jogo rodando por inteiro e gravados em vídeo. Toda falha virou issue no GitHub e só foi fechada depois de um reteste.

| Sprint | Entrega | Casos | Passaram | Falharam | Parciais / não testados | Relatório |
| :-: | :-: | :-: | :-: | :-: | :-: | :-- |
| 01 | 03 | 27 | 19 | 6 | 2 | [`casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md) |
| 02 | 04 | 13 | 7 | 2 | 4 | [`casos_de_teste_sprint02.md`](./docs/casos_de_teste_sprint02.md) |
| 03 | 05 | 27 | 27 | 0 | 0 | [`casos_de_teste_sprint03.md`](./docs/casos_de_teste_sprint03.md) |

Além dos testes de sistema, a lógica do jogo tem testes automatizados (`make test-lmc` e `make verificar-certificado`, ver [seção 3.4](#34-testes-automatizados)).

### 6.2. Sprint 01 (Entrega 03)

Os testes de sistema da Sprint 01 estão em [`docs/casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md): 27 casos de teste das histórias US01, US02, US03, US05, US06, US07 e US13, escritos a partir dos critérios de confirmação de cada card do Jira.

* **Resultado:** 19 casos passaram, 6 falharam e 2 passaram só em parte.
* **Evidência em vídeo:** o [vídeo de testes](./docs/screencast_testes_sprint01.mov) (1:46, com legendas e sem áudio) mostra os casos executados, e o [vídeo de demonstração](./docs/screencast_demonstracao_lofi.mp4) mostra os demais. Os horários de cada caso estão na coluna Evidência da tabela.
* **Falhas encontradas**, registradas na aba [Issues](https://github.com/vdornelass/pi2-squad-e7/issues):
  * O Espaço conta como erro de digitação (CT-US06-02, CT-US07-02 e CT-US07-03): [#1](https://github.com/vdornelass/pi2-squad-e7/issues/1) (corrigida e retestada na Sprint 02, ver [seção 6.3](#63-sprint-02-entrega-04)).
  * As teclas W, A, S e D geram erro de digitação (CT-US06-03): [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2).
  * O jogo não emite som (CT-US06-01 e CT-US07-05): [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3).

### 6.3. Sprint 02 (Entrega 04)

Os testes de sistema da Sprint 02 estão em [`docs/casos_de_teste_sprint02.md`](./docs/casos_de_teste_sprint02.md): 12 casos de teste das histórias **US12** e **US15**, escritos a partir dos critérios de confirmação de cada card do Jira, mais 1 reteste de regressão da Sprint 01.

* **Resultado:** 7 casos passaram, 2 falharam, 3 passaram só em parte e 1 não foi testado.
* **Evidência em vídeo** (também anexada aos cards do Jira):

| História | Card | Screencast |
| :-- | :-: | :-- |
| US12: Barra de Alinhamento Ético | [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) | [vídeo](./docs/screencast_testes_sprint02_US12.mp4) |
| US15: Vitória e Relatório de Auditoria | [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) | [vitória](./docs/screencast_testes_sprint02_US15_vitoria.mp4) · [ranking](./docs/screencast_testes_sprint02_US15_ranking.mp4) |

* **Ambiente de teste:** na US15, as vidas foram aumentadas para 50 só na máquina de teste, para validar a condição de vitória sem depender da habilidade de quem joga. A alteração não foi commitada.

#### Issue / Bug Tracker

* **Corrigida e retestada:** Barra de espaço conta como erro de digitação: [#1](https://github.com/vdornelass/pi2-squad-e7/issues/1) (fechada).
* **Novas falhas encontradas na Sprint 02:**
  * [US15] Contador de patches exibe "11/10" na tela de vitória: [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7)
  * [US15] Tela de vitória não exibe Precisão, Tempo de Sessão e Rank: [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8)
  * [US12] Sem aviso narrativo na transição de fase da AURA-67: [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9)
  * [Build] Makefile não recompila quando só o src/config.h é alterado: [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10)
* **Continuam abertas da Sprint 01:**
  * Teclas W, A, S e D geram erro de digitação: [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) (aguardando reteste)
  * O jogo não emite som: [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) (prevista para a US19)

![Issue tracker da Sprint 02](./docs/img/bug_tracker_sprint02.png)

### 6.4. Sprint 03 (Entrega 05 · PI2-237 / PI2-238 / PI2-239)

Os testes de sistema da Sprint 03 estão em [`docs/casos_de_teste_sprint03.md`](./docs/casos_de_teste_sprint03.md): **22 casos** das histórias **US16 a US20**, escritos a partir dos critérios de confirmação de cada card do Jira, mais **5 retestes de regressão** das issues abertas nas Sprints 01 e 02.

Os testes foram feitos em rodadas, à medida que cada história entrava na `main`:

| Rodada | Data | Versão testada | O que foi testado |
| :-: | :-: | :-- | :-- |
| 1ª | 19 e 20/11 | `2a82daa` e `ef37f30` | US18, US19 (no `jogo.exe`, PC do Caio) e retestes das issues #2, #7, #8 e #10 |
| 2ª | 21/11 | `3f7655d` | US16, US17, US18, US19, US20 e retestes das issues #9, #10 e #12 |
| 3ª | 22/11 | `c35ea04` | Reteste da US20 depois da correção da issue #15 (PR #16) |
| 4ª | 26/11 | `43dcdc8` e `3c58b56` | Retestes das issues #9, #10 e #17, corrigidas no commit `43dcdc8` (25/11) |

* **Resultado:** os 27 casos passaram. Depois da 3ª rodada eram 24 aprovados e 3 falhas (#9, #10 e #17); as três foram corrigidas em 25/11 e passaram no reteste da 4ª rodada.
* **Evidência em vídeo** (também anexada aos cards do Jira):

| História | Card | Resultado | Evidência |
| :-- | :-: | :-: | :-- |
| US16: Ícone personalizado | [PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217) | 4 de 4 passaram | [ícone no .exe](./docs/img/print_us16_icone_exe.png) · [sem a pasta assets](./docs/img/print_us16_sem_assets.png) · [make windows](./docs/img/print_us16_make_windows.png) · [barra de tarefas](./docs/img/print_us16_icone_barra_tarefas.png) · [barra de título](./docs/img/print_us16_icone_barra_titulo.png) |
| US17: Tutorial guiado | [PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218) | 4 de 4 passaram | [partida](./docs/screencast_testes_sprint03_rodada2_partida.mp4) · [vitória](./docs/screencast_testes_sprint03_rodada2_vitoria.mp4) |
| US18: Widescreen HD, fonte e menu | [PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219) | 4 de 4 passaram | [partida](./docs/screencast_testes_sprint03_rodada2_partida.mp4) |
| US19: Feedback sonoro | [PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220) | 6 de 6 passaram | [áudio](./docs/screencast_testes_sprint03_US19_audio.mp4) · [vitória](./docs/screencast_testes_sprint03_rodada2_vitoria.mp4) |
| US20: Certificado de alinhamento | [PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246) | 4 de 4 passaram | [vitória e certificado](./docs/screencast_testes_sprint03_rodada2_vitoria.mp4) · [hash e verificação](./docs/screencast_testes_sprint03_rodada3_US20.mp4) |

* **Ambiente de teste:** para validar a vitória sem depender da habilidade de quem joga, o dano ao jogador foi desligado só na máquina de teste (alteração não commitada). Os detalhes de ambiente (som no WSL, bloqueio do `jogo.exe` pelo Windows) estão no documento de casos de teste e no [CONTRIBUTING.md](./CONTRIBUTING.md).
* **Mudança de critério registrada:** o CA03 da US18 pedia um menu em estilo terminal CLI. Com o menu novo (commit `f91402c`), o card [PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219) foi atualizado em 21/11, com nota de rastreabilidade, e o caso foi reexecutado com o critério novo.

#### Issue / Bug Tracker

As falhas foram registradas como issues no GitHub no mesmo dia em que foram encontradas, citando o caso de teste e o card do Jira.

* **Corrigidas e retestadas na Sprint 03:**
  * [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2) Teclas W, A, S e D geram erro de digitação (RT-02, fechada)
  * [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3) O jogo não emite som (CT-US19-01 a 06, fechada)
  * [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7) Contador "11/10" na vitória (RT-07, fechada)
  * [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8) Vitória sem Precisão, Tempo e Rank (RT-08, fechada)
  * [#12](https://github.com/vdornelass/pi2-squad-e7/issues/12) Textos sem acento (CT-US18-03, fechada)
  * [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15) Certificado sem hash de integridade e sem integridade restante (CT-US20-02 e CT-US20-04, fechada). Correção no PR [#16](https://github.com/vdornelass/pi2-squad-e7/pull/16), revisado pelo Matheus Chaves.
* **Corrigidas em 25/11 (commit `43dcdc8`, Matheus Chaves) e retestadas na 4ª rodada (26/11):**
  * [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9) Sem aviso narrativo na transição de fase (RT-09, fechada): [aviso da Fase 2](./docs/img/print_rt09_fase2.png) · [aviso da Fase 3](./docs/img/print_rt09_fase3.png) · [vídeo](./docs/screencast_testes_sprint03_rodada4_RT09.mp4)
  * [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) Makefile não recompila quando só um `.h` muda (RT-10, fechada)
  * [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17) Ícone da AURA-67 não aparece na barra de título da janela (CT-US16-03, fechada): [print da barra de título](./docs/img/print_us16_icone_barra_titulo.png)
* **Situação final:** as 10 issues registradas nos testes estão fechadas, todas com reteste.

![Issue tracker da Sprint 03](./docs/img/bug_tracker_sprint03.png)

---

## 7. Processo e sustentabilidade

Em atendimento ao princípio central da **Entrega 05 (Item 4 — Sustentabilidade)**: *"O repositório precisa sustentar o projeto sem a presença da equipe. O GitHub não é o lugar onde se joga o código — é o documento onde o projeto se explica"*.

### 7.1. Versionamento

Esta subseção registra como a Squad E7 versiona o projeto: onde o código fica, qual fluxo de trabalho seguimos, como ligamos cada commit ao card do Jira e a atividade do repositório durante a Sprint 01.

#### Ambiente de versionamento

* **Repositório:** [github.com/vdornelass/pi2-squad-e7](https://github.com/vdornelass/pi2-squad-e7), com Git e GitHub.
* **Branch principal:** `main`, mantida estável e pronta para entrega.
* **Integração contínua:** o GitHub Actions compila o projeto em C99 (`-Wall -Wextra -std=c99 -pedantic`) a cada push e a cada Pull Request para a `main` ([`.github/workflows/build.yml`](./.github/workflows/build.yml)).
* **Templates:** modelo de Pull Request com vínculo ao card do Jira e checklist de qualidade, além de modelos de issue para bugs e novas funcionalidades ([`.github/`](./.github)).

#### Fluxo de trabalho e convenções

O fluxo completo está no [CONTRIBUTING.md](./CONTRIBUTING.md). Em resumo:

1. **Uma branch por card do Jira**, a partir da `main` atualizada: `feature/PI2-XXX-nome-da-tarefa`.
2. **Commits no padrão Conventional Commits**, com o card entre parênteses no final: `tipo(escopo): descricao (PI2-XXX)`. Tipos usados: `feat`, `fix`, `docs`, `style`, `refactor`, `test`.
3. **Pull Request** para a `main`, preenchendo o template e com revisão de pelo menos um colega antes do merge.

Exemplos:

```text
feat(pif): implementar modulo save.c (PI2-XXX)
fix(bullet): corrigir colisao de projeteis (PI2-XXX)
docs(fds): adicionar secao de versionamento no README (PI2-200)
```

**Regra da Sprint 01:** todo commit e todo Pull Request cita a chave do card correspondente.

#### Rastreabilidade: história, card e commit

A cadeia de rastreabilidade é **história de usuário → card no Jira → branch / commit / Pull Request**. A chave `PI2-XXX` é o elo entre o Board e o código. Exemplos reais do histórico do repositório:

| Card | Commit |
| :--- | :--- |
| PI2-15 / PI2-58 (menu e motor do jogo) | [`57dd405`](https://github.com/vdornelass/pi2-squad-e7/commit/57dd405): `feat(pif): implementar menu interativo e motor do jogo em C` |
| PI2-89 / PI2-90 (loop de combate e pontuação) | [`09eb5f7`](https://github.com/vdornelass/pi2-squad-e7/commit/09eb5f7): `feat(pif): consolidar pontuacao e loop de combate` |
| PI2-127 (screencast de demonstração) | [`56ffb38`](https://github.com/vdornelass/pi2-squad-e7/commit/56ffb38): `feat(screencast): adicionar video demonstrativo completo` |

#### Atividade do repositório

| Semana | Período | Commits | Autores ativos |
| :---: | :---: | :---: | :---: |
| 36 | 31/08 – 06/09 | 9 | 1 |
| 37 | 07/09 – 13/09 | 2 | 1 |
| 38 | 14/09 – 20/09 | 5 | 3 |
| 39 | 21/09 – 27/09 | 19 | 3 |
| 40 | 28/09 – 04/10 | 2 | 1 |
| 41 | 05/10 – 11/10 | 2 | 1 |
| 42 | 12/10 – 18/10 | 13 | 2 |
| 43 | 19/10 – 25/10 | 14 | 6 |

Para refazer o levantamento:

```bash
git log --all --date=format:'%G-W%V' --pretty='%ad' | sort | uniq -c
```

### 7.2. Frequência semanal de commits (Semanas 36 a 47)

Levantamento extraído diretamente do histórico do repositório (`git log origin/main --date=format:'%G-W%V' --pretty='%h|%ad|%an'`):

| Semana ISO | Período Calendário | Commits na `main` | Autores Ativos | Entregas e Marcos Principais |
| :---: | :---: | :---: | :---: | :--- |
| **Semana 36** | `01/09 – 03/09` | 9 | 1 | Estrutura inicial do projeto C99 + Raylib 5.0 |
| **Semana 37** | `13/09` | 2 | 1 | Configuração inicial do `Makefile` e flags estritas |
| **Semana 38** | `15/09 – 19/09` | 5 | 3 | Sistema de projéteis, boss e movimentação fluida |
| **Semana 39** | `22/09 – 24/09` | 19 | 3 | Entrega 02 FDS, diagramas UML, protótipos Lo-Fi e MVP 1 |
| **Semana 40** | `29/09` | 2 | 1 | Relatório formal de LMC (AV1) e redesign visual |
| **Semana 41** | `05/10 – 07/10` | 2 | 1 | `jogar.bat` inicial, GitHub Actions CI e templates de PR/Issue |
| **Semana 42** | `13/10 – 18/10` | 13 | 2 | Screencasts, casos de teste Sprint 01 e seção de versionamento do README |
| **Semana 43** | `20/10 – 23/10` | 16 | 6 | Persistência binária (`save.c`), ranking (`ranking.c`), PRs #4/#5 e Entrega 03/04 |
| **Semana 44** | `29/10` | 2 | 1 | Casos de teste Sprint 02 e atualização do Issue Tracker (`PI2-227`, `PI2-228`) |
| **Semana 45** | `06/11` | 4 | 3 | Áudio sintetizado (`US19`), tela Widescreen HD (`US18`) e refinos de boss/projéteis |
| **Semana 46** | `11/11` | 3 | 1 | Validação lógica LMC (`PI2-31`), Pair Programming Sprint 03 e deck final (`PR #11`) |
| **Semana 47** | `19/11 – 22/11` | 23+ | 6+ | `jogar.bat` portátil (`PI2-254`), `src/report.c` (`US20`), `src/tutorial.c` (`PR #13`), ícone/rebalanceamento, fonte UTF-8, 2ª rodada de testes (`bcd2dc7`), `CONTRIBUTING.md` e Entrega 05 (`PR #14`) |

### 7.3. Guia de contribuição (`CONTRIBUTING.md` · PI2-241)
* **Documento Oficial:** [`CONTRIBUTING.md`](./CONTRIBUTING.md)
* Contém o passo a passo completo para qualquer contribuidor configurar e compilar o projeto de forma autônoma no **Windows (`jogar.bat`, `w64devkit`/MinGW-w64)**, **Linux Ubuntu/Debian** e **WSL2**, além do mapa de módulos em `src/`, comandos do `Makefile` (`make`, `make windows`, `make test-lmc`), convenções C99, fluxo *Feature Branch + Conventional Commits (`PI2-XXX`)*, checklist de *Definition of Done* e guia de *troubleshooting*.

### 7.4. Programação em pares

Cada sprint teve um relato das duplas (*Driver* / *Navigator*, horários, cards e aprendizados):

| Sprint | Cards | Relato |
| :-: | :-- | :-- |
| 01 (Entrega 03) | PI2-195 / PI2-207 / PI2-208 / PI2-209 | [`relatorio_pair_programming_sprint01.md`](./docs/relatorio_pair_programming_sprint01.md) |
| 02 (Entrega 04) | PI2-223 / PI2-225 / PI2-226 / PI2-230 / PI2-231 | [`relatorio_pair_programming_sprint02.md`](./docs/relatorio_pair_programming_sprint02.md) |
| 03 (Entrega 05) | PI2-242 | [`relatorio_pair_programming_sprint03.md`](./docs/relatorio_pair_programming_sprint03.md) |

* **Sprint 03:** o relato detalha a atuação da **Dupla 1** (João Gabriel & Caio Brayner — áudio, certificado e `jogar.bat`), **Dupla 2** (Matheus Chaves & Julio Cesar — widescreen 720p, fonte UTF-8, tutorial e usabilidade), **Dupla 3** (Theo Monteiro & Larissa Almeida — validação lógica LMC em `tests/test_logica_lmc.c` e testes de sistema) e **Facilitação** (Mateus Lacerda — governança Jira, sustentabilidade e roteiro final).

### 7.5. Retrospectiva técnica da Unidade 2

O que funcionou, o que não funcionou e as ações para a próxima unidade: [`docs/retrospectiva_unidade2.md`](./docs/retrospectiva_unidade2.md).

---

## 8. Histórico das entregas de FDS

Registro de cada entrega como foi avaliada. As partes que valem para o projeto todo (testes, rastreabilidade, processo) estão nas seções 5, 6 e 7.

### 8.1. Entrega 01: board e backlog

#### Visão geral do Board (quadro Kanban no Jira)
*(Print do quadro Kanban com as colunas Backlog, A Fazer, Em Andamento e Concluído)*
![Board Atualizado no Jira](./docs/img/print_board.png)

#### Backlog priorizado no Jira
*(Print da lista de Backlog ordenada por prioridade no Jira)*
![Backlog Priorizado no Jira](./docs/img/print_backlog.png)

#### Card no padrão 3Cs (Card, Conversation, Confirmation)
*(Print de um ticket aberto no Jira exibindo os 3Cs preenchidos)*
![Exemplo de Card 3Cs no Jira](./docs/img/print_card_3cs.png)

### 8.2. Entrega 02: modelagem, prototipação e demonstração

Esta seção consolida a preparação e a infraestrutura documental da **Entrega 02 de Engenharia de Software (FDS)** estruturada pela Lead de Engenharia (Larissa Almeida):

* **Documento Técnico de Rastreabilidade:** [Consulte o documento em docs/entrega_02_modelagem_prototipacao.md](./docs/entrega_02_modelagem_prototipacao.md)
* **Diagramas de atividades e protótipos lo-fi:** [seções 5.3 e 5.4](#53-diagramas-de-atividades-us01-a-us15).
* **Matriz de rastreabilidade (atualizada para US01 a US20):** [seção 5.2](#52-matriz-de-rastreabilidade-bidirecional-us01-a-us20).

#### Demonstração (roteiro e screencast · PI2-127)

Roteiro de apresentação e narração estruturado por Larissa Almeida para o screencast de demonstração do MVP 1 do AI Safety, jogo em C99 + Raylib 5.0:

* **Documento Técnico de Falas (Teleprompter):** [Consulte as falas e minutagem detalhadas em docs/roteiro-screencast-entrega03.md](./docs/roteiro-screencast-entrega03.md)
* **Critérios Formais da Rubrica:** Demonstração em vídeo (1 a 3 minutos) com áudio e legendas.
* **Sequência da Demonstração (02:45):**
  * **Cena 1 (00:00 – 00:35):** Abertura e build — C99 + Raylib 5.0, Makefile e compilação sem warnings.
  * **Cena 2 (00:35 – 00:55):** **US13** — Menu principal, modos Normal e Difícil e controles.
  * **Cena 3 (00:55 – 01:30):** **US01** e **US02** — Movimentação, esquiva e HUD de combate.
  * **Cena 4 (01:30 – 02:15):** **US05, US06, US07, US08, US11 e US12** — Motor de digitação.
  * **Cena 5 (02:15 – 02:45):** **US03, US04 e US15** — Fases cognitivas da AURA-67 e vitória.
* **Histórias não demonstradas no vídeo:** US09, US10 e US14.
* **Vídeo da Demonstração (Áudio e Legendas Integradas):** [`docs/screencast_demonstracao_lofi.mp4`](./docs/screencast_demonstracao_lofi.mp4)

### 8.3. Entrega 03: Sprint 01

Evidências da Entrega 03, referentes à Sprint 01 (sprint **Week 12e13 - Protótipo** no Board do Jira), organizadas pelos quatro critérios de avaliação.

Esta subseção consolida o cumprimento do **Item 1: Implementação** da Entrega 03 de FDS, demonstrando a entrega de software funcionando a partir de requisitos formais, rastreabilidade completa no Jira e validação por testes de sistema.

#### 8.3.1. Histórias de Usuário Implementadas (Mínimo de 5 Exigido)

A Squad E7 selecionou e validou **7 Histórias de Usuário** no ciclo de entrega, superando o mínimo de 5 exigido pela rubrica. Todas as histórias possuem cards detalhados no Jira no padrão 3Cs, código integrado no motor em C99 e cobertura pelos 27 casos de teste de sistema documentados na [seção 6.2](#62-sprint-01-entrega-03) ([`docs/casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md)):

| US | Card no Jira | Descrição Funcional Implementada | Arquivos em C | Testes de sistema (Sprint 01) |
| :---: | :---: | :--- | :--- | :---: |
| **US01** | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | Movimentação e esquiva do jogador na arena de combate | `src/player.c` | 3 CTs: 3 passaram |
| **US02** | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | HUD: integridade do jogador, barra do chefe e alinhamento | `src/ui.c` | 3 CTs: 3 passaram |
| **US03** | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | Fases cognitivas da AURA-67 e padrões de ataque | `src/boss.c`, `src/bullet.c` | 3 CTs: 1 passou, 2 parciais |
| **US05** | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | Terminal de inserção de diretrizes éticas | `src/ui.c` (`ui_draw_typing_box`), `src/typing_engine.c` | 3 CTs: 3 passaram |
| **US06** | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | Validação de digitação em tempo real e detecção de erros | `src/typing_engine.c` (`typing_engine_handle_key`) | 3 CTs: 3 falharam (Issues [#1](https://github.com/vdornelass/pi2-squad-e7/issues/1) e [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2)) |
| **US07** | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | Avaliação de precisão e pontuação dos patches | `src/typing_engine.c` (`typing_engine_get_accuracy`), `src/main.c` (`combat_process_round`) | 5 CTs: 2 passaram, 3 falharam |
| **US13** | [PI2-79](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-79) | Menu principal com instruções, dificuldade e fluxo de entrada | `src/ui.c` (`ui_draw_menu`), `src/main.c` (estado `STATE_MENU`) | 7 CTs: 7 passaram |

*Correção (Entrega 05):* a versão anterior desta tabela citava `src/terminal.c`, `src/patch.c` e `src/menu.c`, arquivos que não existem no repositório, e registrava todos os testes como 100% OK. A tabela foi conferida com o código da branch `main` e com os resultados de [`docs/casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md). A falha do Espaço ([#1](https://github.com/vdornelass/pi2-squad-e7/issues/1)) foi corrigida e retestada na Sprint 02 ([seção 6.3](#63-sprint-02-entrega-04)).

*Histórias seguintes:*

* **US14** ([PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80)): Persistência local de progresso (`src/save.c`).
* **US11** ([PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77)): Inserção de patches de alinhamento (`src/patch_feedback.c`, no PR [#6](https://github.com/vdornelass/pi2-squad-e7/pull/6), ainda não integrado à `main`).

#### 8.3.2. Gestão da Sprint no Board (Jira Software)

* **Link Oficial do Board:** [Acessar Board do Projeto PI2 - Squad E7](https://csprj-adsr-2p-e7.atlassian.net/jira/software/c/projects/PI2/boards/2)
* **Equivalência de Nomenclatura:** A "Sprint 01" avaliada na Entrega 03 de FDS corresponde ao ciclo de desenvolvimento da Unidade 2, ativo no Board do Jira como **Week 12 - Protótipo** (Sprint ID 82, período 19/10/2026 a 24/10/2026).
* **Meta da Sprint (*Sprint Goal*):** *"PIF: protótipo jogável integrado em C99, persistencia binaria, ranking, patches de alinhamento e playtesting + Entrega 03 FDS: testes de sistema, screencasts, rastreabilidade e pareamento."*
* **Status das Colunas:** O Board reflete rigorosamente a realidade do repositório:
  * **Concluído (Done):** Histórias finalizadas, casos de testes de sistema elaborados e executados, convenção de versionamento e definição de duplas.
  * **Em andamento (In Progress):** Playtesting do protótipo e evidências finais.
  * **Tarefas pendentes (To Do):** Histórias planejadas para os ciclos subsequentes.

#### 8.3.3. Evidência Visual do Board Atualizado

Captura em alta resolução realizada diretamente do Jira Software, exibindo todas as colunas (*To Do*, *In Progress* e *Done*) e as swimlanes de PIF e FDS:

![Visão Completa do Board no Jira](./docs/img/print_board_sprint2_completo.png)

#### 8.3.4. Qualidade, testes e programação em pares
* Testes de sistema da Sprint 01: [seção 6.2](#62-sprint-01-entrega-03).
* Relato de programação em pares da Sprint 01: [seção 7.4](#74-programação-em-pares).

### 8.4. Entrega 04: Sprint 02

No Jira, a Sprint 02 corresponde à sprint **"Week 13 e 14"** (26/10/2026 a 09/11/2026), finalizada pelo Scrum Master Mateus Lacerda.

**Meta da sprint:** *"Concluir 100% das Histórias de Usuário restantes (US12 e US15), aplicar os ajustes de usabilidade e interface (IHC), validar a lógica formal no código em C (LMC) e reexecutar os testes de sistema solucionando as Issues abertas (FDS/PIF)."*

#### Histórias de usuário entregues

| US | Card no Jira | Descrição | Arquivos em C | Testes de sistema |
| :---: | :---: | :--- | :--- | :---: |
| **US12** | [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) | Barra de Alinhamento Ético e mudança de comportamento da AURA-67 por fase | `src/boss.c`, `src/ui.c` (`ui_draw_boss_hp`, `ui_draw_hud_stats`) | 6 CTs: 3 passaram, 2 falharam, 1 não testado ([seção 6.3](#63-sprint-02-entrega-04)) |
| **US15** | [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) | Condição de sucesso (AURA-67 alinhada) e relatório de auditoria | `src/ui.c` (`ui_draw_victory`), `src/ranking.c`, `src/main.c` | 6 CTs: 3 passaram, 3 parciais ([seção 6.3](#63-sprint-02-entrega-04)) |

#### Relatório da sprint no Jira

* **Concluídos (8 itens):** as histórias US12 ([PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78)) e US15 ([PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81)), as entregas semanais [PI2-32](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-32) (W13-Testes, FDS) e [PI2-33](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-33) (W15-Versão final, PIF), e os cards dos critérios da Entrega 04: [PI2-223](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-223) (Implementação), [PI2-224](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-224) (Qualidade e testes), [PI2-229](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-229) (Produto em produção) e [PI2-230](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-230) (Processo).
* **Não completados (2 itens):** [PI2-30](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-30) (W13-Ajustes, IHC) e [PI2-31](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-31) (Validação lógica, LMC), que seguiram para a sprint seguinte.
* **Removidos e replanejados (4 itens):** US16 ([PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217)), US17 ([PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218)), US18 ([PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219)) e US19 ([PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220)) saíram da Sprint 02 e foram replanejadas para a Sprint 03 ("Week 15 e 16").

![Relatório da Sprint 02 no Jira](./docs/img/print_sprint02_relatorio.png)

#### Processo e engenharia de software (PI2-230 / PI2-231)

Sob facilitação do Scrum Master **Mateus Lacerda**, esta subseção consolida as evidências de processo exigidas na Entrega 04 de FDS:

* **Cadência Semanal de Commits (Semanas 36 a 44):** Verificada continuamente via `git log`, comprovando entregas incrementais em todas as semanas e participação de **6 autores distintos** na Semana 43 (`20/10` a `23/10`).
* **Programação em Pares (Sprint 02):** Relato formal das duplas (*Driver* / *Navigator*, horários e aprendizados) documentado em [`docs/relatorio_pair_programming_sprint02.md`](./docs/relatorio_pair_programming_sprint02.md).
* **Evidências Visuais do Board e Product Backlog (Sprint 02 — `Week 13 e 14`):**

| Visão do Board (Sprint 02) | Visão do Product Backlog (Pós-Sprint 02) |
| :---: | :---: |
| ![Print Oficial do Board da Sprint 02](./docs/img/print_board_sprint02.png) | ![Print Oficial do Backlog do Produto](./docs/img/print_backlog_sprint02.png) |

#### Qualidade e testes
* Testes de sistema da Sprint 02 e Issue Tracker: [seção 6.3](#63-sprint-02-entrega-04).

### 8.5. Entrega 05: Sprint 03

Esta seção consolida os entregáveis de fechamento da **Unidade 2 — Entrega 05 de FDS** ([PI2-233](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-233), [PI2-240](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-240), [PI2-243](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-243)) e da avaliação final de processo de **Projetos 2** ([PI2-256](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-256)).

#### Implementação e governança da Sprint 03 (PI2-233 / PI2-234)

No Jira Software, a **Sprint 03** corresponde à sprint ativa **`Week 15 e 16`** (Sprint ID 116, período `09/11/2026` a `23/11/2026`), estruturada sob facilitação do Scrum Master **Mateus Lacerda** com **36 itens no ciclo** e metas alinhadas à **Matriz RACI**.

> **Meta da Sprint (*Sprint Goal*):** *"Concluir todas as pendências, para entregarmos o jogo rodando em windows, documentação geral do projeto atualizada e regras de lógica aplicadas."*

#### Histórias de Usuário e Entregas Consolidadas na Sprint 03

| US / ID | Card no Jira | Descrição Funcional & Técnica | Módulos / Evidências no Repositório | SP | Situação (Ref. `main` / Jira) |
| :---: | :---: | :--- | :--- | :---: | :--- |
| **US17** | [PI2-218](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-218) / [PI2-215](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-215) | Modo Tutorial Guiado de AI Safety (Treinamento de Esquiva e Digitação) | `src/tutorial.c`, `src/tutorial.h`, `src/main.c` ([PR #13](https://github.com/vdornelass/pi2-squad-e7/pull/13), [`4a32f16`](https://github.com/vdornelass/pi2-squad-e7/commit/4a32f16), [`236da44`](https://github.com/vdornelass/pi2-squad-e7/commit/236da44)) | `3.0` | **Integrada na `main`** e **Concluída** (**4/4 CTs aprovados**) |
| **US18** | [PI2-219](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-219) / [PI2-216](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-216) | Interface Widescreen HD (`1280x720`), Fonte TrueType UTF-8 e Menu Principal Ilustrado | `src/config.h`, `src/ui.c`, `src/main.c` ([`a9c8bb4`](https://github.com/vdornelass/pi2-squad-e7/commit/a9c8bb4), [`2a82daa`](https://github.com/vdornelass/pi2-squad-e7/commit/2a82daa), [`a2173ba`](https://github.com/vdornelass/pi2-squad-e7/commit/a2173ba), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c)) | `3.0` | **Integrada na `main`** e **Concluída** (**4/4 CTs aprovados**, após o critério do menu ser atualizado no card) |
| **US19** | [PI2-220](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-220) | Sistema de Feedback Sonoro Sintetizado em C e Efeitos de Combate/Terminal (Issue [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3)) | `src/audio.c`, `src/audio.h`, `src/main.c` ([`6a8a9d4`](https://github.com/vdornelass/pi2-squad-e7/commit/6a8a9d4)) | `3.0` | **Integrada na `main`** (**6/6 CTs aprovados** na 2ª rodada) |
| **US20** | [PI2-246](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-246) / [PI2-247](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-247) | Exportação de Relatório de Auditoria (`bin/certificado.txt`/`.json`) e Certificado Ético | `src/report.c`, `src/report.h`, `Makefile` ([`ef37f30`](https://github.com/vdornelass/pi2-squad-e7/commit/ef37f30), [`9c9b832`](https://github.com/vdornelass/pi2-squad-e7/commit/9c9b832)) | `5.0` | **Integrada na `main`** (**4/4 CTs aprovados** na 3ª rodada, com hash de integridade · [PR #16](https://github.com/vdornelass/pi2-squad-e7/pull/16)) |
| **US16** | [PI2-217](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-217) / [PI2-221](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-221) | Identidade Visual e Ícone Personalizado no Executável (`.exe`) e Janela *(não contabilizada no total concluído)* | `src/icon.rc`, `src/icon_data.h`, `assets/aura67.ico` ([`3f7655d`](https://github.com/vdornelass/pi2-squad-e7/commit/3f7655d)) | `2.0` | **Concluída no Jira** em 23/11 (**4/4 CTs aprovados** depois do reteste de 26/11; ícone na barra de título corrigido no commit `43dcdc8`, issue [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17) fechada) |
| **PIF-02** | [PI2-254](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-254) | Portabilidade do launcher [`jogar.bat`](./jogar.bat) para execução em qualquer PC Windows | [`jogar.bat`](./jogar.bat) ([`939fe6e`](https://github.com/vdornelass/pi2-squad-e7/commit/939fe6e)) | `3.0` | **Integrada na `main`** e **Concluída** |
| **LMC-02** | [PI2-31](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-31) | Validação lógica formal da Unidade 2 e suíte automatizada (`make test-lmc`) | [`docs/relatorio_lmc_unidade2.md`](./docs/relatorio_lmc_unidade2.md), [`tests/test_logica_lmc.c`](./tests/test_logica_lmc.c), [`Makefile`](./Makefile) ([`e519ed1`](https://github.com/vdornelass/pi2-squad-e7/commit/e519ed1), [`f91402c`](https://github.com/vdornelass/pi2-squad-e7/commit/f91402c)) | `5.0` | **Concluída** (alvo `test-lmc` corrigido no `Makefile` com `src/ui.c` após ter quebrado na `main`) |
| **IHC-02** | [PI2-248](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-248) / [PI2-251](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-251) | Comprovação de usabilidade e auditoria visual das telas do produto final | `src/main.c`, `src/ui.c` ([`2a82daa`](https://github.com/vdornelass/pi2-squad-e7/commit/2a82daa)) | `10.0` | `PI2-251` **Concluída** · `PI2-248` em andamento |

#### Síntese do Acumulado de Histórias de Usuário (Meta da Rubrica: $\ge 15$ Histórias)
* **Sprint 01 (Entrega 03):** **7 Histórias de Usuário** entregues (`US01`, `US02`, `US03`, `US05`, `US06`, `US07`, `US13`).
* **Sprint 02 (Entrega 04):** **4 Novas Histórias de Usuário** entregues (`US11`, `US12`, `US14`, `US15`) → acumulado de 11 histórias.
* **Sprint 03 (Entrega 05):** **4 Novas Histórias de Usuário** integradas na `main` (`US17`, `US18`, `US19`, `US20`) — a `US16` ficou com 1 falha até 25/11 (issue #17) e não entrou nesta conta; corrigida e retestada em 26/11, ela soma uma 16ª história entregue.
* **Total Acumulado no Projeto:** **`7 + 4 + 4 = 15 Histórias de Usuário`** implementadas e testadas no acumulado das 3 sprints ([`docs/casos_de_teste_sprint01.md`](./docs/casos_de_teste_sprint01.md), [`sprint02`](./docs/casos_de_teste_sprint02.md) e [`sprint03`](./docs/casos_de_teste_sprint03.md)), atingindo exatamente a meta de **15 histórias acumuladas** exigida na Entrega 05.

#### Evidências do Board e Backlog na Sprint 03 (`Week 15 e 16`)

| Quadro da Sprint 03 (`Week 15 e 16`) | Backlog Priorizado no Jira |
| :---: | :---: |
| ![Print do Board da Sprint 03](./docs/img/print_board_sprint03.png) | ![Print do Backlog na Sprint 03](./docs/img/print_backlog_sprint03.png) |

#### Qualidade, sustentabilidade e documentação

* **Qualidade e testes (PI2-237 / PI2-238 / PI2-239):** [seção 6.4](#64-sprint-03-entrega-05--pi2-237--pi2-238--pi2-239).
* **Sustentabilidade (PI2-240 / PI2-241 / PI2-242):** [seção 7](#7-processo-e-sustentabilidade).
* **Documentação técnica final (PI2-222):** conferida com o código da `main` e com o Jira em 22/11/2026. Matriz US01 a US20 na [seção 5.2](#52-matriz-de-rastreabilidade-bidirecional-us01-a-us20), arquitetura na [seção 4](#4-arquitetura-e-estrutura-do-repositório), build na [seção 3](#3-como-executar) e no [`CONTRIBUTING.md`](./CONTRIBUTING.md), e [retrospectiva da Unidade 2](./docs/retrospectiva_unidade2.md).

---

## 9. Outras disciplinas do PI2 (FP2 e LMC)

### 9.1. Project Model Canvas (FP2)
* **Documento Completo do PM Canvas:** [Consulte o Project Model Canvas detalhado em docs/pm_canvas.md](./docs/pm_canvas.md)

### 9.2. Lógica Matemática para Computação (LMC — Entrega AV1)
* **Relatório Técnico e Especificação da Mecânica Lógica:** [Consulte a documentação completa em docs/relatorio_lmc_av1.md](./docs/relatorio_lmc_av1.md)
* **Arquivo Oficial em PDF para Submissão:** [Download do PDF da AV1 (docs/Relatorio_LMC_Projeto_Integrador_AV1.pdf)](./docs/Relatorio_LMC_Projeto_Integrador_AV1.pdf)
* **Atividade Prática Anterior (Refatoração de Condicionais via Lógica Clássica):** [Relatório em PDF](./docs/Relatorio_LMC_Refatoracao_Logica_23_09.pdf)

### 9.3. Lógica Matemática para Computação (LMC — Validação da Unidade 2 · PI2-31)
* **Relatório de validação lógica do motor em C99:** [docs/relatorio_lmc_unidade2.md](./docs/relatorio_lmc_unidade2.md) (máquina de estados, tabelas-verdade, invariantes das fases da AURA-67 e análise do game loop a 60 FPS)
* **Testes automatizados da validação:** [`tests/test_logica_lmc.c`](./tests/test_logica_lmc.c). Rode com `make test-lmc` (181 verificações)

---

## 10. Apresentação final

Cards: PI2-243 / PI2-244 / PI2-245 / PI2-256.

Apresentação técnica cronometrada de **15 minutos** estruturada rigorosamente nos **4 blocos obrigatórios** (*Produto*, *Processo de Trabalho*, *Engenharia* e *Time — com 1 slide individual por integrante respondendo: O que fez, O que não conseguiu fazer e O que aprendeu*):

* **Roteiro Cronometrado, Divisão de Falas & Dossiê de Processo (Projetos 2 / FDS):** [`docs/roteiro_apresentacao_final_pi2.md`](./docs/roteiro_apresentacao_final_pi2.md)
* **Slides Oficiais (PDF):** [`docs/apresentacao_final/apresentacao_final_squad_e7.pdf`](./docs/apresentacao_final/apresentacao_final_squad_e7.pdf)
* **Arquivo Editável (PowerPoint):** [`docs/apresentacao_final/apresentacao_final_squad_e7.pptx`](./docs/apresentacao_final/apresentacao_final_squad_e7.pptx)
