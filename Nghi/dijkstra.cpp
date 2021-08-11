#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <map>

using namespace std;

#define INF 9999
//Graph is represented by adjacency matrix
class Graph {
public:
	int numNode;
	vector<vector<int>> matrix;

	Graph(int numNode): numNode(numNode) {
		for (int i = 0; i<numNode; i++) {
			vector<int> temp;
			for (int j = 0; j<numNode; j++) {
				temp.push_back(INF);
			}
			matrix.push_back(temp);
		}
	}

	void addEdge(int source, int destination, int weight) {
		matrix[source][destination] = weight;
	}

	void printMatrix() {
		for (int i = 0; i<matrix.size(); i++) {
			for (int j = 0; j<matrix.size(); j++) {
				cout<<matrix[i][j]<<"\t";
			}
			cout<<endl;
		}
	}

	void dijkstra(int start) {
		//initialize C,D and S
		//C stores all the nodes that we haven't checked
		vector<int> C;
		//D stores the current distance from starting node to each other node
		//it's a map, each pair has two values: index of the node, distance to that node
		map<int, int> D;
		//S stores all of the nodes that we have checked
		vector<int> S;

		//add "start" to S
		S.push_back(start);
		for (int i = 0; i<numNode; i++) {
			//because we have added "start" to S,
			//Insert into C other nodes (that are not "start")
			//Update D with the distance from "start" to other nodes (that are not "start")
			if (i!=start) {
				C.push_back(i);
				D.insert({i, matrix[start][i]});
			}
		}

		//repeat n-1 times for n-1 nodes (except from starting node)
		for (int i = 0; i<numNode-1; i++) {
			//find node with min cost in D
			int min_node = C[0];
			for (int j = 0; j<C.size(); j++) {
				if (D[C[j]] < D[min_node]) {
					min_node = C[j];
				}
			}

			//add that node to S
			S.push_back(min_node);

			//delete that node from C
			int find;
			for (int j = 0; j<C.size(); j++) {
				if (C[j] == min_node) {
					find = j;
				}
			}
			C.erase(C.begin() + find);

			//update D with new minimal cost
			for (int j = 0; j<C.size(); j++) {
				D[C[j]] = min(D[C[j]], D[min_node] + matrix[min_node][C[j]]);
			}
		}

		cout<<"This is the minimum cost to get from 0 to other nodes: "<<endl;
		cout<<"(0 = s;    1 = t;    2 = x;    3 = y;    4 = z)"<<endl;
		for (auto i = D.begin(); i!=D.end(); i++) {
			cout<<"0 to "<<i->first<<": "<<i->second<<endl;
		}
	}
};

int main() {
	
	Graph g(5);

	g.addEdge(0,1,10);
	g.addEdge(0,3,5);
	g.addEdge(1,2,1);
	g.addEdge(1,3,2);
	g.addEdge(2,4,4);
	g.addEdge(3,1,3);
	g.addEdge(3,2,9);
	g.addEdge(3,4,2);
	g.addEdge(4,0,7);
	g.addEdge(4,2,6);

	int s;
	cout<<"Choose your starting node (0-4): ";
	cin>>s;

	g.dijkstra(s);

}