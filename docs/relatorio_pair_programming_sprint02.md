# Relatório de Programação em Pares (*Pair Programming*) — Entrega 04 (FDS / PIF)
## Projeto: AI Safety — Alinhamento Ético da AURA-67
### Squad E7 | CESAR School — Projeto Integrador 2 (PI2)

> **Sprint de Referência:** Sprint 02 - U2 (`Week 13 e 14` — ID 83 no Jira)  
> **Cards Relacionados (FDS):** [PI2-223](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-223), [PI2-225](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-225), [PI2-230](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-230), [PI2-231](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-231) e [PI2-226](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-226)  
> **Linguagem & Stack:** C99 Puro (`-Wall -Wextra -std=c99 -pedantic`) + Raylib 5.0  

---

## 1. Estrutura das Duplas e Alocação RACI (Sprint 02)

| Dupla | Integrantes | Papel RACI | Cards no Jira | Foco Técnico e Módulos | Carga / Agenda |
| :---: | :--- | :--- | :--- | :--- | :--- |
| **Dupla 1** | **Matheus Chaves** & **Caio Brayner** | Motor em C / PIF | `PI2-80` (US14), `PI2-175`, `PI2-178`, `PI2-179` | Finalização da persistência binária (`src/save.c/h`), máquina de estados consolidada (`src/game_state.c/h`) e integração de save/load ao loop de combate | Terça e Sexta (2h/sessão via Discord & VS Code Live Share) |
| **Dupla 2** | **Julio Cesar** & **João Gabriel** | LMC / Motor em C & Ranking | `PI2-77` (US11), `PI2-78` (US12), `PI2-81` (US15), `PI2-177`, `PI2-181`, `PI2-31` | Tabela de recordes com `qsort` (`src/ranking.c/h`), patches e motor de digitação (`src/typing_engine.c/h`) e otimização de ciclos de clock (LMC) | Quarta e Sábado (2h/sessão via Discord) |
| **Dupla 3** | **Larissa Almeida** & **Theo Monteiro** | Engenharia FDS / QA & Testes | `PI2-224`, `PI2-227`, `PI2-228`, `PI2-229`, `PI2-232` | Especificação e execução dos testes de sistema da Sprint 02, gravação de screencasts, gestão de bugs e validação de deploy em produção | Segunda e Quarta (2h30/sessão) |
| **Facilitação** | **Mateus Lacerda** | Scrum Master / Governança | `PI2-223`, `PI2-225`, `PI2-230`, `PI2-231` | Planejamento da Sprint 02, garantia da meta de 5+ histórias adicionais (10+ acumuladas), prints do Board/Backlog e governança ágil no README | Acompanhamento diário contínuo |

---

## 2. Detalhamento das Sessões por Dupla (Driver / Navigator)

---

### 2.1. Dupla 1: Persistência Binária e Estabilidade da Máquina de Estados
* **Integrantes:** Matheus Chaves & Caio Brayner (*RACI: Motor em C / PIF*)
* **Cards / Histórias no Board:**
  * [PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80) (*US14: Persistência de Progresso — Save/Load binário `bin/savegame.dat`*)
  * [PI2-178](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-178) (*Estabilização da transição de estados `src/game_state.c/h`*)
  * [PI2-179](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-179) (*Loop contínuo de combate com salvamento de checkpoint automático*)
* **Horários / Carga:** Terça e Sexta-feira (2h por sessão).
* **Dinâmica de Papéis:**
  * **Sessão 1:** **Matheus Chaves** (*Driver* — validação da integridade de leitura/escrita do cabeçalho de salvamento e verificação de checksum de integridade) / **Caio Brayner** (*Navigator* — acompanhamento do fluxo de controle e garantia de que nenhum ponteiro pendente fosse desreferenciado durante a serialização).
  * **Sessão 2:** **Caio Brayner** (*Driver* — integração do gatilho de salvamento ao concluir uma diretriz ética e ao transicionar para Game Over/Vitória) / **Matheus Chaves** (*Navigator* — validação no console de depuração e prevenção de concorrência com o loop de renderização da Raylib).
* **Desafios e Aprendizados:**
  * A serialização direta de estruturas em C99 exige alinhamento rígido de memória. A programação em pares permitiu definir explicitamente os tipos de tamanho fixo (`uint32_t`, `int32_t`) em `save.h`, evitando incompatibilidades entre compiladores GCC em ambientes Windows (MinGW) e Linux (WSL/Ubuntu).

---

### 2.2. Dupla 2: Motor de Digitação, Ranking Ordenado e Validação LMC
* **Integrantes:** Julio Cesar & João Gabriel (*RACI: LMC / Motor em C & Ranking*)
* **Cards / Histórias no Board:**
  * [PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77) (*US11: Inserção de patches no núcleo da IA e cálculo de precisão de alinhamento*)
  * [PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78) (*US12: Telas de Game Over e Vitória com relatório analítico de alinhamento*)
  * [PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81) (*US15: Tabela de recordes com ordenação decrescente via `qsort` e persistência CSV*)
  * [PI2-31](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-31) (*Validação LMC e otimização de ciclos de instrução no loop principal*)
