#include <iostream>
#include <limits>

using namespace std;


void prim_algo(int Vertex, int graph[Vertex][Vertex])
{
	int from[Vertex];

	int key[Vertex];

	bool MST_vertex[Vertex];

	for(int i=0; i < Vertex; i++)
	{
		key[i] = numeric_limits<int>::max();
		MST_vertex[i] = false;
	}
	key[0] = 0;
	from[0] = -1; //parent of root doesn't exist

	for(int i=0; i < Vertex -1; i++)
	{
			
	}

}


int main()
{
	int graph[4][4] = {{0,5,4,12},
						{5,0,2,9},
						{4,2,0,11},
						{12,9,11,0}};
}