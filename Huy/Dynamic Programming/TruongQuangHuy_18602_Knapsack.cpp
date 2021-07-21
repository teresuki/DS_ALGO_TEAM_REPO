// 0-1_Knapsack problem -- Dynamic Programming
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
#include <vector>
using namespace std;

// use vectors here to make it easier to pass into and return from the function
int Knapsack(const vector<int>& w, const vector<int>& v, int n, int W);
vector<int> optimal_solution;   // global container

int debug_mode = 0;
int main(void)
{
    int n, W, result;   // n and W must be integer

if(debug_mode == 0)
{
    cout << "Enter the number of objects: n = ";
    cin >> n;
    cout << "Enter the capacity of the sack: W = ";
    cin >> W;

    vector<int> w;
    vector<int> v;
    int temp;
    for(int i = 0; i < n; i++)
    {
        cout << "w[" << i + 1 << "] = ";
        cin >> temp;
        w.push_back(temp);

        cout << "v[" << i + 1 << "] = ";
        cin >> temp;
        v.push_back(temp);
    }

    result = Knapsack(w, v, n, W);  // must call only 1 time because of the global container optimal_solution will change each call
}

if(debug_mode == 1)
{
    n = 5;
    W = 10;
    vector<int> w = {6, 5, 4, 2, 2};
    vector<int> v = {6, 3, 5, 4, 6};

    result = Knapsack(w, v, n, W);
}

if(debug_mode == 2)
{
    n = 6;
    W = 10;
    vector<int> w = {3, 2, 6, 1, 7, 4};
    vector<int> v = {7, 10, 2, 3, 2, 6};

    result = Knapsack(w, v, n, W);
}

    cout << "\nThe value of the Optimal solution is: " << result << endl;
    cout << "The Optimal solution is: ";

    for(int i = optimal_solution.size() - 1; i >= 1; i--)   // size_t here will easily because error because size_t == unsigned int
        cout << optimal_solution[i] << ", ";
    cout << optimal_solution[0] << endl;

    return 0;
}

int Knapsack(const vector<int>& w, const vector<int>& v, int n, int W)
{
    int K[n][W + 1];    // i from 0 to n - 1, j from 0 to W

    /* Initialize the table */
    for(int i = 0; i < n; i++)
        K[i][0] = 0;

    for(int j = 0; j <= W; j++)
    {
        if(w[0] <= j)       // w[0] here is w[1] in pseudo code
            K[0][j] = v[0]; // v[0] here is v[1] in pseudo code
        else
            K[0][j] = 0;
    }

    /* Compute other value in the table */
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j <= W; j++)
        {
            if(j >= w[i] && K[i - 1][j - w[i]] + v[i] > K[i - 1][j])
                K[i][j] = K[i - 1][j - w[i]] + v[i];
            else
                K[i][j] = K[i - 1][j];
        }
    }

    // print out the optimal solutions table
    cout << "The table for storing the optimal solutions of all possible subproblems: " << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= W; j++)
            printf("%5d", K[i][j]);
        cout << endl;
    }

    /* Construct the optimal solution */
    int k = W;
    for(int i = n - 1; i >= 0; i--)
    {
        if(i != 0)
        {
            if(K[i][k] != K[i - 1][k])
            {
                optimal_solution.push_back(i + 1);
                k -= w[i];
            }
        }
        else    // i == 0
            if(K[i][k] != 0)
                optimal_solution.push_back(i + 1);
    }

    return K[n - 1][W]; // equal to K[n][W] in pseudo code
}
