#include <iostream>
#include <vector>
#include <time.h>

struct Object
{
    int weight;
    int value;
};

std::vector<Object> allObj;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// dynamic programing bottom up method
int k(int n, int W)
{
    std::vector<std::vector<int>> K;
    std::vector<int> temp;

    // initialize value table
    for (int i = 0; i < n; i++)
    {
        K.push_back(temp);
        for (int j = 0; j <= W; j++)
        {
            K[i].push_back(0);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int w = allObj[i].weight;
        int v = allObj[i].value;
        for (int j = 0; j <= W; j++)
        {
            // fill the first row condition
            if (i == 0)
            {
                if (w <= W)
                {
                    K[i][j] = v;
                }
                else
                {
                    K[i][j] = 0;
                }
            }
            // fill matrix by max(K[i-1][j], K[i-1][j-w] + v)
            else
            {
                if (j > w)
                {
                    K[i][j] = max(K[i - 1][j - w] + v, K[i - 1][j]);
                }
                else
                {
                    K[i][j] = K[i - 1][j];
                }
            }
        }
    }

    // print the value table
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            std::cout << K[i][j] << '\t';
        }
        std::cout << '\n';
    }

    // print what object is used
    bool isFound = false;
    int a = n - 1;
    int b = W;
    while (!isFound)
    {
        int w = allObj[a].weight;
        if (K[a][b] == 0)
        {
            isFound = true;
            break;
        }
        else
        {
            if (a > 0)
            {
                if (K[a][b] == K[a - 1][b])
                {
                    a -= 1;
                }
                else
                {
                    std::cout << "Use object " << a << '\n';
                    a -= 1;
                    b -= w;
                }
            }
            else if (K[a][b] != 0)
            {
                std::cout << "Use object " << a << '\n';
                break;
            }
            else
            {
                break;
            }
        }
    }
    return K[n - 1][W];
}
int main()
{
    srand(time(NULL));
    int n, W;
    std::cout << "Input number of objects: ";
    std::cin >> n;
    std::cout << "Input total weight: ";
    std::cin >> W;
    std::vector<int> temp;

    for (int i = 0; i < n; i++)
    {
        Object temp;
        temp.weight = rand() % 10 + 1;
        temp.value = rand() % 10 + 1;
        allObj.push_back(temp);
        std::cout << i << " weight: " << allObj[i].weight << ", value: " << allObj[i].value << '\n';
    }
    int maxValue = k(n, W);
    std::cout << "Max value: " << maxValue;
}