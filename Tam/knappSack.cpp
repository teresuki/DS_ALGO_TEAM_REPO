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
                if (w <= j)
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
                if (j >= w)
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
        int v = allObj[a].value;
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
                    std::cout << "Use object " << a + 1 << ": weight: " << w << ", value: " << v << '\n';
                    a -= 1;
                    b -= w;
                }
            }
            else if (K[a][b] != 0)
            {
                std::cout << "Use object " << a + 1 << ": weight: " << w << ", value: " << v << '\n';
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
void randomizeObject();
void testCase();

int main()
{
    std::cout << "Test case: " << '\n';
    testCase();
    std::cout << "\n\n";
    std::cout << "Make random objects: " << '\n';
    randomizeObject();
}
void testCase()
{
    srand(time(NULL));
    int n = 6, W = 10; // 6 items, 10 total weight
    Object obj1;
    obj1.weight = 3;
    obj1.value = 7;
    allObj.push_back(obj1);

    Object obj2;
    obj2.weight = 2;
    obj2.value = 10;
    allObj.push_back(obj2);

    Object obj3;
    obj3.weight = 6;
    obj3.value = 2;
    allObj.push_back(obj3);

    Object obj4;
    obj4.weight = 1;
    obj4.value = 3;
    allObj.push_back(obj4);

    Object obj5;
    obj5.weight = 7;
    obj5.value = 2;
    allObj.push_back(obj5);

    Object obj6;
    obj6.weight = 4;
    obj6.value = 6;
    allObj.push_back(obj6);
    std::cout << 1 << " weight: " << allObj[0].weight << ", value: " << allObj[0].value << '\n';
    std::cout << 2 << " weight: " << allObj[1].weight << ", value: " << allObj[1].value << '\n';
    std::cout << 3 << " weight: " << allObj[2].weight << ", value: " << allObj[2].value << '\n';
    std::cout << 4 << " weight: " << allObj[3].weight << ", value: " << allObj[3].value << '\n';
    std::cout << 5 << " weight: " << allObj[4].weight << ", value: " << allObj[4].value << '\n';
    std::cout << 6 << " weight: " << allObj[5].weight << ", value: " << allObj[5].value << '\n';
    int maxValue = k(n, W);
    std::cout << "Max value: " << maxValue;
}
void randomizeObject()
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