* **Horários / Carga:** Quarta-feira e Sábado (2h por sessão).
* **Dinâmica de Papéis:**
  * **Sessão 1:** **João Gabriel** (*Driver* — implementação da função comparadora de `qsort` em `src/ranking.c` para pontuação decrescente e persistência em `bin/matches.csv`) / **Julio Cesar** (*Navigator* — validação matemática do cálculo de precisão percentual e testes de borda com pontuações idênticas).
  * **Sessão 2:** **Julio Cesar** (*Driver* — refatoração da rotina de captura de teclado em `src/typing_engine.c` para mitigar conflito com teclas de movimento `WASD` e espaçamento) / **João Gabriel** (*Navigator* — inspeção de código estático com `-Wall -Wextra -pedantic` garantindo aderência estrita à especificação C99).
* **Desafios e Aprendizados:**
  * A ordenação estável de structs em C requer tratamento cuidadoso de empates de pontuação (critério de desempate por tempo e acurácia). Trabalhar em dupla acelerou a resolução do bug de captura de caracteres múltiplos no Raylib (`GetCharPressed`), garantindo digitação fluida a 60 FPS.

---

### 2.3. Dupla 3: Qualidade, Bateria de Testes de Sistema e Deploy
* **Integrantes:** Larissa Almeida & Theo Monteiro (*RACI: Engenharia FDS / QA & Testes*)
* **Cards / Histórias no Board:**
  * [PI2-224](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-224) (*3. Qualidade e testes — Entrega 04 FDS*)
  * [PI2-227](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-227) (*Execução dos Testes de Sistema da Sprint 02 e screencasts*)
  * [PI2-228](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-228) (*Issue/Bug Tracker no GitHub e validação de correções*)
  * [PI2-229](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-229) (*2. Produto em produção — Entrega 04 FDS*)
  * [PI2-232](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-232) (*Deploy funcional e screencast com URL pública*)
* **Horários / Carga:** Segunda-feira e Quarta-feira (2h30 por sessão).
* **Dinâmica de Papéis:**
  * **Larissa Almeida** (*Driver* — elaboração dos cenários de teste de sistema das novas histórias US11, US12, US14 e US15, verificação das regras de aceitação 3Cs e gravação de screencasts) / **Theo Monteiro** (*Navigator* — estruturação dos fluxos de automação de build/deploy, conferência dos links nos cards do Jira e documentação dos resultados).
* **Desafios e Aprendizados:**
  * A sincronização entre testes funcionais e gravação com legendas evidenciando os critérios de aceite exigiu planejamento prévio dos roteiros. A cooperação em dupla assegurou rastreabilidade bidirecional entre cada card do Jira e suas respectivas evidências.

---

### 2.4. Facilitação Ágil e Governança do Processo (Scrum Master)
* **Responsável:** Mateus Lacerda
* **Atuação:** 
  * Gestão estratégica do Jira Board (`PI2-223`, `PI2-225`, `PI2-230`, `PI2-231`), garantindo a preservação do Product Backlog com as histórias `US16` a `US19` para a próxima sprint.
  * Validação das metas da Sprint 02 (10+ histórias acumuladas, alcançando 14 no total integrado).
  * Consolidação da cadência semanal de commits (Semanas 36 a 43) e atualização dos prints oficiais do Board e Backlog no `README.md`.

---

## 3. Rastreabilidade de Commits e Pull Requests por Dupla (Sprint 02)

| Dupla / Responsável | Cards no Jira | Módulos / Arquivos Principais | Commits / PRs no GitHub |
| :--- | :--- | :--- | :--- |
| **Dupla 1:** Matheus Chaves & Caio Brayner | `PI2-80`, `PI2-175`, `PI2-178`, `PI2-179` | `src/save.c`, `src/save.h`, `src/game_state.c`, `src/game_state.h`, `src/main.c` | [`1b0e96f`](https://github.com/vdornelass/pi2-squad-e7/commit/1b0e96f), [`61206dd`](https://github.com/vdornelass/pi2-squad-e7/commit/61206dd), [`d671026`](https://github.com/vdornelass/pi2-squad-e7/commit/d671026) |
| **Dupla 2:** Julio Cesar & João Gabriel | `PI2-77`, `PI2-78`, `PI2-81`, `PI2-177`, `PI2-181`, `PI2-31` | `src/ranking.c`, `src/ranking.h`, `src/typing_engine.c`, `src/ui.c`, `src/main.c`, `Makefile` | [`b296cb2`](https://github.com/vdornelass/pi2-squad-e7/commit/b296cb2), [`5b80d72`](https://github.com/vdornelass/pi2-squad-e7/commit/5b80d72), [`2483c92`](https://github.com/vdornelass/pi2-squad-e7/commit/2483c92) |
| **Dupla 3:** Larissa Almeida & Theo Monteiro | `PI2-224`, `PI2-227`, `PI2-228`, `PI2-229`, `PI2-232` | `docs/casos_de_teste_sprint01.md`, `README.md`, screencasts | [`254dbcc`](https://github.com/vdornelass/pi2-squad-e7/commit/254dbcc), [`7e8f110`](https://github.com/vdornelass/pi2-squad-e7/commit/7e8f110), [`343d3ae`](https://github.com/vdornelass/pi2-squad-e7/commit/343d3ae) (PR #4) |
| **Scrum Master:** Mateus Lacerda | `PI2-223`, `PI2-225`, `PI2-230`, `PI2-231` | `README.md` (Seção 10), `docs/relatorio_pair_programming_sprint02.md`, prints do Board e Backlog | [`15dbcb1`](https://github.com/vdornelass/pi2-squad-e7/commit/15dbcb1), [`487d1d3`](https://github.com/vdornelass/pi2-squad-e7/commit/487d1d3) (PR #5) |
