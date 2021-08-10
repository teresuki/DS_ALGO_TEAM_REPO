// Shortest path by Dijkstra's Algorithm -- generate optimal shortest path in some conditions (non negative weights)
/* Refer to my friends' way, maybe for the problem dealing with a lot of objects (Nodes) like this,
   we should use OOP*/
   
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

#define INF 99999    // INT_MAX will cause error in D[v] + L[v,w]
                     // the logic is ok but still need to understand the basic of language to debug
enum node_list {s, t, x, y, z};

void vector_print(const vector<int>& vec)
{
    for(size_t i = 0; i < vec.size(); i++)
    {
        if(vec[i] == INF)
            cout << "INF" << " ";
        else
            cout << vec[i] << " ";
    }

    cout << endl << endl;
}

void vector_print(const vector<bool>& vec)
{
    for(size_t i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";

    cout << endl << endl;
}

class Graph
{
private:
    int number_of_nodes;
    vector<vector<int>> adjacency_matrix;

public:
    Graph(int number_of_node)
    {
        this->number_of_nodes = number_of_node;

        for(int i = 0; i < number_of_nodes; i++)
        {
            vector<int> vec(number_of_nodes, INF);
            adjacency_matrix.push_back(vec);
        }
    }

    void add_edge(size_t source, size_t destination, int weight)
    {
        adjacency_matrix[source][destination] = weight;
    }

    void print()     // print the adjacency matrix, just for debugging
    {
        for(int i = 0; i < number_of_nodes; i++)
        {
            for(int j = 0; j < number_of_nodes; j++)
            {
                if(adjacency_matrix[i][j] == INF)
                    cout << "INF" << " ";
                else
                    cout << adjacency_matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // shortest path by Dijkstra's algorithm
    vector<int> shortest_path(int starting_node = 0)
    {
        vector<int> C;
        for(int i = 0; i < number_of_nodes; i++)
        {
            if(i != starting_node)
                C.push_back(i);
        }
        // vector_print(C);
        vector<bool> checked_out(C.size(), false);  // to keep track of checked-out element

        vector<int> D;
        for(size_t i = 0; i < C.size(); i++)        // C and D, corresponding 1 by 1
        {
            D.push_back(adjacency_matrix[starting_node][C[i]]);
        }
        // vector_print(D);

        for(int i = 0; i < number_of_nodes - 1; i++)    // repeat n - 1 times;
        {
            // some element of C minimizing D[v]
            int min_D = INF;
            int v;
            for(size_t i = 0; i < C.size(); i++)
            {
                if(checked_out[i] == false)
                {
                    if(D[i] < min_D)     // depend on implementation then should not use && here
                    {
                        min_D = D[i];
                        v = i;
                    }
                }
            }

            checked_out[v] = true;    // C = C \ {v}
            //vector_print(checked_out);

            for(size_t i = 0; i < D.size(); i++)
            {
                if(checked_out[i] == false) // should not use && => undefined behavior of implementation (experience + basic)
                    D[i] = min(D[i], D[v] + adjacency_matrix[C[v]][C[i]]);
            }
            // vector_print(D);
        }

        return D;
    }
};

int main(void)
{
    Graph A(5);

    A.add_edge(0, 1, 50);
    A.add_edge(0, 2, 30);
    A.add_edge(0, 3, 100);
    A.add_edge(0, 4, 10);
    A.add_edge(2, 1, 5);
    A.add_edge(2, 3, 50);
    A.add_edge(3, 1, 20);
    A.add_edge(4, 3, 10);

    cout << "Graph A(in slide): " << endl;
    A.print();

    cout << "Shortest path from node a: " << endl;
    vector<int> result = A.shortest_path(0);
    vector_print(result);


    Graph B(5);

    B.add_edge(s, t, 10);
    B.add_edge(s, y, 5);
    B.add_edge(t, x, 1);
    B.add_edge(t, y, 2);
    B.add_edge(x, z, 4);
    B.add_edge(y, t, 3);
    B.add_edge(y, x, 9);
    B.add_edge(y, z, 2);
    B.add_edge(z, s, 7);
    B.add_edge(z, x, 6);

    cout << "Graph B (in exercise): " << endl;
    B.print();

    cout << "Shortest path from node s: " << endl;
    vector<int> result_2 = B.shortest_path(s);
    vector_print(result_2);

    return 0;
}
