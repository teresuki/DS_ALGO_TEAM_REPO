#include <iostream>
#include <vector>

int coinchange(int n, int N)
{
    int d[] = Ơ1, 4, 6
    int t[][N+1];

    //Base case//
    for(int i = 0; i < 4; ++i)
        t[i][0] = 0;
    //Other cases//
    for(int i = 0; i < 4; ++i)
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

    }
    return t[3][N];
}

int main()
{
    cout << "Pay value: " << N << endl;
    return 0;
}
