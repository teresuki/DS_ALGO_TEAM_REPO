// Ex_2 -- Solving the Coin Change Problem with Dynamic Programming
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
#include <vector>
using namespace std;

int coin(int N);    // assume that n = 4
vector<int> optimal_solution(4, 0);   // global container

int main(void)
{
    int N;

    cout << "Enter the amount of money needed to pay back: N = ";
    cin >> N;

    int result = coin(N);   // call only 1 because of the global container optimal_solution will change each call
    cout << "\nThe smallest amount of coins needed is: ";
    cout << result << endl;

    cout << "\nThe optimal solution is: " << endl;
    cout << "one dollars: " << optimal_solution[3] << endl;
    cout << "quarters: " << optimal_solution[2] << endl;
    cout << "dimes: " << optimal_solution[1] << endl;
    cout << "pennies " << result - optimal_solution[3] - optimal_solution[2] - optimal_solution[1] << endl;

    return 0;
}

int coin(int N)
{
    int d[4] = {1, 10, 25, 100};
    int t[4][N + 1];

    // Base case
    for(int i = 0; i < 4; i++)
        t[i][0] = 0;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(i == 0)   // the 1st index must be 0, not 1
                t[i][j] = t[i][j - d[i]] + 1;   // fill in the 1st row
            else if(j < d[i])
                t[i][j] = t[i - 1][j];          // fill in the rest, row by row
            else
                t[i][j] = min(t[i - 1][j], t[i][j - d[i]] + 1); // fill in the rest, row by row
        }
    }

    // Construct the optimal solution from the table
    int i = 3, j = N;
    while(i != 0)     // start at entry t[n, N]
    {
        if(t[i][j] == t[i - 1][j])
            i--;
        if(t[i][j] == t[i][j - d[i]] + 1)
        {
            optimal_solution[i] += 1;
            j = j - d[i];
        }
    }

    return t[3][N];
}
