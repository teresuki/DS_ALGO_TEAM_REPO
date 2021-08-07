#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

	int find_element_of_C_min_D(map<double,int> distance_vertex)
	{
		// sort(distance_vertex.begin(),distance_vertex.end());
		auto v = distance_vertex.begin();
		return v->second;
	}

int main()
{
	map<double,int> distance_vertex;
	distance_vertex.insert(pair<double,int>(100,2));	
	distance_vertex.insert(pair<double,int>(10,1));	

	cout << find_element_of_C_min_D(distance_vertex);
}