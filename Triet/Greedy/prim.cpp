#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
//MST 

using namespace std;


#define V 4

int Extract_min(int key[],bool vertex_in_MST[])
{
	int min= INT_MAX, result;
	for(int i=0; i < V; i++)
	{
		if( key[i] < min && vertex_in_MST[i] == false )
		{
			min = key[i];
			result = i;
		}
	}
	return result;
}


void printMST(int parent[], int graph[V][V])
{
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
}

void find_MST_prim(int Graph[V][V])
{
	int key[V];
	int parent[V];
	bool vertex_in_MST[V];

	for(int i=0; i < V; i++)
	{
		key[i] = INT_MAX;
		vertex_in_MST[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;// root does not have a parent

	for(int edge=0; edge < V-1;edge++)
	{
		int u = Extract_min(key,vertex_in_MST);

		vertex_in_MST[u] = true;
		for(int destination=0; destination < V; destination++)
		{
			if(Graph[u][destination] != 0 && vertex_in_MST[destination] == false && Graph[u][destination] < key[destination])
			{
				parent[destination] = u;
				key[destination] = Graph[u][destination];
			}	
		}
	}
	printMST(parent, Graph);

 }

int main()
{
	int matrix[V][V] = {{0,5,4,12},
					  {5,0,2,9},
					  {4,2,0,11},
					  {12,9,11,0}};
	
	find_MST_prim(matrix);
}
