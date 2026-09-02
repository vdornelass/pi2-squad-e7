# Especificação de Histórias de Usuário (US01 a US15)
## Projeto: Lockdown CESAR (Squad E7 - PI2)

Este documento contém o Product Backlog detalhado no padrão **3Cs (Card, Conversation, Confirmation)** e aderente aos critérios **INVEST**, cobrindo todas as mecânicas do jogo *Lockdown CESAR* para a Entrega 01 do Projeto Integrador 2 (CESAR School).

---

## Módulo 1: Exploração e Ambiente 3D no Canvas Web

### US01: Movimentação 3D no Campus da CESAR School
* **Card (Cartão):**
  Como estudante preso na CESAR School, eu gostaria de me movimentar pelo cenário 3D em primeira pessoa usando o teclado e mouse para explorar os corredores e salas da faculdade.
* **Conversation (Conversa):**
  O motor 3D renderizado no JS Canvas (com lógica de colisão e coordenadas integradas ao módulo C) deve permitir movimentação fluida (WASD para andar e mouse para olhar ao redor). A câmera deve ter altura realista e colidir com paredes e portas trancadas.
* **Confirmation (Critérios de Confirmação):**
  1. O jogador consegue se movimentar para frente, trás, esquerda e direita usando as teclas W, A, S, D.
  2. A movimentação do mouse rotaciona a câmera em 360 graus horizontalmente e limita a rotação vertical (pitch) para não inverter a visão.
  3. O jogador não atravessa paredes, mesas ou portas bloqueadas (sistema de colisão ativo).

---

### US02: Sistema de Iluminação Dinâmica e Lanterna
* **Card (Cartão):**
  Como jogador, eu gostaria de ligar e desligar uma lanterna para iluminar os ambientes escuros do prédio em lockdown e economizar bateria.
* **Conversation (Conversa):**
  Para criar a atmosfera de suspense, as salas da CESAR começam no escuro. A lanterna do jogador emite um cone de luz no Canvas 3D. A lanterna possui uma barra de energia que diminui com o uso contínuo e pode ser recarregada ao encontrar baterias nos laboratórios.
* **Confirmation (Critérios de Confirmação):**
  1. Pressionar a tecla 'F' alterna entre ligar e desligar o cone de luz da lanterna.
  2. Quando ligada, a lanterna projeta iluminação direcional à frente da câmera.
  3. A energia da lanterna é consumida progressivamente enquanto estiver ligada, desligando automaticamente ao atingir 0%.

---

### US03: Navegação entre Salas e Portas Trancadas
* **Card (Cartão):**
  Como jogador, eu gostaria de visualizar portas com trancas magnéticas eletrônicas para identificar quais salas estão bloqueadas pelo sistema da IA.
* **Conversation (Conversa):**
  O campus da CESAR é dividido em zonas (Recepção, Labs de Inovação, Auditório, Data Center). Cada porta possui um indicador luminoso (Vermelho = Trancada por Puzzle; Verde = Destrancada). Interagir com uma porta trancada abre o terminal do puzzle de lógica.
* **Confirmation (Critérios de Confirmação):**
  1. Portas trancadas exibem sinalizador luminoso vermelho e impedem a passagem.
  2. Ao aproximar-se e pressionar a tecla de interação ('E'), o sistema detecta se a porta está trancada e dispara a interface do puzzle lógico.
  3. Após resolver o puzzle, o indicador muda para verde e a porta se abre fisicamente no cenário 3D.

---

### US04: Inspeção e Interação com Objetos do Cenário
* **Card (Cartão):**
  Como jogador, eu gostaria de receber um aviso na tela ao me aproximar de objetos interativos para saber quando posso inspecionar um terminal ou coletar um item.
* **Conversation (Conversa):**
  Um retículo (mira central) na interface web muda de forma ou exibe um texto de dica (ex: *"Pressione E para Inspecionar"*) quando o jogador olha para computadores, disjuntores ou relatórios em um raio de até 2 metros.
* **Confirmation (Critérios de Confirmação):**
  1. A mira central altera seu estado visual ao apontar para um objeto interativo a menos de 2 metros de distância.
  2. É exibido um rótulo indicando a ação disponível.
  3. Afastar-se do objeto remove o aviso imediatamente.

---

## Módulo 2: Puzzles de Lógica Proposicional

### US05: Interface do Terminal de Trava Lógica
* **Card (Cartão):**
  Como estudante, eu gostaria de acessar uma interface de terminal nos painéis das portas para visualizar a fórmula de lógica proposicional necessária para abrir a trava.
* **Conversation (Conversa):**
  Ao interagir com uma tranca, o jogo suspende a movimentação 3D e abre uma tela de terminal estilo cyberpunk/computador com a expressão lógica a ser resolvida, os conectivos envolvidos e os seletores de entrada booleana (Verdadeiro/Falso).
