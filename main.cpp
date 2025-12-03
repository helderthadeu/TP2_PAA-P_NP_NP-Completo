#include <bits/stdc++.h>
#include <time.h>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

#define SIZE_KNAPSACK 5
#define MAX_WEIGHT 5
#define MAX_VAL 5
#define CAPACITY 5

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

int linearKnapsackRec(int W, vector<int> &val, vector<int> &wt, int n)
{

    // Base Case
    if (n == 0 || W == 0)
        return 0;

    int pick = 0;

    // Pick nth item if it does not exceed the capacity of knapsack
    if (wt[n - 1] <= W)
        pick = val[n - 1] + linearKnapsackRec(W - wt[n - 1], val, wt, n - 1);

    // Don't pick the nth item
    int notPick = linearKnapsackRec(W, val, wt, n - 1);

    return max(pick, notPick);
}

int linearKnapsack(int W, vector<int> &val, vector<int> &wt)
{
    int n = val.size();
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

            // Debug: Mostra quais itens foram escolhidos
            // cout << "Item escolhido: " << items[i].id << " (Val: " << items[i].val << ", Peso: " << items[i].wt << ")\n";
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
    for (k = 0; k < 100; k++)
    {
        for (int i = 0; i < SIZE_KNAPSACK; i++)
        {
            val[i] = rand() % MAX_VAL;   // Random values for item values
            wt[i] = rand() % MAX_WEIGHT; // Random weights
        }

        auto start = high_resolution_clock::now();
        vector<vector<int>> dp = memoization_knapsack(W, val, wt);
        cout << "Programacao dinamica: " << dp[val.size()][W] << endl;
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Tempo de execucao em programacao dinamica: " << duration.count() << " ms " << endl;
        cout << "Solucao completa usando programacao dinamica: " << endl;
        for (int i = 0; i <= val.size(); i++)
        {
            for (int j = 0; j <= W; j++)
            {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }

        start = high_resolution_clock::now();
        cout << "Linear: " << linearKnapsack(W, val, wt) << endl;
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        cout << "Tempo de execucao em linear: " << duration.count() << " ms\n";

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
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    avg_percentage_difference /= k;
    cout << "Diferenca entre programacao dinamica e abordagem gulosa media: " << avg_percentage_difference << endl
         << endl;

    return 0;
}