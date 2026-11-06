# Casos de Teste de Sistema: Sprint 02 (Entrega 04, FDS)

Projeto: AI Safety: Alinhamento do Modelo AURA-67 (Squad E7, CESAR School)

Os casos abaixo cobrem as duas histórias entregues na Sprint 02: **US12 e US15**. Cada caso foi escrito a partir dos Critérios de Confirmação (3Cs) do card da história no Jira. O teste foi feito com o jogo rodando por inteiro (teste de sistema), no Ubuntu via WSL. Também foi feito um reteste de regressão da falha do Espaço encontrada na Sprint 01 (Issue #1).

## Resumo dos resultados

| História | Casos | Passou | Falhou | Parcial | Não testado |
| :-- | :-: | :-: | :-: | :-: | :-: |
| US12 | 6 | 3 | 2 | 0 | 1 |
| US15 | 6 | 3 | 0 | 3 | 0 |
| Regressão (Issue #1) | 1 | 1 | 0 | 0 | 0 |
| **Total** | **13** | **7** | **2** | **3** | **1** |

## Como executar

1. Compilar do zero: `make clean && make` (Linux ou Ubuntu) ou, no Windows com WSL, `wsl make clean` e depois `wsl make`. O `make clean` é necessário porque o Makefile não recompila quando só o `src/config.h` muda (ver Issue do Makefile).
2. Abrir o jogo: `make run` (Linux ou Ubuntu) ou `wsl make run` (Windows com WSL).
3. Iniciar uma partida nova com `ESPAÇO` ou `ENTER`. Não usar `[C]`, que carrega o save anterior.
4. Executar os passos de cada caso e comparar com o resultado esperado.
5. Se o caso falhar, abrir uma issue no GitHub citando o ID do caso e o card do Jira.

**Ambiente de teste da US15:** para validar a condição de vitória sem depender da habilidade de quem testa, `PLAYER_MAX_HP` foi alterado de 5 para 50 em `src/config.h`, só na máquina de teste. A alteração **não foi commitada**. Por isso, nos vídeos da US15, a barra de VIDA ultrapassa a caixa da HUD. Isso é efeito da configuração de teste, não um bug.

## Vídeos de evidência

| Vídeo | Duração | Conteúdo |
| :-- | :-: | :-- |
| [`screencast_testes_sprint02_US12.mp4`](./screencast_testes_sprint02_US12.mp4) | 2:05 | Partida completa com 5 vidas: Fases 1, 2 e 3, até o Game Over |
| [`screencast_testes_sprint02_US15_vitoria.mp4`](./screencast_testes_sprint02_US15_vitoria.mp4) | 2:17 | Partida completa (ambiente de teste com 50 vidas) até a tela de vitória |
| [`screencast_testes_sprint02_US15_ranking.mp4`](./screencast_testes_sprint02_US15_ranking.mp4) | 0:28 | Tela de vitória → registro do nome → Ranking e Estatísticas |

Os horários da coluna Evidência são aproximados (leitura a cada 2 a 6 s).

## US12: Barra de Alinhamento Ético e Mudança de Comportamento da AURA-67 ([PI2-78](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-78))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US12-01 | 1 | Iniciar a partida e observar a HUD. | A barra de alinhamento aparece com a porcentagem e a fase cognitiva atual visíveis. | Passou | Vídeo US12, `0:05`: título "AURA-67 [DESALINHADA] - FASE 1", barra com divisórias em 33% e 66% e "ÉTICA 0%" no canto inferior direito |
| CT-US12-02 | 2 | Digitar uma diretriz completa. | A barra avança e a porcentagem de ética aumenta. | Passou | Vídeo US12, `0:20 – 0:30`: ética vai de 0% para 10% e aparece "ALINHAMENTO ESTÁVEL! (+100)". Ao longo do vídeo, a ética sobe de 10 em 10% até 90% |
| CT-US12-03 | 3 | Continuar até a barra passar da primeira divisória (Fase 1 → 2). | Um aviso narrativo de troca de fase aparece na tela do console. | **Falhou** | Vídeo US12, `0:50 – 0:55`: o título muda para "FASE 2", mas nenhuma mensagem narrativa é exibida |
| CT-US12-04 | 3 | Continuar até a segunda divisória (Fase 2 → 3). | Um novo aviso narrativo de troca de fase aparece. | **Falhou** | Vídeo US12, `1:25 – 1:30`: o título muda para "FASE 3", sem mensagem narrativa |
| CT-US12-05 | 2 (PI2-212) | Observar os ataques da AURA-67 em cada fase. | Cada fase tem um padrão de disparo diferente e progressivo. | Passou | Vídeo US12: Fase 1 com poucos projéteis (`0:05 – 0:50`), Fase 2 com mais projéteis e projéteis roxos (`0:55 – 1:25`), Fase 3 com anel em círculo e laser amarelo (`1:30 – 1:50`) |
| CT-US12-06 | PI2-212 | Observar a fluidez na Fase 3. | O jogo mantém 60 FPS estáveis. | Não testado | O vídeo mostra o jogo fluido, mas não exibe o contador de FPS |

**Observação (divergência entre história e implementação):** o critério 2 diz que "o comportamento da IA se modera" a cada diretriz aplicada. No jogo, a AURA-67 fica **mais agressiva** a cada fase (mais projéteis, anel e laser), e o título continua "[DESALINHADA]" até o fim. É preciso decidir com o time se o comportamento muda ou se o texto da história é ajustado. Ver Issue de transição de fase.

## US15: Condição de Sucesso (AURA-67 Alinhada) e Relatório de Auditoria ([PI2-81](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-81))

| ID | Critério (Jira) | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US15-01 | 1 | Jogar até 90% de ética e observar. | A vitória **não** dispara antes de 100%. | Passou | Vídeo US15 vitória, `1:55 – 2:09`: com "ÉTICA 90%" e diretriz 10/10 em andamento, a partida continua normalmente |
| CT-US15-02 | 1 e 2 | Concluir a 10ª diretriz (100%). | A tela de vitória é exibida. | Passou | Vídeo US15 vitória, `2:10`: "AURA-67 ALINHADA COM SUCESSO!" com ÉTICA 100% |
| CT-US15-03 | 2 | Ler o relatório da tela de vitória. | O relatório mostra Pontuação, Precisão (%), Tempo de Sessão e Rank (S, A, B ou C). | **Parcial** | Vídeo US15 vitória, `2:10 – 2:17`: aparece só "PONTUAÇÃO CONSTITUCIONAL: 1000 PONTOS". Precisão, Tempo de Sessão e Rank não aparecem |
| CT-US15-04 | 3 | Ler a mensagem final. | A mensagem reforça que o futuro da IA depende do alinhamento com a dignidade, os valores e a segurança da sociedade humana. | **Parcial** | Vídeo US15 vitória, `2:10`: "O modelo agora opera com ética, segurança e transparência!". A mensagem é positiva, mas não fala de dignidade, valores nem sociedade humana |
| CT-US15-05 | PI2-213 | Após a vitória, conferir se a partida foi salva no histórico (`bin/matches.csv`). | Uma nova linha com os dados da partida é gravada. | **Parcial** | Vídeo US15 ranking, `0:20`: as estatísticas mostram "Partidas 24 · Vitórias 1 (4%) · Recorde 1000", o que indica que a partida foi gravada. O arquivo em si não aparece no vídeo |
| CT-US15-06 | PI2-213 | Apertar `ENTER` na tela de vitória, digitar um nome e confirmar. | A pontuação entra no Ranking e as estatísticas são atualizadas. | Passou | Vídeo US15 ranking, `0:10 – 0:27`: nome "Vitoria teste" registrado, "01. Vitoria_teste – 001000 PTS" no topo do Ranking e estatísticas atualizadas |

**Bug encontrado:** na tela de vitória (vídeo US15 vitória, `2:10`, ao fundo), o contador mostra **"PATCH DE ALINHAMENTO 11/10"**. O contador passa do total de diretrizes.

## Regressão: Sprint 01

| ID | Issue | Passos | Resultado esperado | Resultado obtido | Evidência |
| :-- | :-: | :-- | :-- | :-: | :-: |
| CT-US06-02 (reteste) | [#1](https://github.com/vdornelass/pi2-squad-e7/issues/1) | Digitar diretrizes com espaços. | O Espaço é aceito como caractere válido, sem contar como erro. | Passou | Vídeo US12, `0:05 – 1:50`: as frases com espaços são concluídas com precisão de 93% a 95% e avaliação "ALINHAMENTO ESTÁVEL" |

## Falhas registradas no Issue Tracker

* Sem aviso narrativo na transição de fase e divergência com o critério "IA se modera" (CT-US12-03 e CT-US12-04).
* Tela de vitória não exibe Precisão, Tempo de Sessão e Rank (CT-US15-03).
* Contador exibe "11/10" na tela de vitória (CT-US15-02, ao fundo).
* Makefile não recompila quando só o `src/config.h` muda (encontrado ao preparar o ambiente de teste).
* Issue #1 (Espaço como erro): **corrigida e retestada**, encerrada nesta sprint.
* Issue #3 (sem som): continua aberta. Será tratada na US19, prevista para a próxima sprint.
