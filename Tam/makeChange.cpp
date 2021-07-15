#include <iostream>
#include <vector>

// return min value of two int
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// make change function using dynamic programming
int makeChange(int n, int N)
{
    int d[4] = {1, 10, 25, 100};
    std::vector<std::vector<int>> t;
    std::vector<int> temp;
    for (int i = 0; i < n; i++)
    {
        t.push_back(temp);
        for (int j = 0; j <= N; j++)
        {
            t[i].push_back(0);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (d[i] == 1)
            {
                t[i][j] = t[i][j - d[i]] + 1;
            }
            else if (j < d[i])
            {
                t[i][j] = t[i - 1][j];
            }
            else
            {
                t[i][j] = min(t[i][j - d[i]] + 1, t[i - 1][j]);
            }
        }
    }

    // find all the coins used
    bool findAll = false;
    int a = n - 1;
    int b = N;
    int i = 1;
    while (!findAll)
    {
        if (t[a][b] == 0)
        {
            findAll = true;
            break;
        }

        // t[0-1][b] will be error so much check for 'a' first
        if (a > 0)
        {
            if (t[a][b] == t[a - 1][b])
            {
                a -= 1;
            }
            else if (t[a][b] == t[a][b - d[a]] + 1)
            {
                b -= d[a];
                std::cout << i << ":\t" << d[a] << '\n';
                i++;
            }
        }
        else if (t[a][b] == t[a][b - d[a]] + 1)
        {
            b -= d[a];
            std::cout << i << ":\t" << d[a] << '\n';
            i++;
        }
    }
    return t[n - 1][N];
}

int main()
{
    int n = 4;   // input 4 denominations
    int N = 289; // test change is 289 cents
    std::cout << makeChange(n, N);
}