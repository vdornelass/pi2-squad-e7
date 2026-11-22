# Roteiro Oficial da Apresentação Final & Dossiê de Processo — Squad E7

> **Projeto:** *AI Safety: Alinhamento Ético da AURA-67* (Projeto Integrador 2 — CESAR School, ADS 2026.2)  
> **Cards no Jira:** [PI2-243](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-243) · [PI2-245](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-245) (*5. Apresentação Final — Entrega 05 FDS, 26/11*) · [PI2-256](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-256) (*Projetos 2 — Apresentação Final e Avaliação de Processo, Prof. Robson Godoi, 24/11*)  
> **Responsável / Facilitação:** Mateus Almeida de Lacerda (Scrum Master — FP2 / Engenharia de Software — FDS)  
> **Deck de Slides Associado:** [`apresentacao_final_squad_e7.pdf`](./apresentacao_final/apresentacao_final_squad_e7.pdf) · [`apresentacao_final_squad_e7.pptx`](./apresentacao_final/apresentacao_final_squad_e7.pptx)  
> **Duração Máxima Rigorosa:** **15 minutos** (seguidos de arguição da banca)

---

## 1. Estrutura Geral & Cronometragem Oficial (15 Minutos)

O roteiro segue integralmente os **4 blocos obrigatórios** da rubrica de FDS (*"O produto é uma parte. O processo é o assunto."*) e os critérios de avaliação de processo de **Projetos 2 (peso 4 na nota individual)**, distribuindo a fala de forma equilibrada pelos integrantes da Squad E7 dentro dos **25 slides** do deck oficial:

| Bloco | Slides | Tópico & Objetivo na Rubrica | Responsável(is) pela Fala | Tempo Alocado | Janela |
| :--- | :---: | :--- | :--- | :---: | :---: |
| **Abertura** | 1–2 | Contextualização da Squad E7, agenda e tese (*AI Safety*) | **Mateus Lacerda** | `0:30` | `00:00 – 00:30` |
| **01. Produto** | 3–5 | Problema, público, diferencial e **demo ao vivo** (`bin/jogo.exe`) | **Matheus Chaves** & **Caio Brayner** | `2:30` | `00:30 – 03:00` |
| **02. Processo** | 6–9 | Práticas ágeis (real × ideal), 9 Sprints no Jira, RACI, Riscos e rastreabilidade `3Cs → Commit` | **Mateus Lacerda** | `4:00` | `03:00 – 07:00` |
| **03. Engenharia** | 10–14 | Arquitetura C99 modular, CI/Git/PRs, `CONTRIBUTING.md`, QA (testes manuais + `181/181` LMC), Issues e DoD | **João Gabriel**, **Larissa Almeida** & **Theo Monteiro** | `4:00` | `07:00 – 11:00` |
| **04. Time** | 15–25 | Lições aprendidas, resposta a *"Viramos um time?"* e síntese individual (*Fez / Não conseguiu / Aprendizagem*) | **Julio Cesar**, **Jhorge Araújo** + rodada rápida dos **8 membros** | `4:00` | `11:00 – 15:00` |
| **TOTAL** | **1–25** | **Apresentação Completa (Margem de segurança: 0–15s)** | **Todos os 8 integrantes** | **`15:00`** | **`00:00 – 15:00`** |

> [!IMPORTANT]
> **Regra do Ensaio Cronometrado (`PI2-245` / `PI2-256`):** Cada apresentador deve respeitar rigorosamente sua janela de tempo. Em `14:45`, o facilitador sinaliza para encerramento imediato no Slide 25 (*Links do repositório e Release*).

---

## 2. Roteiro Detalhado por Bloco (Fala + Evidência Visual)

### Abertura (`00:00 – 00:30` · Slides 1 e 2) — Mateus Lacerda
* **Slide 1 (Capa):** Apresentar a Squad E7 e o projeto **AI Safety: Alinhamento Ético da AURA-67** (*CESAR School — PI2*).
* **Slide 2 (Roteiro):** Explicar a divisão dos 15 minutos entre **Produto**, **Processo de Trabalho**, **Engenharia de Software** e **Time**, destacando a premissa central da disciplina: mostrar como o processo sustentou a entrega técnica de ponta a ponta.

---

