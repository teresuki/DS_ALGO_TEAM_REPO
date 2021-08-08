#include <iostream>
#include <vector>
#include <stdlib.h> // Calloc
#include <chrono>
#define INF 99999

using namespace std;

struct Node
{
    int pos;
};

struct Graph
{
    vector <Node> Q; // Set of all vertices
    int **L = nullptr; //Adjacency Matrix with weight (Set of Edges alternative)
    int nodeCount = 0;

    Graph(){}
    Graph(vector <Node> nodeList)
    {
        Q = nodeList;
        nodeCount = Q.size();

        //Assign position for nodes in Q
        for(int i = 0; i < nodeCount; ++i)
            Q[i].pos = i;

        //Dynamic allocating 2D array for adjacency Matrix
        //And every value are set to 0
        L = (int**) calloc(nodeCount, sizeof(int*)); // Rows
        for(int i = 0; i < nodeCount; ++i)
         L[i] = (int*) calloc(nodeCount, sizeof(int)); // Columns
    }

    ~Graph()
    {
        for(int i = 0; i < nodeCount; ++i)
         delete L[i];
        delete[] L;
    }

    void addEdge(int u, int v, int weight)
    {
        L[u][v] = weight;
        L[v][u] = weight;
    }

    //Print out adjacency Matrix
    void printWay()
    {
        for(int i = 0; i < Q.size(); ++i)
        {
            for(int j = 0; j < Q.size(); ++j)
                cout << L[i][j] << " ";
            cout << endl;
        }
    }

    void dijkstra()
    {
        vector <Node> C = Q;
        vector <int> D;
        D.resize(nodeCount);
        for(int i = 0; i < nodeCount; ++i)
         D[i] = L[0][i];
        
         vector <vector <bool>> nodeTrack {false};
         nodeTrack.resize(nodeCount);
         for(int i = 0; i < nodeCount; ++i)
         {
            nodeTrack[i].resize(nodeCount);
            if(L[i][0] != 0)
             nodeTrack[i][0] = true; // From Starting node to other node
         }
 
        vector <bool> hasPassed;
        hasPassed.resize(nodeCount, false);
        hasPassed[0] = true;
        for(int i = 1; i < nodeCount; ++i)
        {
            //Choose min D
            int minD = INF;
            int minPos;
            Node v;
            for(int j = 1; j < nodeCount; ++j)
            {
                if(D[j] < minD && hasPassed[j] == false)
                {
                    minD = D[j];
                    minPos = j; 
                    v = Q[j];
                }
            }

            hasPassed[minPos] = true;

            for(int j = 1; j < nodeCount; ++j)
            {
                Node w = Q[j];
                if(Q[j].pos == v.pos)
                continue;

                if(hasPassed[w.pos] == true)
                 continue;
               
                if(L[v.pos][w.pos] == 0)
                 continue;

                if(D[w.pos] < D[v.pos] + L[v.pos][w.pos])
                 continue;
                
                D[w.pos] = D[v.pos] + L[v.pos][w.pos];

                for(int k = 0; k < nodeCount; ++k)
                 nodeTrack[w.pos][k] = nodeTrack[v.pos][k];
                nodeTrack[w.pos][v.pos] = true;
            }
        }

       //Change your desired destination node here (1, 2, 3, 4, 5)
       int result = 4;
       cout << "Shortest total weight to " << result  << ": " << D[result - 1] << endl;
       cout << "Node passed by: ";
       for(int i = 0; i < nodeCount; ++i)
       {
           if(nodeTrack[result-1][i] == true)
            cout << i+1 << " ";
       }
       cout << endl;
    }
};

int main()
{
    auto start = chrono::high_resolution_clock::now();
    
    Node nodes[5];
    int nodeCount = sizeof(nodes) / sizeof(nodes[0]);
    vector <Node> nodeList (nodes, nodes + nodeCount);
    Graph graph(nodeList);
    graph.addEdge(0 ,1, 50);
    graph.addEdge(0, 2, 30);
    graph.addEdge(0, 3, 100);
    graph.addEdge(0, 4, 10);
    graph.addEdge(2, 1, 5);
    graph.addEdge(2, 3, 50);
    graph.addEdge(3, 1, 20);
    graph.addEdge(4, 3, 10);
    //graph.printWay();
    graph.dijkstra();

    auto end = chrono::high_resolution_clock::now();
    double runTime = (double) (chrono::duration_cast <chrono::milliseconds> (end-start).count());
    cout << "Run time: "  << runTime << " ms." << endl;

    return 0;

}