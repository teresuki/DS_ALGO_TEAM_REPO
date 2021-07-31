/* Note: The coinType 3D array takes up
a lot of memory space, with big money
value it is not feasible memory wise*/

#include <iostream>
using namespace std;

#define n 4 // Denomination of coins
#define N 289 // Money needs to be changed

int coin_change()
{
    int d[] = {1, 10, 25, 100};
    int t[n][N+1];
    int coinType[n][N+1][n];
    for(int i = 0; i < n; ++i) {t[i][0] = 0; for(int k = 0; k < n; ++k) coinType[i][0][k] = 0;} /* Base case: No money */
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            if(i == 0)
            {
                t[i][j] = t[i][j-d[i]] + 1;
                coinType[i][j][0] = j;
                for(int k = 1; k < n; ++k) coinType[i][j][k] = 0;
            } 
            else if(j < d[i])
            {
                t[i][j] = t[i-1][j];
                for(int k = 0; k < n; ++k)
                 coinType[i][j][k] = coinType[i-1][j][k];
            } 
            else
            {
                if(t[i-1][j] < t[i][j-d[i]] + 1)
                {
                    t[i][j] = t[i-1][j];
                    for(int k = 0; k < n; ++k)
                     coinType[i][j][k] = coinType[i-1][j][k];
                }
                else
                {
                    t[i][j] = t[i][j-d[i]] + 1;
                    for(int k = 0; k < n; ++k)
                     coinType[i][j][k] = coinType[i][j-d[i]][k];
                    coinType[i][j][i]++;
                }
            }
        }
    }

    cout << "Dollars: " << coinType[n-1][N][3] << endl;
    cout << "Quarters: " << coinType[n-1][N][2] << endl;
    cout << "Dimes: " << coinType[n-1][N][1] << endl;
    cout << "Pennies: " << coinType[n-1][N][0] << endl;
    return t[n-1][N];
}

int main()
{
    cout << coin_change();
    return 0;
}