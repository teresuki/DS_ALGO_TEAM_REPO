#include <iostream>
#include <time.h>
#include <vector>

std::vector<std::vector<int>> createRandomGraph(int vertexNumber, int edgeNumber)
{
    srand(time(NULL));
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
                graphMatrix[col][row] = value;
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
                    (graphMatrix[i][j] != 0) ? std::cout << graphMatrix[i][j] << "\t" : std::cout << "\t";
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

bool isBelong(std::vector<int> Q, int v)
{
    for (int i = 0; i < Q.size(); i++)
    {
        if (Q[i] == v)
        {
            return true;
        }
    }
    return false;
}

// get the min value to the top
void sortMin(std::vector<int> &Q, std::vector<int> &key)
{
    int min = INT_MAX;
    int minVertex;
    for (int i = 0; i < key.size(); i++)
    {
        if ((min >= key[i]) && isBelong(Q, i))
        {
            min = key[i];
            minVertex = i;
        }
    }
    for (int i = 0; i < Q.size(); i++)
    {
        if (Q[i] == minVertex)
        {
            std::swap(Q[0], Q[i]);
            break;
        }
    }
}
int extractMin(std::vector<int> &Q)
{
    int min = Q[0];
    Q.erase(Q.begin());
    return min;
}

// primm's algorithm for minimum spanning tree
std::vector<int> primm(std::vector<std::vector<int>> G, int r)
{
    std::vector<int> key;
    std::vector<int> p;
    std::vector<int> Q;
    std::vector<int> minimumSpanningTree;
    // initialize value
    int vertexNumber = G[0].size();
    for (int i = 0; i < vertexNumber; i++)
    {
        std::vector<int> temp;
        key.push_back(INT_MAX);
        p.push_back(-1);
        Q.push_back(i);
        // root of spanning tree
        if (i == r)
        {
            key[i] = 0;
            p[i] = i;
        }
    }
    // primm's algorithm
    while (Q.size() != 0)
    {
        sortMin(Q, key);
        int u = extractMin(Q);
        minimumSpanningTree.push_back(u);
        for (int v = 0; v < vertexNumber; v++)
        {
            if (G[u][v] != 0)
            {
                if (isBelong(Q, v) && (G[u][v] < key[v]))
                {
                    p[v] = u;
                    key[v] = G[u][v];
                }
            }
        }
    }

    // print the result
    std::cout << "Order:" << '\t';
    for (int i = 0; i < vertexNumber; i++)
    {
        std::cout << minimumSpanningTree[i] << '\t';
    }
    std::cout << '\n';
    std::cout << "vertex:" << '\t';
    for (int i = 0; i < vertexNumber; i++)
    {
        std::cout << i << '\t';
    }
    std::cout << '\n';
    std::cout << "p:" << '\t';
    for (int i = 0; i < vertexNumber; i++)
    {
        std::cout << p[i] << '\t';
    }
    return minimumSpanningTree;
}
void test();
void randomizeGraph();
int main()
{
    std::cout << "Test Case: " << '\n';
    test();
    std::cout << "\n\n";
    std::cout << "Random graph:" << '\n';
    randomizeGraph();
}

void randomizeGraph()
{
    srand(time(NULL));
    std::vector<std::vector<int>> graphMatrix = createRandomGraph(5, 10);
    int vertexNumber = graphMatrix[0].size();
    int r = rand() % vertexNumber; // choose random root
    std::vector<int> minimumSpanningTree = primm(graphMatrix, r);
}
void test()
{
    std::vector<std::vector<int>> graphMatrix1;
    std::vector<int> temp;
    for (int i = 0; i < 8; i++)
    {
        graphMatrix1.push_back(temp);
        for (int j = 0; j < 8; j++)
        {
            graphMatrix1[i].push_back(0);
        }
    }
    graphMatrix1[0][1] = 12;
    graphMatrix1[1][0] = 12;
    graphMatrix1[0][2] = 5;
    graphMatrix1[2][0] = 5;
    graphMatrix1[0][3] = 4;
    graphMatrix1[3][0] = 4;
    graphMatrix1[1][2] = 9;
    graphMatrix1[2][1] = 9;
    graphMatrix1[1][3] = 11;
    graphMatrix1[3][1] = 11;
    graphMatrix1[2][3] = 2;
    graphMatrix1[3][2] = 2;
    graphMatrix1[2][4] = 2;
    graphMatrix1[4][2] = 2;
    graphMatrix1[2][5] = 4;
    graphMatrix1[5][2] = 4;
    graphMatrix1[3][4] = 7;
    graphMatrix1[4][3] = 7;
    graphMatrix1[3][6] = 1;
    graphMatrix1[6][3] = 1;
    graphMatrix1[4][6] = 3;
    graphMatrix1[6][4] = 3;
    graphMatrix1[4][7] = 6;
    graphMatrix1[7][4] = 6;
    graphMatrix1[5][7] = 1;
    graphMatrix1[7][5] = 1;
    graphMatrix1[5][6] = 8;
    graphMatrix1[6][5] = 8;

    int vertexNumber = graphMatrix1[0].size();
    // int r = rand() % vertexNumber;
    int r = 0;
    std::vector<int> minimumSpanningTree = primm(graphMatrix1, r);
}