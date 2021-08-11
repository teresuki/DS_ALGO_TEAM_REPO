#include<iostream>
#include<algorithm>
#include<limits>
#include<vector>

using namespace std;

class Graph
{
	private:
	vector< vector<double> > adjacency_weighted_matrix;
	int vertices=0;
	public:
	Graph(int vertices): vertices(vertices)
	{
		for(int row=0; row < vertices; row++)
		{
			vector<double> add_row;
			for(int col=0; col < vertices; col++)
			{
				add_row.push_back(0);
			}
			adjacency_weighted_matrix.push_back(add_row);
		}
	}

	int find_index_min_D(vector<double> D, vector<bool> S) //find vertex of 
	{
		double min = numeric_limits<double>::infinity(); //min is as big as possible so that any number smaller than it is picked immediately
		int index_min_D; //result that will be returned 
		for(int i=0; i < D.size(); i++) //D and S both have the same size
		{
			if(S[i] == false && D[i] < min)
			{
				min = D[i];
				index_min_D = i; //the index with the smallest value for now
			}
		}
		return index_min_D;
	}

	void print_final_result(vector<double> D)
	{
		for(int i=0; i < D.size(); i ++)
		{
			cout<<i <<'\t' << D[i] <<'\n';
		}
	}

	public:
	void print_adjacency_matrix()
	{
		for(int row=0; row < vertices; row++)
		{
			for(int col=0; col < vertices; col++)
			{
				cout<< this->adjacency_weighted_matrix[row][col]<<'\t';
			}
			putchar('\n');
		}
	}

	void add_weighted_egde( int from, int to, int weight)
	{
		this->adjacency_weighted_matrix[from][to] = weight;
	}


	void find_min_weight_to_all()
	{
		int source;
		cout<<"Enter the starting vertex(source): ";
		cout<<"available sources are: 0-"<<this->vertices -1 <<'\n';
		cin>>source;

		vector<bool> S(this->vertices); //list of nodes whose minimal distance from the source is already known
		fill(S.begin(),S.end(),false);  //Since we haven't done anything yet no node is currently include in our solution

		vector<double> D(this->vertices); //a list containing the distance value from the source node to that node, from the source node to itself the value is 0
		//Since I don't want to deal with changing index caused by not including source in the D list, I will include it in the list (a waste of space)
		fill(D.begin(),D.end(), numeric_limits<double>::infinity());

		//set distance to source to 0 so it will be picked first
		D[source] = 0;

		for(int time=0; time < this->vertices -1; time++) //repeat N-1 times
		{
			int u = find_index_min_D(D, S);
	
			S[u] = true;
	
			// Update dist value of the adjacent vertices of the picked vertex.
			for (int v = 0; v < this->vertices; v++)
				if (S[v] == false && adjacency_weighted_matrix[u][v] != 0 && D[u] != numeric_limits<double>::infinity()
					&& D[u] + adjacency_weighted_matrix[u][v] < D[v])
					D[v] = D[u] + adjacency_weighted_matrix[u][v];
		}	
		print_final_result(D);
	}
};

int main()
{
	Graph G1(5);

	// s is 0, t is 1, y is 2, x is 3 and z is 4

	G1.add_weighted_egde(0,1,10);
	G1.add_weighted_egde(0,3,5);
	G1.add_weighted_egde(1,2,1);
	G1.add_weighted_egde(1,3,2);
	G1.add_weighted_egde(2,4,4);
	G1.add_weighted_egde(3,1,3);
	G1.add_weighted_egde(3,2,9);
	G1.add_weighted_egde(3,4,2);
	G1.add_weighted_egde(4,0,7);
	G1.add_weighted_egde(4,2,6);



	// G1.add_weighted_egde(0,1,50);
	// G1.add_weighted_egde(0,2,30);
	// G1.add_weighted_egde(0,3,100);
	// G1.add_weighted_egde(0,4,10);
	// G1.add_weighted_egde(2,1,5);
	// G1.add_weighted_egde(2,3,50);
	// G1.add_weighted_egde(3,1,20);
	// G1.add_weighted_egde(4,3,10);

	G1.print_adjacency_matrix();
	putchar('\n');
	G1.find_min_weight_to_all();
}