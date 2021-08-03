#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
//MST 

using namespace std;

//Create a C++ pair container to store the weight and the start and end point into an edge instance. 
//rmb that we are operating on a weighted graph
typedef pair<char, char> start_end;

class Graph
{
	private:
	set<char> all_vertex;
	vector< pair<int, start_end> > weighted_edges;
	vector< pair<int, start_end> > MST;

	public:
	void add_weighted_edge(int weight, char start, char end)
	{
		weighted_edges.push_back({weight,{start,end}});
		all_vertex.insert(start);
		all_vertex.insert(end);
	}

	void print_all_edges()
	{
		for(int i=0; i <weighted_edges.size(); i++)
		{
			cout<<weighted_edges[i].second.first<<"----" << weighted_edges[i].second.second<<"\t" <<weighted_edges[i].first<<'\n';
		}
	}

	void print_MST()
	{
		for(int i=0; i <MST.size(); i++)
		{
			cout<<MST[i].second.first<<"----" << MST[i].second.second<<"\t" <<MST[i].first<<'\n';
		}
	}

	void print_all_vertex()
	{
		
		set<char>::iterator vertex_itr;
		for(vertex_itr= all_vertex.begin(); vertex_itr != all_vertex.end(); vertex_itr++)
		{
			cout<< *vertex_itr <<'\n';
		}
		
	}

	void MST_Kruskal()
	{
		set<char> MST_vertex;
		set<char> add_MST_vertex;

		sort(weighted_edges.begin(),weighted_edges.end());
		while(MST_vertex != all_vertex)
		{
			add_MST_vertex = MST_vertex;
			char from = weighted_edges[0].second.first;
			char to = weighted_edges[0].second.second;
			add_MST_vertex.insert(from);
			add_MST_vertex.insert(to);

			if(add_MST_vertex != MST_vertex)
			{
				MST.push_back(weighted_edges[0]);
				set<char>::iterator new_vertex;
				for(new_vertex = add_MST_vertex.begin(); new_vertex != add_MST_vertex.end(); new_vertex++)
				{
					MST_vertex.insert(*new_vertex);
				}
			}
			weighted_edges.erase(weighted_edges.begin());

		}

	}


};

int main()
{
	Graph G;
	G.add_weighted_edge(12,'A','B');
	G.add_weighted_edge(5,'A','C');
	G.add_weighted_edge(4,'A','D');

	G.add_weighted_edge(9,'B','C');
	G.add_weighted_edge(11,'B','D');
	G.add_weighted_edge(2,'C','D');
	G.MST_Kruskal();
	G.print_MST();
		// G.print_MST();
	// G.print_all_edges();


}
