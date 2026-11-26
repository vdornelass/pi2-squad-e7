# Retrospectiva Técnica — Unidade 2 (Sprints 02 e 03)

**Projeto:** AI Safety: Alinhamento Ético da AURA-67 · Squad E7 · CESAR School (ADS 2026.2)
**Card:** [PI2-222](https://csprj-adsr-2p-e7.atlassian.net/browse/PI2-222) (Documentação FDS)
**Período:** 26/10/2026 a 23/11/2026 (Sprint 02 "Week 13 e 14" e Sprint 03 "Week 15 e 16")
**Organização:** Larissa Almeida (Lead FDS / QA), a partir dos relatórios de teste, do Issue Tracker, dos PRs e do board do Jira

---

## 1. Resultado da Unidade

| Item | Resultado |
| :--- | :--- |
| Histórias de usuário | 20 no backlog, todas com código na `main`. 15 contam como entregues e testadas até a Sprint 03. A US16 teve 1 falha até 25/11, foi corrigida e passou no reteste de 26/11 (ver [matriz no README, seção 5.2](../README.md#52-matriz-de-rastreabilidade-bidirecional-us01-a-us20)) |
| Testes de sistema | Sprint 02: 13 casos. Sprint 03: 27 casos em 4 rodadas. Depois da 3ª rodada eram 24 aprovados e 3 falhas; com as correções de 25/11, os 27 passaram no reteste de 26/11 ([`casos_de_teste_sprint03.md`](./casos_de_teste_sprint03.md)) |
| Testes automatizados | `make test-lmc` com 181 verificações de lógica (LMC) e `make verificar-certificado` para o hash do certificado (US20) |
| Issue Tracker | Fechadas com reteste: [#1](https://github.com/vdornelass/pi2-squad-e7/issues/1), [#2](https://github.com/vdornelass/pi2-squad-e7/issues/2), [#3](https://github.com/vdornelass/pi2-squad-e7/issues/3), [#7](https://github.com/vdornelass/pi2-squad-e7/issues/7), [#8](https://github.com/vdornelass/pi2-squad-e7/issues/8), [#12](https://github.com/vdornelass/pi2-squad-e7/issues/12), [#15](https://github.com/vdornelass/pi2-squad-e7/issues/15). Corrigidas em 25/11 e fechadas com reteste em 26/11: [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9), [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10), [#17](https://github.com/vdornelass/pi2-squad-e7/issues/17). Nenhuma issue aberta |
| Produto | Executável Windows (`bin/jogo.exe`, gerado com `make windows`) e versão Linux/WSL (`make run`) |

---

## 2. O que funcionou

* **Fluxo de branch, PR e revisão.** As histórias da Sprint 03 entraram por Pull Request com revisão de outro integrante antes do merge. Exemplos: o tutorial da US17 ([PR #13](https://github.com/vdornelass/pi2-squad-e7/pull/13)) e o hash de integridade da US20 ([PR #16](https://github.com/vdornelass/pi2-squad-e7/pull/16)). Na revisão do PR #16, o time decidiu tirar da tela do jogo o ID e o hash do certificado, porque o jogador não precisa dessas informações.
* **Testes ligados aos critérios do card.** Cada caso de teste foi escrito a partir dos critérios de aceitação (3Cs) do card no Jira, com vídeo ou print como evidência. Assim, quando um teste falhava, ficava claro qual critério não tinha sido atendido.
* **Ciclo bug → issue → correção → reteste.** Toda falha virou issue no GitHub, e cada issue só foi fechada depois de um reteste gravado. As falhas da Sprint 01 (Espaço contando como erro, W/A/S/D contando como erro e jogo sem som) foram todas corrigidas e retestadas na Unidade 2.
* **Testes automatizados para a parte crítica.** A suíte `make test-lmc` valida as regras de lógica do jogo. O `make verificar-certificado` confirma que o hash do certificado detecta alteração no arquivo.
* **Rastreabilidade melhor nos commits.** A partir da Sprint 03, os commits passaram a citar o card do Jira (ex.: `feat(PI2-246): ...`, `docs(fds): ... (PI2-238)`).

---

## 3. O que não funcionou

| Problema | Impacto | Causa |
| :--- | :--- | :--- |
| `make test-lmc` quebrou na `main` depois de um merge | A suíte de lógica parou de compilar até um commit de correção | `player.c` passou a depender de `ui.c`, e o alvo do Makefile não foi atualizado. O CI (`.github/workflows/build.yml`) só roda `make`, então não pegou o erro |
| O Makefile não recompila quando só um `.h` muda ([#10](https://github.com/vdornelass/pi2-squad-e7/issues/10)) | Mudanças em `config.h` não aparecem no jogo sem `make clean` | As regras do Makefile não listavam os headers como dependência. Corrigido em 25/11 (commit `43dcdc8`) |
| Áudio mudo no WSL | Parecia que a US19 não funcionava | Faltava a biblioteca de som do Linux (`libpulse0`) no WSL. O Raylib caía no backend "Null". Não era bug no código |
| Diff gigante no PR por causa de fim de linha (CRLF/LF) | O PR mostrava o arquivo inteiro como alterado e ficou difícil revisar | O repositório não tem `.gitattributes`, e cada máquina salva o fim de linha de um jeito |
| Ícone fora da barra de título ([#17](https://github.com/vdornelass/pi2-squad-e7/issues/17)) | 1 critério da US16 falhou | O ícone não era passado para a janela na criação. Corrigido em 25/11 (commit `43dcdc8`) e retestado em 26/11 |
| Sem aviso narrativo na troca de fase ([#9](https://github.com/vdornelass/pi2-squad-e7/issues/9)) | 1 critério da US12 falhou desde a Sprint 02 | Ficou sem responsável e passou duas sprints aberta. Corrigido só em 25/11 (commit `43dcdc8`) |
| Critérios de card desatualizados | Em US16, US18 e US20, o código mudou (menu ilustrado, ícone embutido, certificado `.txt`/`.json`) e o card não acompanhou. Os testes acusavam "falha" de algo que o time tinha decidido mudar | O card só foi atualizado depois do teste. O ajuste foi feito em 22/11 |
| Histórias da Unidade 1 sem teste formal | US04, US08, US09 e US14 não têm caso de teste próprio | Os casos de teste começaram na Sprint 01, só para as histórias daquela sprint |
| `jogo.exe` bloqueado pelo Windows (Smart App Control) | Em alguns PCs o jogo não abre com dois cliques | O executável não é assinado digitalmente |

---

## 4. Lições e ações para a próxima unidade

1. **Rodar os testes no CI**, e não só a compilação. Incluir `make test-lmc` e `make verificar-certificado` no `build.yml`, para que um merge que quebre a suíte seja barrado no PR.
2. **Atualizar o card junto com o código.** Se o time muda uma decisão (ex.: menu em texto → menu ilustrado), o critério do card é ajustado no mesmo PR, antes do teste.
3. **Escrever os casos de teste quando o card é criado**, e não só no fim da sprint. Isso evita histórias sem teste como as US04, US08, US09 e US14.
4. **Adicionar `.gitattributes`** com `* text=auto` para padronizar o fim de linha e deixar os diffs limpos.
5. **Manter as dependências do Makefile corretas.** A [#10](https://github.com/vdornelass/pi2-squad-e7/issues/10) foi corrigida em 25/11 listando os headers; ao criar um módulo novo, conferir que ele entra no `make`.
6. **Dar responsável e prazo para cada issue aberta** na planning da sprint, para que nenhuma fique duas sprints parada como a [#9](https://github.com/vdornelass/pi2-squad-e7/issues/9).
7. **Manter o ambiente de teste documentado.** O WSL com `libpulse0` e o bloqueio do Smart App Control já estão no [`CONTRIBUTING.md`](../CONTRIBUTING.md) (seções de solução de problemas). Todo problema de ambiente novo entra lá.
