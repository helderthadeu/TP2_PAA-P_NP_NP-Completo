# TP2_PAA-P_NP_NP-Completo

## Resumo

Este projeto implementa e compara três abordagens para o problema da mochila 0/1 (Knapsack):
- Programação dinâmica (solução ótima com tabela `dp`).
- Abordagem recursiva/linear (chamada `linearKnapsack`) usada como comparação.
- Abordagem gulosa (heurística que ordena por valor/peso e tenta inserir itens inteiros).

O programa principal (`main.cpp`) gera instâncias aleatórias (por padrão 100 iterações) com 10 itens cada e capacidade fixa, executa as três abordagens, mede tempos de execução e grava resultados em arquivos de saída.

## Estrutura do repositório

- `main.cpp` : implementação em C++ das três abordagens e rotina principal que gera instâncias aleatórias e grava resultados.
- `inputs.txt` : registros das instâncias (valores e pesos dos itens e capacidade) geradas pelo programa.
- `results.txt` : para cada instância, uma linha com três números: `<valor_DP> <valor_linear> <valor_gulosa>` (separados por espaços e blocos em linhas vazias entre instâncias).
- `table_dynamic_program.txt` : matrizes `dp` (tabela de programação dinâmica) impressas para cada instância (uma tabela por instância).
- `items_selected_dynamic_program.txt` : lista de itens selecionados pela solução de programação dinâmica (cada item com `Value` e `Weight`).

## Como compilar

Requisitos mínimos: um compilador C++ compatível (ex.: `g++`).

No Windows (PowerShell), exemplo de comando com MinGW/g++:

```powershell
# compilar
g++ main.cpp -o main.exe

# executar
.\main.exe
```

Observação: no workspace já existe uma tarefa definida que compila e executa `main.cpp` — você pode usar o atalho/tarefa do VS Code.

## Como executar e onde estão os resultados

Ao executar `main.exe`, o programa:
- Gera entradas aleatórias e registra em `inputs.txt`.
- Para cada instância grava em `results.txt` os valores obtidos por Programação Dinâmica, Linear (recursiva) e Gulosa.
- Grava a tabela `dp` em `table_dynamic_program.txt` e os itens selecionados (pela DP) em `items_selected_dynamic_program.txt`.

Interpretação rápida de `results.txt`:
- Cada bloco corresponde a uma instância gerada.
- O formato de cada bloco é `DP Linear Greedy` — por exemplo, uma linha `35 35 35` significa que todas as três abordagens retornaram valor 35 naquela instância.

## Parâmetros principais (alterar em `main.cpp`)

As constantes definidas no topo de `main.cpp` controlam o comportamento padrão:

- `SIZE_KNAPSACK` : número de itens por instância (padrão 10).
- `CAPACITY` : capacidade da mochila (padrão 10).
- `MAX_WEIGHT` / `MAX_VAL` : valores máximos usados na geração aleatória (padrões 10).
- O loop principal atualmente gera 100 instâncias; altere o limite do `for (k = 0; k < 100; k++)` para ajustar o número de execuções.

## Saída detalhada

- `inputs.txt` — cada instância lista os 10 itens no formato `Item i: Value = X, Weight = Y` e logo abaixo `Knapsack Capacity: Z`.
- `table_dynamic_program.txt` — para cada instância o programa imprime a matriz `dp` (linhas: itens considerados de 0..n, colunas: capacidades 0..W).
- `items_selected_dynamic_program.txt` — após calcular a tabela `dp`, o programa reconstrói os índices dos itens escolhidos e os grava com seus `Value` e `Weight`.
- `results.txt` — contém os tripletos `<dp> <linear> <greedy>` para cada instância, permitindo análise de diferença percentual entre a heurística gulosa e a solução ótima.

## Notas / Sugestões

- A abordagem gulosa usada ordena por razão `value/weight` e tenta inserir itens inteiros — ela não é ótima em geral para o problema 0/1.
- A função `linearKnapsack` implementa uma solução recursiva (exponencial) útil para comparação, mas não escalável para n grande.
- Para experimentar: aumente `SIZE_KNAPSACK` e `CAPACITY` com cuidado (a tabela DP usa O(n * W) memória e tempo).

## Executar testes personalizados

Se desejar testar com entradas próprias, você pode modificar `main.cpp` para ler de um arquivo em vez de gerar aleatoriamente, ou gerar e manualmente editar `inputs.txt` e adaptar a execução para ler deste arquivo.

## Autor / Referência

Projeto de Trabalho de Curso (PAA) — implementação demonstrativa de abordagens para problema da mochila.

---

Se quiser, posso:
- Atualizar `README.md` com exemplos de saída reais extraídos dos arquivos do projeto;
- Adicionar um pequeno script `run.sh`/`run.ps1` para compilar e executar automaticamente;
- Modificar `main.cpp` para aceitar argumentos de linha de comando (número de instâncias, tamanho, capacidade).

Diga qual destes extras deseja que eu faça e eu prossigo.
