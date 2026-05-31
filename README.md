# Desafio 5 — Simulação de Redes de Computadores

**Integrantes:** Joanne, Maria Regina, Jhean

---

## Sobre o Projeto

Simulação de uma rede simples de computadores com comutação de pacotes, implementada em C. Cada pacote possui número de identificação, tamanho (KB) e tempo estimado de transmissão.

O sistema é modular: cada estrutura de dados tem seu próprio `.h` e `.c`.

---

## Estrutura de Arquivos

```
.
├── pacote.h      # structs PacoteFila e PacotePilha
├── fila.h        # interface da fila (FIFO)
├── fila.c        # implementação da fila
├── pilha.h       # interface da pilha (LIFO)
├── pilha.c       # implementação da pilha
├── lista.h       # interface da lista encadeada
├── lista.c       # implementação da lista encadeada
└── main.c        # orquestra a simulação
```

### Como compilar e executar

```bash
gcc main.c fila.c lista.c pilha.c -o pacotes
./pacotes
```

---

## Parte 1 — Fila (Pacotes aguardando transmissão)

Pacotes chegam à interface de rede e aguardam envio na ordem de chegada — comportamento **FIFO** (First In, First Out).

**Operações:**
- `adicionarFila(numero, tamanho, tempo)` — enfileira um pacote
- `transmitirPacote()` — remove e transmite o próximo da fila
- `mostrarFila()` — exibe os pacotes em espera

**Pacotes inseridos:**

| Pacote | Tamanho |
|--------|---------|
| 1      | 500 KB  |
| 2      | 300 KB  |
| 3      | 700 KB  |
| 4      | 200 KB  |

> **Qual pacote será transmitido primeiro?**
> O Pacote 1. Por ser FIFO, o primeiro a entrar é o primeiro a sair. Após duas transmissões, restam os pacotes 3 e 4 na fila.

---

## Parte 2 — Pilha (Pacotes com erro)

Pacotes que falham na transmissão são empilhados para retransmissão — comportamento **LIFO** (Last In, First Out).

**Operações:**
- `adicionarErro(numero)` — empilha um pacote com falha
- `retransmitirPacote()` — desempilha e retransmite o último com erro
- `mostrarPilha()` — exibe os pacotes com erro do topo à base

**Exemplo:** Pacote 2 falhou → Pacote 4 falhou

> **Qual será retransmitido primeiro?**
> O Pacote 4. Por ser LIFO, o último a ser empilhado é o primeiro a ser retirado.

---

## Parte 3 — Lista Encadeada (Pacotes ativos na rede)

Pacotes em trânsito são mantidos em uma lista com alocação dinâmica. Cada nó contém: ID, origem, destino e status.

**Operações:**
- `inserirPacoteLista(id, origem, destino, status)` — insere na cabeça da lista
- `listarPacotes()` — exibe todos os pacotes ativos
- `buscarPacote(id)` — localiza um pacote pelo ID
- `removerPacote(id)` — remove um pacote entregue e libera memória

---

## Complexidade de Algoritmo

| Operação              | Estrutura       | Complexidade | Observação                        |
|-----------------------|-----------------|:------------:|-----------------------------------|
| `adicionarFila`       | Fila (vetor)    | O(1)         | Insere no fim diretamente         |
| `transmitirPacote`    | Fila (vetor)    | O(1)         | Remove do início diretamente      |
| `mostrarFila`         | Fila (vetor)    | O(n)         | Percorre todos os elementos       |
| `adicionarErro`       | Pilha (vetor)   | O(1)         | Push no topo                      |
| `retransmitirPacote`  | Pilha (vetor)   | O(1)         | Pop do topo                       |
| `mostrarPilha`        | Pilha (vetor)   | O(n)         | Percorre do topo à base           |
| `inserirPacoteLista`  | Lista encadeada | O(1)         | Inserção na cabeça                |
| `buscarPacote`        | Lista encadeada | O(n)         | Busca linear por ID               |
| `removerPacote`       | Lista encadeada | O(n)         | Percorre até encontrar o nó       |
| `listarPacotes`       | Lista encadeada | O(n)         | Percorre toda a lista             |

### Observações

- As operações críticas (inserção/remoção nas pontas) são todas **O(1)**.

- O principal gargalo é a **busca por ID na lista**: O(n) no pior caso. Substituir por uma hash table tornaria busca e remoção **O(1)** amortizado — em vez de percorrer nó por nó, a hash table calcula diretamente a posição do pacote a partir do ID, sem varredura. O custo extra ocasional (colisões) existe, mas é raro o suficiente para manter a média em O(1).

- A fila usa array estático sem reuso dos índices liberados. Uma **fila circular** (`% FILA_MAX`) eliminaria esse desperdício mantendo O(1).

---

## Respostas às Perguntas Teóricas

**1. Por que a fila representa bem a transmissão de pacotes?**

Porque a transmissão segue naturalmente a ordem de chegada: o primeiro pacote que chega à interface de rede deve ser o primeiro enviado. Esse é exatamente o comportamento FIFO da fila. Protocolos como TCP/IP adotam esse modelo para garantir equidade e previsibilidade.

**2. Por que a pilha pode representar retransmissão?**

Quando pacotes falham, faz sentido priorizar o erro mais recente — ele tem maior chance de ser consequência de uma condição momentânea ainda ativa na rede. O LIFO da pilha atende exatamente essa política: o último erro registrado é o primeiro a ser tratado.

**3. Por que a lista encadeada ajuda no controle de pacotes ativos?**

Porque o número de pacotes em trânsito varia continuamente. A lista encadeada aloca e libera memória dinamicamente, sem limite fixo de tamanho. Além disso, suporta inserção, busca e remoção em qualquer posição — essencial para gerenciar pacotes com IDs arbitrários em trânsito simultâneo.

**4. Qual estrutura melhor representa atraso de fila?**

A estrutura que melhor representa atraso de fila é a própria fila. Isso ocorre porque o atraso em redes geralmente acontece quando muitos pacotes aguardam processamento ou transmissão ao mesmo tempo. Quanto maior a quantidade de elementos armazenados na fila, maior será o tempo de espera dos pacotes que estão no final dela. Esse fenômeno é conhecido em redes como latência de enfileiramento (queue delay), sendo um dos principais fatores que afetam desempenho e velocidade de transmissão em sistemas computacionais e redes de comunicação.
