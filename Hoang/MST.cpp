#include <iostream>
#include <vector>
#include <stdlib.h> // Calloc
#include <chrono>
#define INF 999999999;
using namespace std;

int POS_COUNT = 0;
struct Node
{
    int pos;
    Node()
    {
        pos = POS_COUNT;
        POS_COUNT++;
    }
    Node(int nullPos) // for NIL Node
    {
        pos = nullPos;
    }
};

struct Graph
{
    vector<Node> Q;    // Set of all vertices
    int **w = nullptr; //Adjacency Matrix with weight (Set of Edges alternative)
    int nodeCount = 0;

    Graph() {}
    Graph(vector<Node> nodeList)
    {
        Q = nodeList;
        nodeCount = Q.size();

        //Dynamic allocating 2D array for adjacency Matrix
        //And every value are set to 0
        w = (int **)calloc(nodeCount, sizeof(int *)); // Rows
        for (int i = 0; i < nodeCount; ++i)
            w[i] = (int *)calloc(nodeCount, sizeof(int)); // Columns
    }

    ~Graph()
    {
        for (int i = 0; i < nodeCount; ++i)
            delete w[i];
        delete[] w;
    }

    void addEdge(Node u, Node v, int weight)
    {
        w[u.pos][v.pos] = weight;
        w[v.pos][u.pos] = weight;
    }

    //Print out adjacency Matrix
    void printWay()
    {
        for (int i = 0; i < Q.size(); ++i)
        {
            for (int j = 0; j < Q.size(); ++j)
                cout << w[i][j] << " ";
            cout << endl;
        }
    }

    bool isConnectedGraph()
    {
        bool *checked = new bool[nodeCount];
        *checked = {false};
        for (int i = 0; i < nodeCount; ++i)
        {
            for (int j = 0; j < nodeCount; ++j)
            {
                if (w[i][j] != 0)
                {
                    checked[i] = true;
                    checked[j] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < nodeCount; ++i)
        {
            if (checked[i] == false)
                return false;
        }

        return true;
    }

    void MST()
    {
        //Setup
        Node NIL(-1);
        int *key = new int[nodeCount];
        Node *p = new Node[nodeCount];
        bool *hasPassed = new bool[nodeCount]; // to check if that node has been gone through or not. (AKA belongs to MST already)

        for (int i = 0; i < nodeCount; ++i)
        {
            key[i] = INF;
            hasPassed[i] = false;
        }
        key[0] = 0;
        p[0] = NIL;

        Node u, v;
        int ans = 0;
        for (int i = 0; i < nodeCount; ++i)
        {
            //ExtractMinQ
            //We need minKey and minLocation to update hasPassed vertices.
            int minKey = INF;
            int minLocation = 0;
            for (int j = 0; j < nodeCount; ++j)
            {
                if (key[j] < minKey && hasPassed[j] == false)
                {
                    u = Q[j];
                    minKey = key[j];
                    minLocation = j;
                }
            }
            //Stuck check
            if (minKey == 999999999)
            {
                cout << "Stucked " << endl;
                return;
            }
            cout << "Go from " << p[minLocation].pos << " to " << minLocation << ". Weight: " << minKey << endl;
            ans += minKey;
            hasPassed[minLocation] = true;

            if (i == nodeCount - 1)
                break; // hasPassed the last vertex so we stop.

            for (int j = 0; j < nodeCount; ++j)
            {
                v = Q[j];

                //Guard clauses for better readability
                if (w[u.pos][j] == 0)
                    continue;

                if (hasPassed[j] == true)
                    continue;

                if (w[u.pos][v.pos] >= key[v.pos])
                    continue;

                p[v.pos] = u;
                key[v.pos] = w[u.pos][v.pos];
            }
        }

        //Free dynamic arrays
        delete[] key;
        delete[] p;
        delete[] hasPassed;

        cout << "Total weight of MST: " << ans << endl;
    }
};

int main()
{
    auto start = chrono::high_resolution_clock::now();

    Node A, B, C, D, E, F, G, H;
    vector<Node> nodeList{A, B, C, D, E, F, G, H};
    Graph graph(nodeList);
    graph.addEdge(A, B, 12);
    graph.addEdge(A, C, 5);
    graph.addEdge(A, D, 4);
    graph.addEdge(B, C, 9);
    graph.addEdge(B, D, 11);
    graph.addEdge(C, D, 2);
    graph.addEdge(C, E, 2);
    graph.addEdge(C, F, 4);
    graph.addEdge(D, E, 7);
    graph.addEdge(D, G, 1);
    graph.addEdge(E, G, 3);
    graph.addEdge(E, H, 6);
    graph.addEdge(F, G, 8);
    graph.addEdge(F, H, 1);

    //graph.printWay();

    graph.MST();
    auto end = chrono::high_resolution_clock::now();
    double runTime = (double)(chrono::duration_cast<chrono::milliseconds>(end - start).count());
    cout << "Run time: " << runTime << " ms." << endl;

    return 0;
}