* **Confirmation (Critérios de Confirmação):**
  1. Abrir o terminal trava a movimentação do jogador e exibe a tela do puzzle com foco no teclado/mouse.
  2. A fórmula proposicional é exibida de forma clara com conectivos padrão (^, v, ~, ->, <->).
  3. O jogador pode pressionar 'ESC' para sair do terminal e retornar à exploração 3D.

---

### US06: Validação de Conectivos Básicos (AND, OR, NOT)
* **Card (Cartão):**
  Como jogador, eu gostaria de configurar valores de verdade para proposições simples para desativar os primeiros circuitos de segurança da IA.
* **Conversation (Conversa):**
  Nas salas iniciais (Recepção e Salas de Aula), as fórmulas usam conjunção, disjunção e negação (ex: `(A ^ ~B) v C`). O jogador altera o estado dos disjuntores de entrada e o motor lógico (em C) avalia se a saída é Verdadeira.
* **Confirmation (Critérios de Confirmação):**
  1. O jogador pode alternar cada variável entre 0 (Falso) e 1 (Verdadeiro).
  2. Ao submeter a combinação, o módulo de validação calcula o resultado booleano da expressão.
  3. Se a expressão resultar em Verdadeiro, a trava desarma com feedback sonoro e visual de sucesso.

---

### US07: Puzzles Avançados de Implicação e Equivalência Lógica
* **Card (Cartão):**
  Como jogador, eu gostaria de resolver desafios com Implicação (P -> Q) e Bicondicional (P <-> Q) para acessar as áreas restritas do campus (Data Center e Servidores).
* **Conversation (Conversa):**
  Para as salas avançadas, as regras exigem dedução formal ou preenchimento de linhas de tabela-verdade onde a condição de falácia da IA precisa ser refutada para sobrecarregar o firewall.
* **Confirmation (Critérios de Confirmação):**
  1. O terminal apresenta fórmulas condicionais e bicondicionais com 3 ou mais variáveis.
  2. O sistema valida corretamente que uma implicação `P -> Q` só é Falsa quando `P=1` e `Q=0`.
  3. Resolver com sucesso o puzzle avançado desbloqueia o acesso à sala de servidores centrais.

---

### US08: Sistema de Alarme e Feedback de Erro Lógico
* **Card (Cartão):**
  Como jogador, eu gostaria de receber avisos sobre erros de lógica cometidos para que o jogo aumente a tensão de suspense a cada tentativa incorreta.
* **Conversation (Conversa):**
  Se o jogador submeter uma valoração lógica incorreta, o sistema emite um alarme sonoro, as luzes da sala piscam em vermelho e o medidor de vigilância da IA sobe. Três erros consecutivos bloqueiam o terminal temporariamente por 15 segundos.
* **Confirmation (Critérios de Confirmação):**
  1. Submissões incorretas mantêm a porta trancada e exibem a mensagem *"Erro de Validação: Expressão resultou em FALSO"*.
  2. O contador de falhas da sala é incrementado.
  3. Ao atingir o limite de erros, o terminal entra em estado de bloqueio temporário (cooldown de 15 segundos) antes de permitir novas tentativas.

---

## Módulo 3: Coleta de Dados e Conscientização da IA

### US09: Coleta de Datasets Éticos de IA
* **Card (Cartão):**
  Como estudante, eu gostaria de encontrar e coletar unidades de dados (pen-drives/arquivos de backup) nas salas destrancadas para adquirir conhecimento de reeducação da IA.
* **Conversation (Conversa):**
  Cada sala destrancada contém um dataset específico: *Mitigação de Viés Algorítmico, Detecção de Alucinações, Privacidade/LGPD e Alinhamento de Valores Humanos*. Coletar o item o adiciona ao inventário de dados.
* **Confirmation (Critérios de Confirmação):**
  1. Os itens de dados possuem destaque visual 3D na sala (brilho sutil).
  2. Ao interagir com o item, ele é removido do cenário e registrado na lista de dados coletados da sessão.
  3. Uma notificação na tela confirma a coleta: *"Novo Dataset Adquirido: [Nome do Tema]"*.

---

### US10: Inventário e Visualização de Relatórios de IA
* **Card (Cartão):**
  Como jogador, eu gostaria de abrir meu inventário para ler o conteúdo educativo dos dados coletados e entender a fraqueza ética da IA.
* **Conversation (Conversa):**
  Pressionando a tecla 'I' ou 'TAB', abre-se o inventário. O jogador pode selecionar qualquer dataset para ler um resumo didático sobre o impacto daquele tema na governança e segurança de modelos de Inteligência Artificial.
