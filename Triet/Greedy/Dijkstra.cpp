#include<iostream>
#include<algorithm>
#include<limits>
#include<map>
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
				add_row.push_back(numeric_limits<double>::infinity());
			}
			adjacency_weighted_matrix.push_back(add_row);
		}
	}


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

	int find_element_of_C_min_D(vector<int> Candidate, vector<double> Distance)
	{
		map<double,int> distance_vertex;
		for(int i=0; i  < Candidate.size(); i++)
		{
			distance_vertex.insert(pair<double,int>(Distance[i],Candidate[i]));
		}
		// sort(distance_vertex.begin(),distance_vertex.end());
		auto v = distance_vertex.begin();
		return v->second;
	}

	void find_min_to_all_verticies()
	{
		int source =0 ;
		vector<int> Candidate;
		vector<double> Distance;
		// cout<<"Possible verticies to choose from include: 0-"<< this->vertices - 1 <<'\n'; 
		// cout<<"Enter the starting vertex: ";
		// cin >> source;

		
		for(int i=0; i < this->vertices; i++)
		{
			if( i != source) Candidate.push_back(i);
		}
		
		for(int i=0; i < this->vertices; i++)
		{
			if(i != source) Distance.push_back(adjacency_weighted_matrix[source][i]);
		}


		for(int i=0; i < this->vertices -1; i++)
		{
			int v = find_element_of_C_min_D(Candidate,Distance);
			for(int j=0; j < Candidate.size();j++)
			{
				if(Candidate[j] == v) 
				{
					Candidate.erase(Candidate.begin() + j);
					break;
				}
			}
			for(int run_C=0; run_C < Candidate.size(); run_C++)
			{
				int w = Candidate[run_C];
				w--;
				Distance[w] = min(Distance[w],Distance[v-1] + adjacency_weighted_matrix[v][w+1]);
			}
		}

		for(int i=0; i < Distance.size(); i++)
		{
			cout << Distance[i]<<'\n';
		}
		
	}	

	void add_weighted_egde( int from, int to, int weight)
	{
		this->adjacency_weighted_matrix[from][to] = weight;
	}
};

int main()
{
	Graph G1(5);
	//s is 0, t is 1, y is 2, x is 3 and z is 4
	// G1.add_weighted_egde(0,1,10);
	// G1.add_weighted_egde(0,2,5);
	// G1.add_weighted_egde(1,2,2);
	// G1.add_weighted_egde(1,3,1);
	// G1.add_weighted_egde(2,1,3);
	// G1.add_weighted_egde(2,3,9);
	// G1.add_weighted_egde(2,4,2);
	// G1.add_weighted_egde(3,4,4);
	// G1.add_weighted_egde(4,3,6);
	// G1.add_weighted_egde(4,0,7);
	G1.add_weighted_egde(0,1,50);
	G1.add_weighted_egde(0,2,30);
	G1.add_weighted_egde(0,3,100);
	G1.add_weighted_egde(0,4,10);
	G1.add_weighted_egde(2,1,5);
	G1.add_weighted_egde(2,3,50);
	G1.add_weighted_egde(3,1,20);
	G1.add_weighted_egde(4,3,10);

	G1.print_adjacency_matrix();
	G1.find_min_to_all_verticies();
}