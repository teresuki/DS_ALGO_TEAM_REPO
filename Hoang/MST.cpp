#include <iostream>
#include <vector>
#define INF 999999999;
using namespace std;

static int POS_COUNT = 0;
struct Node
{
    int pos;
    Node()
    {
        pos = POS_COUNT;
        POS_COUNT++;
    }
    Node(int nullPos)
    {pos = nullPos;}
};

struct Graph
{
    vector <Node> Q;
    int **w = nullptr; //Adjacency Matrix with weight
    int nodeCount = 0;
    Graph(){}
    Graph(vector <Node> nodeList)
    {
        Q = nodeList;
        nodeCount = Q.size();

        //Dynamic allocating space for adjacency Matrix
        w = new int*[nodeCount];
        for(int i = 0; i < nodeCount; ++i)
         w[i] = new int[nodeCount];

        for(int i = 0; i < nodeCount; ++i)
        {
            for(int j = 0; j < nodeCount; ++j)
             w[i][j] = 0;
        }
    }

    //Add Edge function
    void addEdge(Node u, Node v, int weight)
    {
        w[u.pos][v.pos] = weight;
        w[v.pos][u.pos] = weight;
    }

    //Print out adjacency Matrix
    void printWay()
    {
        for(int i = 0; i < Q.size(); ++i)
        {
            for(int j = 0; j < Q.size(); ++j)
                cout << w[i][j] << " ";
            cout << endl;
        }
    }

    void MST()
    {
        //Setup
        Node NIL(-1);
        int *key = new int[nodeCount];
        Node *p = new Node[nodeCount];
        bool *passed = new bool[nodeCount]; // boolean of passed (have been gone over) vertices
        for(int i = 0; i < Q.size(); ++i)
         {key[i] = INF; passed[i] = false;}
        key[0] = 0;
        p[0] = NIL;

        Node u, v;
        int ans = 0;
        for(int i = 0; i < nodeCount; ++i)
        {
            //ExtractMinQ
            //We need minKey and minLocation to update passed vertices.
            int minKey = INF;
            int minLocation = 0;
            for(int j = 0; j < nodeCount; ++j)
            {
                if(key[j] < minKey && passed[j] == false)
                 {
                     u = Q[j];
                     minKey = key[j];
                     minLocation = j;
                 }
            }
            cout << "Go from " << p[minLocation].pos << " to " << minLocation << ". Weight: " << minKey << endl;
            ans += minKey;
            passed[minLocation] = true;

            if(i == nodeCount - 1) break; // Passed the last vertex so we stop.
            
            for(int j = 0; j < nodeCount; ++j)
            {
                //Check for adjacent vertices that has not been go through
                if(w[u.pos][j] != 0 && passed[j] == false)
                {
                    v = Q[j];
                    if(w[u.pos][v.pos] < key[v.pos])
                    {
                        p[v.pos] = u;
                        key[v.pos] = w[u.pos][v.pos];
                    }
                }
            }

        }
      //Free dynamic arrays
      delete[] key;
      delete[] p;
      delete[] passed;
      cout << "Total weight of MST: " << ans << endl;
    }
};

int main()
{
    Node A, B, C, D, E, F, G, H;
    vector <Node> nodeList {A,B,C,D,E,F,G,H};
    Graph graph(nodeList);
    graph.addEdge(A,B,12);
    graph.addEdge(A,C,5);
    graph.addEdge(A,D,4);
    graph.addEdge(B,C,9);
    graph.addEdge(B,D,11);
    graph.addEdge(C,D,2);
    graph.addEdge(C,E,2);
    graph.addEdge(C,F,4);
    graph.addEdge(D,E,7);
    graph.addEdge(D,G,1);
    graph.addEdge(E,G,3);
    graph.addEdge(E,H,6);
    graph.addEdge(F,G,8);
    graph.addEdge(F,H,1);

    //graph.printWay();
    graph.MST();

    return 0;
}

