#include <bits/stdc++.h>
#include <time.h>

using namespace std;
using namespace chrono;

#define SIZE_KNAPSACK 100
#define MAX_WEIGHT 500
#define MAX_VAL 500
#define CAPACITY 500


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


int memoization_knapsackRec(int W, vector<int> &val, vector<int> &wt, int n) {

    // Base Case
    if (n == 0 || W == 0)
        return 0;

    int pick = 0;

    // Pick nth item if it does not exceed the capacity of knapsack
    if (wt[n - 1] <= W)
        pick = val[n - 1] + memoization_knapsackRec(W - wt[n - 1], val, wt, n - 1);
    
    // Don't pick the nth item
    int notPick = memoization_knapsackRec(W, val, wt, n - 1);
     
    return max(pick, notPick);
}

int memoization_knapsack(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();
    return memoization_knapsackRec(W, val, wt, n);
}

int main()
{

    srand(time(NULL));
    vector<int> val(SIZE_KNAPSACK);
    vector<int> wt(SIZE_KNAPSACK);
    int W = CAPACITY;

    for (int i = 0; i < SIZE_KNAPSACK; i++)
    {
        val[i] = rand() % MAX_VAL;   // Random values for item values
        wt[i] = rand() % MAX_WEIGHT; // Random weights between 1 and 10
    }
    
    auto start = high_resolution_clock::now();
    cout << "Programacao dinamica: " << memoization_knapsack(W, val, wt) << endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Tempo de execucao em programacao dinamica: " << duration.count() << " ms\n";
  
    start = high_resolution_clock::now();
    cout << "Linear: " << memoization_knapsack(W, val, wt) << endl;
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Tempo de execucao em linear: " << duration.count() << " ms\n";


    return 0;
}