### Bloco 1 — Produto (`00:30 – 03:00` · Slides 3 a 5) — Matheus Chaves & Caio Brayner
* **Slide 3–4 (Pitch & Proposta de Valor — `01:00` — Matheus Chaves):**
  * **Problema:** Usuários interagem diariamente com modelos de IA sem compreender riscos reais como viés nos dados, alucinações, *prompt injection* e convergência instrumental.
  * **Público-alvo:** Estudantes de tecnologia e usuários de IA que buscam aprender *AI Safety* de forma prática e interativa, sem depender apenas de artigos teóricos.
  * **Diferencial:** Jogo *bullet hell + typing* em C99/Raylib 5.0 onde *"sua missão não é destruir a AURA-67, mas reprogramá-la"*.
* **Slide 5 (Mecânica & Demo Rápida — `01:30` — Caio Brayner):**
  * Demonstrar ao vivo o build final Windows/WSL via [`jogar.bat`](../jogar.bat) (`bin/jogo.exe` / WSL):
    1. **Menu Principal & Tutorial (`US18` / `US17`):** janela widescreen `1280x720`, fonte TrueType UTF-8 com acentos PT-BR, **Modo Tutorial Guiado** (`src/tutorial.c`), Configurações e Ranking;
    2. **Arena + Terminal em 60 FPS:** esquiva com `WASD`/Setas/Mouse contra projéteis, lasers e vórtice enquanto digita 10 diretrizes constitucionais ao longo das 3 fases cognitivas da AURA-67;
    3. **Feedback & Pós-Jogo:** efeitos sonoros sintetizados em C (`US19`), tela de vitória com Certificado/Relatório de Alinhamento Ético em `.txt`/`.json` (`US20`) e Ranking Top 10 (`US15`).

---

### Bloco 2 — Processo de Trabalho & Dossiê Avaliação Peso 4 (`03:00 – 07:00` · Slides 6 a 9) — Mateus Lacerda

> **Foco direto na rubrica de Projetos 2 (`PI2-256`) e FDS:** transparência radical sobre o que foi adotado, o que foi adaptado e quais evidências auditáveis comprovam a governança do grupo.

#### 2.1. Matriz de Práticas Ágeis (Adotadas Totalmente × Parcialmente × Não Adotadas — Slide 7)

| Classificação | Práticas | Evidência Concreta no Projeto |
| :--- | :--- | :--- |
| **Adotadas Totalmente** | • **Sprints de 1 a 2 semanas** (9 sprints planejadas e executadas no Jira)<br>• **Backlog 3Cs + INVEST & MoSCoW** (`US01` a `US20`)<br>• **Kanban Board** (`Tarefas pendentes` → `Em andamento` → `Concluído`)<br>• **Scrum Master dedicado** e **Matriz RACI formal por frente**<br>• **Programação em Pares** (*Driver/Navigator* documentado nas Sprints 01, 02 e 03)<br>• **Feature Branch por Card (`PI2-XXX`)** | Board oficial `PI2` (ID 2), [`docs/historias_de_usuario.md`](./historias_de_usuario.md), [`docs/relatorio_pair_programming_sprint01.md`](./relatorio_pair_programming_sprint01.md), [`sprint02`](./relatorio_pair_programming_sprint02.md) e [`sprint03`](./relatorio_pair_programming_sprint03.md) |
| **Adotadas Parcialmente / Adaptadas** | • **Dailies:** adaptadas para alinhamentos curtos no Discord e **check-in assíncrono diário no WhatsApp** (mitigação pós-Atividade 4 de FP2, pois horários entre os 8 membros variavam)<br>• **Code Review / PR:** nem 100% dos commits passaram por Pull Request na U1; processo amadureceu na U2 via PRs #4, #5, #6, #11 e regras em `CONTRIBUTING.md`<br>• **Testes Automatizados:** foco em testes de sistema manuais com screencasts nas Sprints 01–02; automação lógica (`181` asserts) adicionada na Sprint 03 (`make test-lmc`)<br>• **Story Points:** ausentes nos cards da U1, padronizados e equilibrados na U2 (Sprint `Week 13 e 14` e Sprint `Week 15 e 16`) | Histórico de PRs no GitHub, `tests/test_logica_lmc.c` e Aba de Lista no Jira |
| **Não Adotadas** | • **TDD (Test-Driven Development):** não escrevemos testes antes da implementação da camada gráfica em C/Raylib | Optamos por validação por casos de teste de sistema derivados dos Critérios de Confirmação (`3Cs`) |

