// #include <bits/stdc++.h>
#include <time.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;
using namespace chrono;

#define SIZE_KNAPSACK 100
#define MAX_WEIGHT 100
#define MAX_VAL 100
#define CAPACITY 100

// Estrutura para manter os dados do item unidos
struct Item
{
    int id; // Para rastrear qual item é (opcional)
    int val;
    int wt;
};

// Comparador: Ordena pela razão Valor/Peso (do maior para o menor)
bool compareRatio(const Item &a, const Item &b)
{
    double r1 = (double)a.val / a.wt;
    double r2 = (double)b.val / b.wt;
    return r1 > r2;
}

// Função recursiva para resolver o problema da mochila 0/1
// W: Capacidade restante da mochila
// val: Vetor com os valores (utilidades) dos itens
// wt: Vetor com os pesos dos itens
// n: Índice do item atual sendo considerado (de n até 1)
int linearKnapsackRec(int W, vector<int> &val, vector<int> &wt, int n)
{
    // Caso Base: Se não há mais itens ou a capacidade da mochila é 0,
    // o valor acumulado é 0.
    if (n == 0 || W == 0)
        return 0;

    int pick = 0;

    // Opção 1: Incluir o n-ésimo item (se o peso dele couber na capacidade atual)
    // O índice no vetor é n-1 pois vetores em C++ são 0-indexed.
    if (wt[n - 1] <= W)
        pick = val[n - 1] + linearKnapsackRec(W - wt[n - 1], val, wt, n - 1);

    // Opção 2: Não incluir o n-ésimo item e passar para o próximo
    int notPick = linearKnapsackRec(W, val, wt, n - 1);

    // Retorna o valor máximo entre incluir ou não incluir o item atual
    return max(pick, notPick);
}

// Função wrapper para iniciar a chamada recursiva
int linearKnapsack(int W, vector<int> &val, vector<int> &wt)
{
    int n = val.size(); // Número total de itens
    return linearKnapsackRec(W, val, wt, n);
}

vector<vector<int>> memoization_knapsack(int W, vector<int> &val, vector<int> &wt)
{
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    // Inicializa apenas a linha 0 (nenhum item considerado) com 0
    for (int j = 0; j <= W; j++) dp[0][j] = 0;

    for (int i = 1; i <= n; i++) // Começa do item 1
    {
        for (int j = 0; j <= W; j++) // Inclui capacidade 0
        {
            int pick = 0;
            if (wt[i - 1] <= j)
                pick = val[i - 1] + dp[i - 1][j - wt[i - 1]];

            int notPick = dp[i - 1][j];

            dp[i][j] = max(pick, notPick);
        }
    }
    return dp;
}

struct KnapsackMemoizationResult {
    int maxValue;              // Valor máximo conseguido
    vector<int> selectedItems; // Índices dos itens escolhidos (0-based)
};

KnapsackMemoizationResult memoization_knapsack_with_items(int W, vector<int> &val, vector<int> &wt) {

    vector<vector<int>> dp = memoization_knapsack(W, val, wt);
    int n = wt.size();

    int res = dp[n][W]; // Valor ótimo final
    int w_atual = W;    // Capacidade restante para rastreio
    vector<int> itens;

    for (int i = n; i > 0 && res > 0; i--) {
        // Se o valor atual é igual ao da linha de cima, o item i NÃO foi incluído
        if (res == dp[i - 1][w_atual]) {
            continue;
        } 
        else {
            // O item i foi incluído
            // Como os vetores val e wt são 0-indexados, o item i na matriz é o i-1 nos vetores
            itens.push_back(i - 1); 
            
            // Subtrai o valor do item para continuar a busca
            res -= val[i - 1];
            // Subtrai o peso do item da capacidade atual
            w_atual -= wt[i - 1];
        }
    }

    // Retorna o resultado (valor ótimo e vetor de itens)
    return {dp[n][W], itens};
}

