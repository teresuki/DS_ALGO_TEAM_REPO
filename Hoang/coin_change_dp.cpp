#include <iostream>
using namespace std;

#define n 3 // Denomination of coins
#define N 8 // Money needs to be changed

int coin_change()
{
    int d[] = {1, 4, 6};
    int t[n][N+1];
    for(int i = 0; i < n; ++i) t[i][0] = 0; /* Base case: No money */
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            if(i == 0) t[i][j] = t[i][j-d[i]] + 1;
            else if(j < d[i]) t[i][j] = t[i-1][j];
            else t[i][j] = min(t[i-1][j], t[i][j-d[i]] + 1);
        }
    }

    return t[n-1][N];
}

int main()
{
    cout << coin_change();
    return 0;
}