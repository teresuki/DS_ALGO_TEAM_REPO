#include <iostream>
#include <vector>
#include <time.h>

std::vector<std::vector<int>> createRandomDirectedGraph(int vertexNumber, int edgeNumber)
{
    srand(time(NULL));
    int maxValue = INT_MAX / 2;
    std::vector<std::vector<int>> graphMatrix;
    // should be connected graph
    if (vertexNumber <= edgeNumber - 1)
    {
        std::vector<int> temp;
        // initialize graph matrix
        for (int i = 0; i < vertexNumber; i++)
        {
            graphMatrix.push_back(temp);
            for (int j = 0; j < vertexNumber; j++)
            {
                graphMatrix[i].push_back(0);
            }
        }

        // randomly assign value to matrix with edge weight 1-10 with exact number of edge
        // still not the best way to do(slow for big matrix) but fast for small matrix
        int row = 0;
        for (int i = 0; i < edgeNumber; i++)
        {
            int col = rand() % vertexNumber;
            int value = rand() % 10 + 1;
            if (graphMatrix[row][col] == 0)
            {
                graphMatrix[row][col] = value;
                row++;
                col = rand() % vertexNumber;
                if (row == vertexNumber)
                {
                    row = rand() % vertexNumber;
                }
            }
            else
            {
                i -= 1;
            }
        }

        // if there is no path then set to a high number(INT_MAX/2)
        for (int i = 0; i < graphMatrix.size(); i++)
        {
            for (int j = 0; j < graphMatrix.size(); j++)
            {
                if (graphMatrix[i][j] == 0)
                {
                    graphMatrix[i][j] = maxValue;
                }
            }
        }

        // print the matrix with index
        for (int i = -1; i < vertexNumber; i++)
        {
            for (int j = -1; j < vertexNumber; j++)
            {
                if (i == -1 && j == -1)
                {
                    std::cout << "\t";
                }
                else if (i == -1)
                {
                    std::cout << j << "\t";
                }
                else if (j == -1)
                {
                    std::cout << i << "\t";
                }
                else
                {
                    (graphMatrix[i][j] != maxValue) ? std::cout << graphMatrix[i][j] << "\t" : std::cout << "\t";
                }
            }
            std::cout << '\n';
            std::cout << '\n';
        }
    }
    else
    {
        std::cout << "Not connected graph" << '\n';
    }
    return graphMatrix;
}
int extractMin(std::vector<int> &C, std::vector<int> &D)
{
    int min = INT_MAX;
    int minIndex;
    for (int i = 0; i < D.size(); i++)
    {
        if (min > D[i])
        {
            min = D[i];
            minIndex = i;
        }
    }

    int result;
    for (int i = 0; i < C.size(); i++)
    {
        // index in D is 0,1,2.. and C value is 2,3,4
        if (C[i] == minIndex + 1)
        {
            result = C[i];
            C.erase(C.begin() + i);
            return result;
        }
    }
    return 0;
}
std::vector<int> dijkstraShortestPath(std::vector<std::vector<int>> G)
{
    std::vector<int> C;
    std::vector<int> V;
    std::vector<int> D;
    int verticesNumber = G[0].size();
    for (int i = 1; i < verticesNumber; i++)
    {
        D.push_back(0);
        D[i - 1] = G[0][i];
    }

    int pathList[verticesNumber][verticesNumber];
    for (int i = 1; i < verticesNumber; i++)
    {
        int v = extractMin(C, D);
        for (int w = 1; w < verticesNumber; w++)
        {
            D[w - 1] = std::min(D[w - 1], D[i - 1] + G[i][w]);
        }
    }
    return D;
}
void randomExample();
void test();
int main()
{
    test();
    std::cout << '\n';
    randomExample();
}
void randomExample()
{
    std::cout << "RandomDirectedGraph: " << '\n';
    std::vector<std::vector<int>> G = createRandomDirectedGraph(5, 15);
    std::vector<int> result = dijkstraShortestPath(G);
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << ' ';
    }
}
void test()
{
    std::cout << "Example: " << '\n';
    std::vector<std::vector<int>> graphMatrix1;
    std::vector<int> temp;
    int maxValue = INT_MAX / 2;
    for (int i = 0; i < 5; i++)
    {
        graphMatrix1.push_back(temp);
        for (int j = 0; j < 5; j++)
        {
            graphMatrix1[i].push_back(maxValue);
        }
    }
    graphMatrix1[0][1] = 10;
    graphMatrix1[0][3] = 5;
    graphMatrix1[1][2] = 1;
    graphMatrix1[1][3] = 2;
    graphMatrix1[2][4] = 4;
    graphMatrix1[3][1] = 3;
    graphMatrix1[3][2] = 9;
    graphMatrix1[3][4] = 2;
    graphMatrix1[4][2] = 6;
    graphMatrix1[4][0] = 7;

    std::vector<int> D = dijkstraShortestPath(graphMatrix1);
    for (int i = 0; i < D.size(); i++)
    {
        std::cout << D[i] << ' ';
    }
}