#### 2.2. Evolução Histórica das 9 Sprints no Jira (`Week 01` a `Week 15 e 16` — Slide 8)
* **9 Sprints executadas de 03/08 a 23/11/2026:** `W01 Kick-Off` → `W02-03 Pesquisa` → `W04-05 Protótipo C` → `W06-07 Núcleo em C` → `W08-09 Fecha U1` → `W10-11 Evolução` → `W12 Protótipo` → `W13-14 Sprint 02` → `W15-16 Sprint 03 / Entrega Final`.
* **Métricas Consolidadas do Jira (`PI2`):** **206+ itens gerenciados** entre Épicos, Histórias (`US01–US20`) e Subtarefas, **>83% de taxa de conclusão** acumulada, com meta explícita de fechamento em Windows, documentação geral e validação lógica.

#### 2.3. Governança RACI, Gestão de Riscos (FP2) e Balanceamento de Carga (Slide 9)
* **Rastreabilidade Ponta a Ponta:** *História (3Cs + MoSCoW) → Card Jira (`PI2-XXX`) com RACI → Branch/Commit (`PI2-XXX`) → Caso de Teste de Sistema / Issue Tracker* (exemplo prático: bug da barra de espaço em `US06` gerou Issue `#1`, corrigida e retestada na Sprint 02).
* **Equilíbrio de Carga na Sprint 03 (`Week 15 e 16`):** Após auditoria da **Aba de Lista** em `09/11`, redistribuímos tickets ociosos/sobrecarregados seguindo a RACI oficial — garantindo que os 7 membros em sprint atuassem em suas disciplinas `R (Executores)` com carga equilibrada (**4 a 5 tickets / 8 a 10 SP cada**), enquanto `Jhorge Araújo` assumiu consultoria de arquitetura/LMC e a entrega do TechNight LMC (`PI2-255`).
* **Controle de Riscos Finais (Atividade 4 de FP2):**
  * **R1/R2 (Acúmulo 20–26/11):** Classificação MoSCoW + marcos intermediários (`20/11` código, `22/11` roteiro/slides, `23/11` *Code Freeze* e ensaio);
  * **R3 (Dependência de IHC e mídia):** Testes de sistema executados em duas rodadas (`19–20/11`) com gravação antecipada no PC Windows para validar áudio (`US19`);
  * **R5 (Avaliação de Processo Peso 4 em 24/11):** Criação formal do card `PI2-256`, evidências consolidadas no `README.md` e ensaio obrigatório até `23/11`.

---

### Bloco 3 — Engenharia de Software & Qualidade (`07:00 – 11:00` · Slides 10 a 14) — João Gabriel, Larissa Almeida & Theo Monteiro
* **Slide 11 (Arquitetura & Desenvolvimento — `01:20` — João Gabriel):**
  * Código modular em **C99 estrito + Raylib 5.0** rodando a **60 FPS** (**15 Histórias de Usuário acumuladas concluídas**: `7` Sprint 01 + `4` Sprint 02 + `4` Sprint 03 `US17–US20`, sem contar `US16` parcial);
  * **12 módulos `.c` integrados em `src/`:** `main`, `game_state`, `player`, `boss`, `bullet` (até 800 projéteis), `typing_engine`, `tutorial` (`US17`), `ui` (1280×720 + TrueType UTF-8), `save` (`0x41555241`), `ranking` (`qsort`), `audio` (PCM 16-bit sintetizado) e `report` (certificado `.txt`/`.json` — `US20`).
* **Slide 12 (Gerência de Configuração & Sustentabilidade — `01:00` — João Gabriel):**
  * Fluxo *Feature Branch* + *Conventional Commits* com `PI2-XXX` + Templates de PR/Issue + CI no GitHub Actions (`.github/workflows/build.yml` compilando com `-Wall -Wextra -std=c99 -pedantic`);
  * Guia autossuficiente [`CONTRIBUTING.md`](../CONTRIBUTING.md) validado para setup no Windows (`jogar.bat`/MinGW, alerta de *Smart App Control* e PowerShell) e Linux/WSL (`make` / `make test-lmc`).
