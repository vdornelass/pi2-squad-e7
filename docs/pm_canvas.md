# Project Model Canvas (PM Canvas)
## Projeto: Lockdown CESAR (Squad E7 — PI2)

O **Project Model Canvas (PM Canvas)** sintetiza a estratégia, escopo, requisitos e planejamento do projeto *Lockdown CESAR*, integrando as diretrizes da disciplina de **Frameworks de Processos 2 (FP2)** da CESAR School.

---

```text
+---------------------------------------------------------------------------------------------------------------+
|                                           PROJECT MODEL CANVAS                                                |
+-------------------+-------------------+-------------------+-------------------+-------------------------------+
| POR QUE?          | O QUE?            | QUEM?             | COMO?             | QUANDO?                       |
+-------------------+-------------------+-------------------+-------------------+-------------------------------+
| JUSTIFICATIVAS    | PRODUTO           | STAKEHOLDERS      | PREMISSAS         | GRUPO DE ENTREGAS             |
|                   |                   |                   |                   |                               |
| OBJETIVOS SMART   | REQUISITOS        | EQUIPE (SQUAD E7) | RISCOS            | LINHA DO TEMPO & RESTRICOES   |
|                   |                   |                   |                   |                               |
| BENEFICIOS        | NAO-ESCOPO        |                   |                   |                               |
+-------------------+-------------------+-------------------+-------------------+-------------------------------+
```

---

### 1. Por Que? (Justificativa, Objetivos e Benefícios)

#### 1.1. Justificativas
* Dificuldade recorrente dos estudantes em assimilar conceitos abstratos de **Lógica Proposicional** e formalismo matemático sem aplicação prática imediata.
* Urgência acadêmica e mercadológica em debater **Ética e Alinhamento em Inteligência Artificial** (mitigação de viés, alucinações e privacidade/LGPD).
* Ausência de ferramentas didáticas imersivas que combinem gamificação de suspense/escape room com lógica formal no ecossistema do 2º período de ADS.

#### 1.2. Objetivo SMART
* Desenvolver e disponibilizar na web um **jogo 3D funcional no Canvas integrado a C (U1) e Haskell (U2)** até o encerramento do semestre letivo (W17), contendo **15 Histórias de Usuário validadas**, no mínimo **4 puzzles lógicos formais** e **4 módulos educativos de IA**, alcançando avaliação de usabilidade $\ge 80\%$ de satisfação.

#### 1.3. Benefícios
* Fixação prática dos conectivos lógicos ($\land, \lor, \neg, \rightarrow, \leftrightarrow$) e tabelas-verdade através de mecânicas de destravamento de portas.
* Conscientização crítica sobre os dilemas contemporâneos da IA através do sistema de coleta e reeducação do modelo.
* Validação e convergência multidisciplinar das 5 matérias do semestre (PIF, IHC, LMC, FDS, FP2).

---

### 2. O Que? (Produto, Requisitos e Não-Escopo)

#### 2.1. Produto
* **Lockdown CESAR:** Jogo de suspense/escape room 3D em primeira pessoa para navegadores web, renderizado via JS Canvas / WebGL com motor lógico em C, ambientado no campus da CESAR School.

#### 2.2. Requisitos de Alto Nível
* **Requisitos Funcionais (RF):**
  * Movimentação 3D em primeira pessoa (WASD + mouse) e lanterna dinâmica com consumo de energia.
  * Terminais de acesso protegidos por travas de lógica proposicional.
  * Inventário de datasets éticos de IA e terminal de upload para reeducação da entidade.
  * Barra de Consciência da IA (0% a 100%) que altera o comportamento do sistema.
  * Persistência de estado local (Save/Load) e condições claras de vitória e derrota.
* **Requisitos Não-Funcionais (RNF):**
  * Execução fluida no navegador sem necessidade de plugins ou instalações complexas.
  * Tempo de resposta para validação lógica inferior a 100ms.
  * Código modular em C compilável sob padrão C99 sem vazamento de memória.
  * Interface em conformidade com as 10 Heurísticas de Usabilidade de Nielsen.

