# Relatório de Programação em Pares (*Pair Programming*) — Entrega 03 (FDS / PIF)
## Projeto: AI Safety — Alinhamento Ético da AURA-67
### Squad E7 | CESAR School — Projeto Integrador 2 (PI2)

> **Sprint de Referência:** Sprint 01 - U2 (`Week 12e13 - Protótipo` — ID 82 no Jira)  
> **Cards Relacionados (FDS):** [PI2-195](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-195), [PI2-207](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-207), [PI2-208](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-208) e [PI2-209](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-209)  
> **Linguagem & Stack:** C99 Puro (`-Wall -Wextra -std=c99 -pedantic`) + Raylib 5.0  

---

## 1. Estrutura das Duplas e Alocação RACI

| Dupla | Integrantes | Papel RACI | Cards no Jira | Foco Técnico e Módulos | Carga / Agenda |
| :---: | :--- | :--- | :--- | :--- | :--- |
| **Dupla 1** | **Matheus Chaves** & **Caio Brayner** | Motor em C / PIF | `PI2-80` (US14), `PI2-175`, `PI2-178`, `PI2-179` | Persistência binária (`src/save.c/h`), refatoração de estado (`src/game_state.c/h`) e fluxo completo de telas | Terça e Sexta (2h/sessão via Discord & VS Code Live Share) |
| **Dupla 2** | **Julio Cesar** & **João Gabriel** | LMC / Motor em C & Ranking | `PI2-77` (US11), `PI2-180`, `PI2-177`, `PI2-181` | Patches de alinhamento no console (`src/typing_engine.c/h`), ordenação de ranking e estatísticas em C (`src/ranking.c/h`) e unificação do loop (`src/main.c`) | Quarta e Sábado (2h/sessão via Discord) |
| **Dupla 3** | **Larissa Almeida** & **Theo Monteiro** | Engenharia FDS / QA & Testes | `PI2-194`, `PI2-202`, `PI2-203`, `PI2-204`, `PI2-205`, `PI2-206` | Especificação e execução dos 27 casos de teste de sistema, gravação de screencasts e gestão do Issue Tracker | Segunda e Quarta (2h30/sessão) |
| **Facilitação** | **Mateus Lacerda** | Scrum Master / Governança | `PI2-192`, `PI2-196`, `PI2-197`, `PI2-198`, `PI2-207`, `PI2-210` | Coordenação do cronograma, atualização do Jira Board e consolidação das evidências visuais no `README.md` | Acompanhamento contínuo na Sprint |

---

## 2. Detalhamento das Sessões por Dupla (Driver / Navigator)

---

### 2.1. Dupla 1: Persistência Binária & Arquitetura de Estado em C
* **Integrantes:** Matheus Chaves & Caio Brayner (*RACI: Motor em C / PIF*)
* **Cards / Histórias no Board:**
  * [PI2-80](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-80) (*US14: Persistência de Progresso — Save/Load binário `bin/savegame.dat`*)
  * [PI2-175](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-175) (*Módulo `src/save.c` e `src/save.h`*)
  * [PI2-178](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-178) (*Refatoração de estado global `src/game_state.c` e `src/game_state.h`*)
  * [PI2-179](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-179) (*Integração do fluxo completo: menu, combate, vitória/derrota, save e ranking*)
* **Horários / Carga:** Terça-feira e Sexta-feira (2h por sessão via Discord e VS Code Live Share).
* **Dinâmica de Papéis:**
  * **Sessão 1:** **Matheus Chaves** (*Driver* — implementação da serialização binária `fwrite`/`fread` com validação de *magic number* `0x41555241` e exportação CSV de partidas) / **Caio Brayner** (*Navigator* — revisão de ponteiros e sincronização dos campos de `SaveData` com o estado da partida).
  * **Sessão 2:** **Caio Brayner** (*Driver* — encapsulamento do contexto global na struct `GameContext` em `src/game_state.c/h` e eliminação de warnings de compilação) / **Matheus Chaves** (*Navigator* — revisão e testes funcionais das opções de menu `[C] Continuar Jogo Salvo` e `[K] Ver Ranking`).
* **Desafios e Aprendizados:**
  * O principal desafio técnico foi garantir que a leitura binária restaurasse com exatidão a fase da AURA-67, o HP do jogador e o índice da diretriz ética sem corromper o buffer de entrada do Raylib. A revisão em par permitiu detectar rapidamente a necessidade de limpar a fila de caracteres (`GetCharPressed()`) ao reiniciar ou carregar uma partida.

---

### 2.2. Dupla 2: Patches de Alinhamento & Módulo de Ranking e Estatísticas em C
* **Integrantes:** Julio Cesar & João Gabriel (*RACI: LMC / Motor em C & Ranking*)
* **Cards / Histórias no Board:**
  * [PI2-77](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-77) (*US11: Inserção de Patches de Alinhamento no Núcleo da AURA-67*)
  * [PI2-180](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-180) (*Console central de diretrizes e métricas de precisão em tempo real*)
  * [PI2-177](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-177) (*Módulo em C de ranking ordenado e estatísticas das partidas — `src/ranking.c` e `src/ranking.h`*)
  * [PI2-181](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-181) (*Unificação dos módulos `game_state`, `save` e `ranking` no loop principal em C e build Windows*)