* **Slide 13–14 (Qualidade, Testes e DoD — `01:40` — Larissa Almeida & Theo Monteiro):**
  * **Testes de Sistema (Larissa):** 3 rodadas formais documentadas com minutagem em vídeo ([`sprint01`](./casos_de_teste_sprint01.md): 27 CTs; [`sprint02`](./casos_de_teste_sprint02.md): 12 CTs + reteste; [`sprint03`](./casos_de_teste_sprint03.md): 27 CTs em duas rodadas cobrindo `US16`–`US20` e regressão). Bug Tracker ativo no GitHub Issues (`#1`, `#2`, `#3`, `#7`, `#8`, `#9`, `#10`, `#12`).
  * **Validação Lógica Automatizada LMC (Theo):** [`docs/relatorio_lmc_unidade2.md`](./relatorio_lmc_unidade2.md) + `tests/test_logica_lmc.c` com 181 verificações lógicas (`make test-lmc` corrigido no `Makefile` com `src/ui.c` no commit `f91402c`) e 4 achados arquiteturais (`A1–A4`) documentados para o time.
  * **Definition of Done (Slide 14):** Card só fecha quando atende 3Cs + build sem warnings no CI + revisão em PR + testes de sistema + evidência anexada no Jira/README.

---

### Bloco 4 — Time, Lições Aprendidas & Reflexão Crítica (`11:00 – 15:00` · Slides 15 a 25) — Todos

* **Slide 16 (Lições Aprendidas & "O grupo se tornou um time?" — `01:00` — Julio Cesar & Jhorge Araújo):**
  * **4 Lições-Chave:** (1) Escrever 3Cs antes acelera a escrita dos casos de teste; (2) Testes independentes revelam bugs invisíveis ao dev (`WASD`/Espaço, `11/10`, falta de acento); (3) Documentar o código real, não o planejado no papel; (4) Integrar na `main` cedo — código parado em máquina local atrasa a release.
  * **Resposta Honesta (*"Viramos um time?"*):** **Sim.** Saímos de 8 alunos divididos por matérias isoladas para uma squad com revisão cruzada entre duplas, testes independentes e visibilidade compartilhada no Board.

#### Síntese Oficial dos 8 Slides Individuais (`11:00 – 14:40` · ~25s por membro · Slides 17 a 24)

Cada integrante apresenta seu próprio slide respondendo às **3 perguntas obrigatórias da rubrica**:

| Integrante (Slide) | 1. O que fez | 2. O que não conseguiu fazer | 3. O que aprendeu |
| :--- | :--- | :--- | :--- |
| **Caio Brayner** *(Slide 17)* | Struct central `GameContext` (`game_state`), pontuação/alinhamento (`PI2-90`), Boss e projéteis, certificado `US20` (`report.c`) e `jogar.bat` portátil | Corrigir mais cedo arquivos duplicados de teste e manter `jogar.bat` independente desde a U1 *(atualizado na reta final com `939fe6e` e `54652d2`)* | Centralizar estado do jogo em uma única `struct` e integrar módulos em C em equipe sem quebrar o build |
| **Jhorge Araújo** *(Slide 18)* | Aprovador (`A`) de IHC e LMC na matriz RACI, consultoria de arquitetura do motor em C e revisão das regras lógicas do relatório LMC | Acompanhar o código de perto em todos os sprints e assumir cards de execução contínua na Sprint 03 | Traduzir lógica proposicional para regras reais de jogo e revisar arquitetura antes do código crescer |
| **João Gabriel** *(Slide 19)* | Ranking/estatísticas (`PI2-177`), unificação do loop principal (`PI2-181`), áudio sintetizado (`US19`), ícone (`US16`) e CI no GitHub Actions | Revisar 100% dos PRs antes do merge e publicar a release final com mais antecedência | Integrar módulos de múltiplos autores no mesmo loop em C99 e sintetizar áudio PCM direto em memória |
| **Julio Cesar** *(Slide 20)* | Laço de combate/rodadas (`PI2-89`), motor de digitação/precisão (`typing_engine.c`), Modo Tutorial Guiado (`US17`, PR #13) e relatório de usabilidade IHC | Integrar o modo tutorial (`US17`) na `main` antes da 1ª rodada de testes e automatizar os testes de digitação | Desacoplar teclas de movimentação (`WASD`) da digitação e auditar interfaces pelas heurísticas de IHC |
| **Larissa Almeida** *(Slide 21)* | Casos de teste de sistema das Sprints 01, 02 e 03, screencasts com minutagem, gestão de Issues no GitHub, matriz de rastreabilidade e seções de Qualidade do `README.md` | Automatizar os testes de interface gráfica e retestar em tempo hábil todas as issues abertas desde a Sprint 01 | Transformar critérios de aceite 3Cs em casos de teste reproduzíveis e usar vídeo cronometrado como evidência auditável |
| **Mateus Lacerda** *(Slide 22)* | Gestão ágil do Jira (9 sprints, 3Cs, RACI, balanceamento), Seções 10/11 do `README.md`, matriz de duplas, `CONTRIBUTING.md` autossuficiente e roteiro da apresentação final | Realizar retrospectivas síncronas formais ao fim de cada sprint e manter atualização diária síncrona do Board nas semanas de prova | Facilitar uma equipe de 8 integrantes com agendas distintas e manter o Jira + GitHub sincronizados como fonte única da verdade |
| **Matheus Chaves** *(Slide 23)* | Save/load binário com validação `0x41555241` (`PI2-175`), protótipos/storyboards, interface Widescreen 720p e Menu CLI (`US18`), fonte TrueType (`PI2-259`), consistência visual (`PI2-252`) e usabilidade | Validar protótipos com usuários externos fora da squad e implementar transições animadas avançadas entre telas | Implementar serialização binária segura em C e prototipar telas antes de codificar para evitar retrabalho |
| **Theo Monteiro** *(Slide 24)* | Validação lógica formal da Unidade 2 (`PI2-31`: `181/181` asserts em `make test-lmc`), catalogação de Issues/evidências, relatório de Pair Programming Sprint 03 (`PI2-242`), deck de slides (`PI2-244`) e Atividade 4 de FP2 (`PI2-257`) | Automatizar a suíte lógica desde a primeira sprint e entrar na base de código C antes da reta final | Validar formalmente o código real contra as especificações dos cards usando lógica matemática e testes automatizados |

* **Encerramento (`14:40 – 15:00` · Slide 25 — Mateus Lacerda):** Agradecer à banca, exibir o link oficial do repositório (`github.com/vdornelass/pi2-squad-e7`) e da release final, e abrir espaço para perguntas.

---

## 3. Checklist de Prontidão & Notas de Atualização Antes de 24/11 e 26/11

Este checklist garante o cumprimento integral de **`PI2-256` (Projetos 2 — 24/11)** e **`PI2-243` / `PI2-245` (Entrega 05 FDS — 26/11)**:

- [x] **Roteiro estruturado em 4 blocos e dividido entre os 8 integrantes** até `22/11` ([este documento](./roteiro_apresentacao_final_pi2.md))
- [x] **Deck de slides oficial no repositório** cobre os 4 blocos e contém **1 slide por integrante** ([PDF](./apresentacao_final/apresentacao_final_squad_e7.pdf) · [PPTX](./apresentacao_final/apresentacao_final_squad_e7.pptx))
- [x] **Evidências de Processo organizadas para 24/11 (Peso 4 — Prof. Robson Godoi):** Board do Jira atualizado, 9 sprints rastreadas, Matriz RACI no `README.md`, histórico de commits semanais e `CONTRIBUTING.md` autossuficiente
- [x] **Slide 11 e Slide 20 atualizados no PPTX/PDF (`~4.000 linhas`, `12 módulos .c/.h`, `102+ commits`, incluindo `tutorial.c` e `report.c`)**; para revisão final antes do *Code Freeze* (`23/11`), confirmar apenas se o time deseja ajustar o Slide 7 (*Story Points* adotados na U2).
- [ ] **Code Freeze do build Windows (`23/11`):** Conferir `make clean`, `make`, `make test-lmc` (um comando por linha no PowerShell via `wsl`) e `.\jogar.bat` rodando liso na máquina de apresentação (incluindo áudio da `US19`).
- [ ] **Ensaio Geral Cronometrado com os 8 Integrantes (`23/11`):** Rodar simulação completa cronometrada confirmando término em até `14:45` antes das apresentações de **24/11 (Projetos 2)** e **26/11 (FDS)**.
