#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
//MST 

using namespace std;

class Graph
{
	private:
	vector<vector<int>> adj_matrix;
	int vertices=0;

	int extract_min(vector<bool> Q, vector<float> key)
	{
		float min = numeric_limits<float>::infinity();
		int index_Q; 
		for(int i=0; i < Q.size(); i++)
		{
			if(Q[i] == false && key[i] < min)
			{
				index_Q = i;
				min = key[i];
			}
		}
		return index_Q;
	}

	void print_result(vector<float>parent, vector<float>key)
	{
		for(int i =0; i < this->vertices; i++)
		{
			cout<<parent[i]<<"---"<<i<<'\t'<< key[i]<<'\n';
		}
	}
	public:
	Graph(int vertices): vertices(vertices) 
	{
		for(int row=0; row < vertices; row++)
		{
			vector<int> add_row;
			for(int col=0; col < vertices; col++)
			{
				add_row.push_back(0);
			}
			adj_matrix.push_back(add_row);
		}

	}

	void add_weighted_egde( int from, int to, int weight)
	{
		this->adj_matrix[from][to] = weight;
	}

	void print_adjacency_matrix()
	{
		for(int row=0; row < vertices; row++)
		{
			for(int col=0; col < vertices; col++)
			{
				cout<< this->adj_matrix[row][col]<<'\t';
			}
			putchar('\n');
		}
	}

	void Prim()
	{
		vector<float>key(this->vertices);
		fill(key.begin(),key.end(),numeric_limits<float>::infinity());

		vector<float>parent(this->vertices);

		vector<bool>Q(this->vertices);
		fill(Q.begin(),Q.end(),false);
		
		int source;
		cout<<"available vertex to choose from: 0-"<<this->vertices-1<<'\n';
		cout<<"Enter your Starting Vertex:";
		cin>>source;
		
		key[source] = 0;
		parent[source] =  NAN;

		for(int times=0; times < this->vertices-1; times++)
		{
			int u = extract_min(Q,key);

			Q[u] = true;

			for(int to=0; to < this->vertices; to++)
			{
				if(adj_matrix[u][to] != 0 //for each v adjacent to u
				 && Q[to] == false //not yet added (v ∈ Q) 
				 && adj_matrix[u][to] < key[to])
				 {
					parent[to] = u;
					key[to] = adj_matrix[u][to];
				 } 
			}
		}

		print_result(parent,key);	


	}

};


int main()
{
	
	Graph G1(4);

	G1.add_weighted_egde(0,1,5);
	G1.add_weighted_egde(1,0,5);

	G1.add_weighted_egde(1,2,2);
	G1.add_weighted_egde(2,1,2);
	
	G1.add_weighted_egde(2,3,11);
	G1.add_weighted_egde(3,2,11);

	G1.add_weighted_egde(0,3,12);
	G1.add_weighted_egde(3,0,12);

	G1.add_weighted_egde(0,2,4);
	G1.add_weighted_egde(2,0,4);

	G1.add_weighted_egde(1,3,9);
	G1.add_weighted_egde(3,1,9);

	G1.print_adjacency_matrix();
	G1.Prim();
}