* **Horários / Carga:** Quarta-feira e Sábado (2h por sessão via Discord).
* **Dinâmica de Papéis:**
  * **Sessão 1:** **Julio Cesar** (*Driver* — lógica de validação de patches no console central, cálculo de precisão percentual `typing_engine_get_accuracy()` e desacoplamento das teclas de movimentação `WASD` / barra de espaço `[_]`) / **João Gabriel** (*Navigator* — verificação das regras de transição de alinhamento e formatação dos dados exportados para o histórico).
  * **Sessão 2:** **João Gabriel** (*Driver* — implementação do módulo `src/ranking.c/h` com ordenação decrescente via `qsort`, agregação de estatísticas de `bin/matches.csv` e unificação final no `src/main.c`) / **Julio Cesar** (*Navigator* — inspeção de tipos em C99 estrito e validação da tela de Ranking e Estatísticas de Auditoria).
* **Desafios e Aprendizados:**
  * O maior desafio foi resolver a colisão entre as teclas de movimentação (`WASD`) e o motor de digitação em tempo real, além do disparo duplicado da barra de espaço entre `GetCharPressed()` e `IsKeyPressed(KEY_SPACE)`. O pareamento permitiu desenhar uma solução limpa em C99 puro e padronizar a interface entre `save.c`, `ranking.c` e `game_state.c`.

---

### 2.3. Dupla 3: Engenharia de Qualidade, Testes de Sistema e Rastreabilidade
* **Integrantes:** Larissa Almeida & Theo Monteiro (*RACI: Engenharia FDS / QA & Testes*)
* **Cards / Histórias no Board:**
  * [PI2-194](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-194) (*3. Qualidade e testes — Entrega 03 FDS*)
  * [PI2-202](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-202) (*Elaboração dos 27 Casos de Teste de Sistema em `docs/casos_de_teste_sprint01.md`*)
  * [PI2-203](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-203) (*Execução dos testes de sistema e registro dos resultados*)
  * [PI2-204](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-204) / [PI2-205](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-205) (*Gravação e anexação dos screencasts dos testes de sistema*)
  * [PI2-206](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-206) (*Registro e atualização dos bugs no Issue Tracker do GitHub — Issues #1, #2 e #3*)
* **Horários / Carga:** Segunda-feira e Quarta-feira (2h30 por sessão).
* **Dinâmica de Papéis:**
  * **Larissa Almeida** (*Driver* — estruturação e redação formal dos 27 cenários de teste com pré-condições, entradas, resultados esperados e minutagem nos vídeos) / **Theo Monteiro** (*Navigator* — conferência cruzada contra os critérios de confirmação 3Cs no Jira, catalogação das Issues no GitHub e documentação colaborativa no `README.md`).
* **Desafios e Aprendizados:**
  * Transformar os critérios de aceitação de cada história em casos de teste reproduzíveis e sincronizados por minutagem com os vídeos exigiu alto rigor metodológico. A atuação em dupla garantiu que falhas reais de input fossem isoladas, documentadas em Issues formais e imediatamente repassadas para correção no código C.

---

### 2.4. Facilitação Ágil (Scrum Master)
* **Responsável:** Mateus Lacerda
* **Atuação:** Coordenação do cronograma da Sprint, organização e higienização do Jira Board (`PI2-192`, `PI2-196` a `PI2-198`), consolidação da matriz de duplas (`PI2-207`) e publicação das evidências visuais do quadro (`PI2-210`).

---

## 3. Rastreabilidade de Commits e Pull Requests por Dupla

| Dupla / Responsável | Cards no Jira | Módulos / Arquivos Principais | Commits / PRs no GitHub |
| :--- | :--- | :--- | :--- |
| **Dupla 1:** Matheus Chaves & Caio Brayner | `PI2-80`, `PI2-175`, `PI2-178`, `PI2-179` | `src/save.c`, `src/save.h`, `src/game_state.c`, `src/game_state.h`, `src/main.c` | [`1b0e96f`](https://github.com/vdornelass/pi2-squad-e7/commit/1b0e96f), [`61206dd`](https://github.com/vdornelass/pi2-squad-e7/commit/61206dd), [`d671026`](https://github.com/vdornelass/pi2-squad-e7/commit/d671026) |
| **Dupla 2:** Julio Cesar & João Gabriel | `PI2-77`, `PI2-180`, `PI2-177`, `PI2-181`, `PI2-27`, `PI2-28` | `src/ranking.c`, `src/ranking.h`, `src/typing_engine.c`, `src/ui.c`, `src/main.c`, `Makefile` | [`b296cb2`](https://github.com/vdornelass/pi2-squad-e7/commit/b296cb2), [`5b80d72`](https://github.com/vdornelass/pi2-squad-e7/commit/5b80d72), [`2483c92`](https://github.com/vdornelass/pi2-squad-e7/commit/2483c92) |
| **Dupla 3:** Larissa Almeida & Theo Monteiro | `PI2-193`, `PI2-194`, `PI2-195`, `PI2-202` a `PI2-206`, `PI2-209`, `PI2-211` | `docs/casos_de_teste_sprint01.md`, `docs/roteiro-screencast-entrega03.md`, `README.md` | [`254dbcc`](https://github.com/vdornelass/pi2-squad-e7/commit/254dbcc), [`b8d01e2`](https://github.com/vdornelass/pi2-squad-e7/commit/b8d01e2), [`7e8f110`](https://github.com/vdornelass/pi2-squad-e7/commit/7e8f110), [`343d3ae`](https://github.com/vdornelass/pi2-squad-e7/commit/343d3ae) (PR #4) |
| **Scrum Master:** Mateus Lacerda | `PI2-192`, `PI2-196` a `PI2-198`, `PI2-207`, `PI2-210` | `README.md` (Seção 9.2), `docs/img/print_board_sprint2_completo.png` | [`15dbcb1`](https://github.com/vdornelass/pi2-squad-e7/commit/15dbcb1), [`487d1d3`](https://github.com/vdornelass/pi2-squad-e7/commit/487d1d3) (PR #5) |
