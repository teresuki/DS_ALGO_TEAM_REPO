#include <iostream>

using namespace std;

int coinchange(int n, int N)
{
    int d[] = {1, 4, 6, 8};
    int t[n][N+1];

    //Base case//
    for(int i = 0; i < n; ++i)
        t[i][0] = 0;
    //Other cases//
    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            if(i == 0)
                t[i][j] = t[i][j-d[i]] + 1;
            else if(j < d[i])
                t[i][j] = t[i-1][j];
            else
                t[i][j] = min(t[i-1][j], t[i][j-d[i]] + 1);
        }
    }

    return t[n-1][N];
}

int main()
{
    cout << coinchange(4, 1000);
    return 0;
}
