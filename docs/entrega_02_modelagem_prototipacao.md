# Entrega 02 — Estrutura de Modelagem, Rastreabilidade e Demonstração (FDS)
## Projeto: AI Safety — Alinhamento do Modelo AURA-67 (Squad E7 — PI2)

> **Documento de Infraestrutura e Rastreabilidade (FDS)**  
> **Responsável:** Larissa Almeida (Lead de Engenharia de Software)  
> **Status:** Estrutura e Matriz de Rastreabilidade concluídas pela Lead; aguardando submissão dos artefatos visuais pelos responsáveis.

---

## 1. Planejamento da Modelagem (Diagramas de Atividades UML)

Em conformidade com as diretrizes da Entrega 02 de Engenharia de Software (FDS), a modelagem de comportamento está estruturada para cobrir **10 Histórias de Usuário (US01 a US10)**, distribuída entre os membros responsáveis:

| ID | História de Usuário | Card no Jira | Responsável na Squad | Status |
| :---: | :--- | :---: | :---: | :--- |
| **US01** | Movimentação e Esquiva na Arena | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | Caio Brayner (`PI2-112`) | Em elaboração |
| **US02** | HUD de Combate, Integridade e Alinhamento | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | Julio Cesar (`PI2-113`) | Em elaboração |
| **US03** | Fases Cognitivas e Padrões da AURA-67 | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | Jhorge Araújo (`PI2-114`) | Em elaboração |
| **US04** | Efeitos de Status Adversariais | [PI2-70](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-70) | Squad E7 | Em elaboração |
| **US05** | Terminal de Inserção de Diretrizes | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | Squad E7 | Em elaboração |
| **US06** | Validação de Digitação em Tempo Real | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | Squad E7 | Em elaboração |
| **US07** | Avaliação de Precisão e Patches | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | Squad E7 | Em elaboração |
| **US08** | Tratamento de Exceções e Penalidade | [PI2-74](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-74) | Squad E7 | Em elaboração |
| **US09** | Coleta de Datasets Constitucionais | [PI2-75](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-75) | Squad E7 | Em elaboração |
| **US10** | Painel de Auditoria e Score | [PI2-76](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-76) | Squad E7 | Em elaboração |

---

## 2. Prototipação Lo-Fi no Figma (IHC)

* **Link Oficial do Projeto no Figma:** [Acessar Protótipo Lo-Fi no Figma](https://www.figma.com/design/BJ1f5Y5TF1yfq1C3jVvRRZ/Sem-t%C3%ADtulo?node-id=0-1&t=RmzS9WKzO4lqzsr6-1)  
  *(Aguardando liberação de acesso 'Anyone with the link can view' por Caio Brayner).*
* **Sketches e Storyboard:** A infraestrutura de publicação no README está pronta, aguardando a exportação das telas finais e storyboards por Matheus Chaves, Caio Brayner, Mateus Lacerda e Theo Monteiro (`PI2-118`, `PI2-119`, `PI2-120`, `PI2-121`).

---

## 3. Matriz de Rastreabilidade Bidirecional

Elaborada pela Lead de Engenharia (Larissa Almeida), esta matriz formaliza a conexão entre Requisitos, Histórias de Usuário, Cards de Gestão no Jira, artefatos previstos e módulos de implementação em C99:

| US | Requisito / Card Jira | Diagrama Previsto | Tela Prevista no Figma | Módulo em C (Código) |
| :---: | :---: | :---: | :---: | :---: |
| **US01** | [PI2-67](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-67) | `AD-US01` | Gameplay Arena | [`src/player.c`](../src/player.c) |
| **US02** | [PI2-68](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-68) | `AD-US02` | HUD / Arena | [`src/ui.c`](../src/ui.c) |
| **US03** | [PI2-69](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-69) | `AD-US03` | Chefe / Arena | [`src/boss.c`](../src/boss.c) |
| **US04** | [PI2-70](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-70) | `AD-US04` | Debuffs / Arena | [`src/player.c`](../src/player.c) |
| **US05** | [PI2-71](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-71) | `AD-US05` | Terminal Neural | [`src/typing_engine.c`](../src/typing_engine.c) |
| **US06** | [PI2-72](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-72) | `AD-US06` | Tutorial / Terminal | [`src/typing_engine.c`](../src/typing_engine.c) |
| **US07** | [PI2-73](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-73) | `AD-US07` | Terminal / HUD | [`src/typing_engine.c`](../src/typing_engine.c) |
| **US08** | [PI2-74](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-74) | `AD-US08` | Arena / HUD | [`src/player.c`](../src/player.c) |
| **US09** | [PI2-75](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-75) | `AD-US09` | Arena Gameplay | [`src/bullet.c`](../src/bullet.c) |
| **US10** | [PI2-76](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-76) | `AD-US10` | Painel de Score | [`src/ui.c`](../src/ui.c) |

---

## 4. Planejamento da Demonstração (Screencast)

Roteiro narrativo e falas completas preparados por Larissa Almeida (`PI2-127`) para orientar a gravação do screencast assim que os fluxos do Figma estiverem desbloqueados:

* **Documento Completo de Falas e Minutagem:** [Consulte o roteiro detalhado em docs/roteiro_screencast_pi2_127.md](./roteiro_screencast_pi2_127.md)
* **Critérios de Aceitação:** Vídeo de 1 a 3 minutos (planejado em 02:15), com narração em áudio e/ou legendas, demonstrando o fluxo principal da solução.
* **Sequência Planejada:**
  1. **Abertura e Apresentação do Escopo (00:00 – 00:25):** Visão panorâmica do Figma e introdução da Squad E7 e do projeto AI Safety.
  2. **US01: Movimentação e Esquiva na Arena (00:25 – 00:55):** Demonstração dos comandos WASD, 60 FPS e contenção aos limites da arena retangular.
  3. **US02: HUD de Combate e Alinhamento Ético (00:55 – 01:30):** Telemetria das 5 vidas, barra de alinhamento da AURA-67 (0% a 100%) e prompt neural.
  4. **US03: Fases Cognitivas da IA (01:30 – 02:00):** Visualização sequencial das 3 fases do chefe (Viés de Dados, Jailbreak e Convergência Instrumental).
  5. **Encerramento e Rastreabilidade (02:00 – 02:15):** Fechamento e conexão com os Diagramas UML e a Matriz de Rastreabilidade.