#### 2.3. Não-Escopo (O que NÃO será feito)
* Modo multiplayer cooperativo ou online.
* Gráficos fotorrealistas de alta complexidade que comprometam o carregamento web (estilo visual low-poly / retro suspense).
* Suporte nativo para plataformas mobile (iOS/Android) com controles de toque.
* Modelagem de inteligência artificial generativa real executando localmente no navegador.

---

### 3. Quem? (Stakeholders e Equipe)

#### 3.1. Stakeholders Externos
* **Docentes Avaliadores:** Professores das disciplinas de FP2, FDS, LMC, IHC e PIF da CESAR School.
* **Usuários Finais:** Estudantes de Ciência da Computação, ADS, Engenharia e entusiastas de jogos de lógica.

#### 3.2. Equipe de Desenvolvimento (Squad E7)
* **Larissa Almeida:** Lead de Engenharia de Software (FDS)
* **Mateus Lacerda:** Gestão Ágil / Scrum Master (FP2) & Engenharia de Requisitos
* **Theo Monteiro:** Analista de Requisitos & Testador de Software (QA)
* **João Gabriel:** Desenvolvedor Web/C, Haskell e Arquitetura
* **Caio Brayner:** Desenvolvedor C
* **Matheus Chaves:** Designer de Interface (IHC) & Desenvolvedor Canvas/Web
* **Julio Cesar:** Consultor de Lógica Matemática (LMC) & Testador
* **Jhorge Araújo:** Consultor de Arquitetura e Lógica Matemática (LMC)

---

### 4. Como? (Premissas e Riscos)

#### 4.1. Premissas
* O usuário final possui navegador web moderno (Chrome, Firefox, Edge) com suporte a HTML5 Canvas e WebGL.
* O fluxo de desenvolvimento seguirá a cadência de Sprints quinzenais gerenciadas via Jira Software.
* A validação de inferências e regras puras será portada para Haskell na Unidade 2.

#### 4.2. Gestão de Riscos e Mitigações

| Risco Identificado | Impacto | Probabilidade | Estratégia de Mitigação |
| :--- | :--- | :--- | :--- |
| **Gargalo de performance no Canvas 3D web** | Alto | Média | Utilizar renderização geométrica low-poly e otimizar o loop de desenho no Canvas. |
| **Dificuldade excessiva nos puzzles lógicos** | Médio | Média | Incluir tutoriais progressivos e pista textual na tela "Como Jogar". |
| **Desvio de escopo (Scope Creep)** | Alto | Baixa | Rastreabilidade estrita através das 15 USs priorizadas via MoSCoW no Jira. |
| **Erros na integração entre JS e C** | Médio | Média | Definir contratos de dados claros e desacoplamento de módulos. |

---

### 5. Quando? (Grupo de Entregas e Linha do Tempo)

```text
[UNIDADE 1] =====================================> [UNIDADE 2] ====================================>
W01 - W04: Concepção & Setup                       W09 - W12: Port Haskell & Refinamento
├── Canvas, RACI, Backlog Inicial (FP2)            ├── Validador Lógico em Haskell (PIF/LMC)
├── Documento de Visão e RF/RNF (FDS)              ├── Testes Empíricos de Usabilidade (IHC)
└── 15 Histórias de Usuário (Jira)                 └── Módulo de Persistência Avançado (FDS)

W05 - W08: Protótipo Jogável 3D em C               W13 - W17: Versão Final & Validação
├── Motor 3D Web Canvas (IHC/PIF)                  ├── Fechamento do Produto e Testes de Carga
├── Validador de Proposições em C (LMC)            ├── Demonstração de Banca e Apresentação
└── Entrega do MVP 1 (U1)                          └── Relatório Final de Encerramento (FP2)
```