int greedy_knapsack(int W, vector<int> &val, vector<int> &wt)
{
    int n = val.size();
    vector<Item> items(n);

    // 1. Unificar peso e valor em uma estrutura
    for (int i = 0; i < n; i++)
    {
        items[i] = {i, val[i], wt[i]};
    }

    // 2. Ordenar os itens (Complexidade O(N log N))
    // A estratégia gulosa aqui é: pegar os itens com melhor custo-benefício primeiro
    sort(items.begin(), items.end(), compareRatio);

    int current_weight = 0;
    int solution_value = 0;

    // 3. Seleção Gulosa 0/1
    for (int i = 0; i < n; i++)
    {
        // Se o item cabe INTEIRO na capacidade restante
        if (current_weight + items[i].wt <= W)
        {
            current_weight += items[i].wt;
            solution_value += items[i].val;
        }
    }

    return solution_value;
}

int main()
{

    srand(time(NULL));
    vector<int> val(SIZE_KNAPSACK);
    vector<int> wt(SIZE_KNAPSACK);
    int W = CAPACITY;

    double avg_percentage_difference = 0;
    int k = 0;
    FILE *fp = fopen("results.txt", "w");
    FILE *fp2 = fopen("table_dynamic_program.txt", "w");
    FILE *fp3 = fopen("items_selected_dynamic_program.txt", "w");
    FILE *fp4 = fopen("inputs.txt", "w");
    FILE *fp5 = fopen("execution_times.txt", "w");
    for (k = 0; k < 100; k++)
    {
        for (int i = 0; i < SIZE_KNAPSACK; i++)
        {
            val[i] = (rand() % MAX_VAL) + 1;   // Random values for item values
            wt[i] = (rand() % MAX_WEIGHT) + 1; // Random weights
            fprintf(fp4, "Item %d: Value = %d, Weight = %d\n", i + 1, val[i], wt[i]);
        }
        fprintf(fp4, "Knapsack Capacity: %d\n\n", W);

        auto start = high_resolution_clock::now();
        vector<vector<int>> dp = memoization_knapsack(W, val, wt);
        cout << "Programacao dinamica: " << dp[val.size()][W] << endl;
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Tempo de execucao em programacao dinamica: " << duration.count() << " ms " << endl;
        cout << "Itens selecionados na programacao dinamica: ";
        KnapsackMemoizationResult result = memoization_knapsack_with_items(W, val, wt);
        for (int index : result.selectedItems) {
            cout << "(" << "Value: " << val[index] << ", Weight: " << wt[index] << ") ";
            fprintf(fp3, "Item %d: Value = %d, Weight = %d\n", index + 1, val[index], wt[index]);
        }
        fprintf(fp3, "\n", result.maxValue);
        cout << "Solucao completa usando programacao dinamica: " << endl;
        for (int i = 0; i <= val.size(); i++)
        {
            for (int j = 0; j <= W; j++)
            {
                cout << dp[i][j] << " ";
                fprintf(fp2, "%d ", dp[i][j]);
            }
            cout << endl;
            fprintf(fp2, "\n");
        }
        fprintf(fp2, "\n");
        fprintf(fp5, "Dynamic Programming: %lld ms\n", duration.count());

        start = high_resolution_clock::now();
        cout << "Linear: " << linearKnapsack(W, val, wt) << endl;
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        cout << "Tempo de execucao em linear: " << duration.count() << " ms\n";
        fprintf(fp5, "Linear: %lld ms\n", duration.count());

        start = high_resolution_clock::now();
        int greedy_solution = greedy_knapsack(W, val, wt);
        cout << "Abordagem gulosa: " << greedy_solution << endl;
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        cout << "Tempo de execucao em abordagem gulosa: " << duration.count() << " ms" << endl;
        double percentage_difference = 100 * (1 - double(greedy_solution) / double(dp[val.size()][W]));
        cout << "Diferenca entre programacao dinamica e abordagem gulosa: " << percentage_difference << endl
             << endl;
        avg_percentage_difference += percentage_difference;
        fprintf(fp5, "Greedy: %lld ms\n", duration.count());
        fprintf(fp5, "\n");

        fprintf(fp, "%d %d %d\n\n", dp[val.size()][W], linearKnapsack(W, val, wt), greedy_solution);

        this_thread::sleep_for(chrono::milliseconds(50));
    }
    avg_percentage_difference /= k;
    cout << "Diferenca entre programacao dinamica e abordagem gulosa media: " << avg_percentage_difference << endl
         << endl;

    return 0;
}