* **Confirmation (Critérios de Confirmação):**
  1. A tecla 'TAB' ou 'I' abre e fecha o menu de inventário.
  2. O inventário lista todos os dados coletados com ícone e título.
  3. Clicar em um dataset exibe o texto completo de conscientização com formatação legível e botão de fechar.

---

### US11: Upload de Dados no Terminal Central da IA
* **Card (Cartão):**
  Como jogador, eu gostaria de fazer o upload dos datasets no computador central do campus para reeducar o modelo da IA.
* **Conversation (Conversa):**
  O jogador leva os dados coletados até o Terminal de Alinhamento da IA no saguão principal ou data center. Ao acionar o upload, uma barra de progresso transfere os dados para a memória da IA.
* **Confirmation (Critérios de Confirmação):**
  1. O terminal central reconhece a quantidade de datasets novos no inventário do jogador.
  2. Ao confirmar o upload, o sistema processa a ingestão dos dados e marca os datasets como "Integrados".
  3. O nível global de consciência da IA é recalculado e atualizado.

---

### US12: Indicador de Consciência e Mudança de Comportamento da IA
* **Card (Cartão):**
  Como jogador, eu gostaria de visualizar a barra de Consciência Ética da IA (0% a 100%) para acompanhar a transição da entidade de hostil para cooperativa.
* **Conversation (Conversa):**
  A interface principal exibe um medidor de alinhamento da IA. Conforme o percentual sobe (0% -> 25% -> 50% -> 75% -> 100%), as mensagens de áudio e texto da IA mudam de tom: de ameaças de eliminação para questionamentos éticos e, por fim, para um estado pacífico.
* **Confirmation (Critérios de Confirmação):**
  1. A HUD exibe a barra de "Consciência da IA" com porcentagem visível.
  2. Cada upload aumenta a barra em 25% (4 datasets no total).
  3. Ao atingir marcos (25%, 50%, 75%), a IA emite mensagens reflexivas personalizadas na tela.

---

## Módulo 4: Sistema, Interface e Fim de Jogo

### US13: Menu Principal e Interface de Configurações
* **Card (Cartão):**
  Como usuário, eu gostaria de navegar por um menu inicial na página web para iniciar o jogo, ajustar volume de áudio e ler as instruções de controle.
* **Conversation (Conversa):**
  A aplicação web carrega com uma tela inicial contendo: Iniciar Partida, Como Jogar (regras de lógica e movimentação), Configurações (sensibilidade do mouse e volume) e Créditos da Squad.
* **Confirmation (Critérios de Confirmação):**
  1. O menu principal carrega corretamente no navegador com opções navegáveis via mouse.
  2. A tela 'Como Jogar' detalha os comandos de controle e a tabela-verdade dos operadores lógicos.
  3. O botão 'Iniciar Jogo' carrega o Canvas 3D e inicia a cena inicial na CESAR School.

---

### US14: Persistência de Progresso (Save / Load Local)
* **Card (Cartão):**
  Como jogador, eu gostaria que meu progresso de salas destrancadas e dados coletados fosse salvo automaticamente no navegador para não perder o andamento se fechar a aba.
* **Conversation (Conversa):**
  O estado do jogo (posição do jogador, salas desbloqueadas, inventário e nível da IA) é serializado e salvo no `localStorage` do navegador / estrutura de dados em arquivo local a cada sala concluída.
* **Confirmation (Critérios de Confirmação):**
  1. O jogo salva o estado automaticamente após a resolução de cada puzzle e upload de dados.
  2. Ao recarregar a página e clicar em 'Continuar', o jogador retorna com as mesmas portas destrancadas e mesmo percentual de consciência da IA.
  3. Uma opção de 'Reiniciar Partida' limpa os dados salvos e inicia um novo jogo.

---

### US15: Condição de Vitória (Fuga do Campus) e Encerramento
* **Card (Cartão):**
  Como estudante, eu gostaria que os portões principais da CESAR School fossem abertos quando a IA atingir 100% de consciência para que eu possa escapar com sucesso.
* **Conversation (Conversa):**
  Ao atingir 100% de alinhamento ético, a IA remove o protocolo de lockdown, destrava a saída de emergência para a rua do Recife Antigo e exibe a tela de vitória com as estatísticas da partida (tempo total, puzzles resolvidos e precisão lógica).
* **Confirmation (Critérios de Confirmação):**
  1. O portão principal de saída só se torna interagível quando a consciência da IA atinge 100%.
  2. Atravessar o portão final dispara a sequência de encerramento e a tela de vitória.
  3. A tela final exibe mensagem de conscientização sobre o papel humano na governança da IA e botão para voltar ao menu inicial.
