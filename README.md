# Análise Comparativa dos Algoritmos de Escalonamento

## Introdução
Este documento apresenta uma análise comparativa de diferentes algoritmos de escalonamento de processos. Os algoritmos analisados incluem **FIFO**, **SJF**, **Round Robin com Prioridade**, **Escalonamento por Prioridade** e um **Algoritmo Personalizado**. A avaliação considera o tempo médio de execução, vantagens, desvantagens e adequação de cada algoritmo para diferentes cenários.

## Algoritmos Analisados

### FIFO (First In, First Out)

#### Funcionamento
Os processos são atendidos na ordem em que chegam à fila, sem levar em conta suas prioridades ou tempos de execução.

#### Vantagens
- Simplicidade na implementação.
- Ordem previsível de execução.

#### Desvantagens
- Pode gerar grandes tempos de espera para processos mais longos, prejudicando a eficiência.

#### Dados Resumidos
- **Tempo médio de execução**: 11,83 unidades de tempo
- **Ordem de execução**: p1 → p2 → p3 → p4 → p5 → p6

---

### SJF (Shortest Job First)

#### Funcionamento
Processos com menor tempo de execução são priorizados.

#### Vantagens
- Minimiza o tempo médio de espera.
- Reduz a latência para processos curtos.

#### Desvantagens
- Pode causar 'starvation' (inanição) em processos longos.

#### Dados Resumidos
- **Tempo médio de execução**: 8,33 unidades de tempo
- **Ordem de execução**: p4 → p5 → p2 → p6 → p3 → p1

---

### RR (Round Robin) com Prioridade

#### Funcionamento
Cada processo recebe uma fatia de tempo fixa para execução, respeitando a prioridade atribuída.

#### Vantagens
- Justo para processos concorrentes.
- Garante que nenhum processo fique indefinidamente na fila.

#### Desvantagens
- Aumenta o overhead com trocas de contexto.
- Pode aumentar o tempo médio de execução.

#### Dados Resumidos
- **Tempo médio de execução**: 12,5 unidades de tempo
- **Ordem de execução**: Intercalada entre processos com base na prioridade e fatia de tempo.

---

### Escalonamento por Prioridade

#### Funcionamento
Processos são ordenados e executados com base em sua prioridade.

#### Vantagens
- Processos mais importantes são atendidos primeiro.
- Reduz o tempo total para tarefas críticas.

#### Desvantagens
- Pode causar starvation em processos de baixa prioridade.

#### Dados Resumidos
- **Tempo médio de execução**: 10,67 unidades de tempo
- **Ordem de execução**: p2 → p1 → p4 → p5 → p3 → p6

---

### Algoritmo Personalizado

#### Funcionamento
Combinação de características dos algoritmos anteriores, buscando otimizar o tempo de espera e execução.

#### Vantagens
- Adapta-se melhor ao contexto específico dos processos.
- Pode equilibrar tempo de espera e execução com base na prioridade e necessidade.

#### Desvantagens
- Complexidade adicional para implementar.
- Possível necessidade de ajustes para cenários diferentes.

#### Dados Resumidos
- **Tempo médio de execução**: 11 unidades de tempo
- **Ordem de execução**: Variada, intercalando processos para balancear prioridade e fatia de tempo.

---

## Conclusão
A análise mostrou que a escolha do algoritmo de escalonamento depende dos objetivos e necessidades específicas do sistema. O **SJF** é ideal para maximizar a eficiência, enquanto o **Round Robin** favorece a justiça entre processos. O **Escalonamento por Prioridade** é útil para sistemas críticos, e o **algoritmo personalizado** pode trazer maior flexibilidade em cenários específicos.
