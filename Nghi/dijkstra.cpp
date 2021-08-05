#include <iostream>
#include <string>
#include <vector>
#include <climits>

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

	void dijkstra() {
		//initialize C,D and S
		vector<int> C;
		vector<int> D;
		vector<int> S;
		S.push_back(0);
		for (int i = 0; i<numNode - 1; i++) {
			C.push_back(i+1);
			D.push_back(matrix[0][i+1]);
		}

		//repeat n-1 times for n-1 nodes (except from starting node)
		for (int i = 1; i<numNode; i++) {
			//find node with min cost in D
			int min_node = C[0] - 1;
			for (int j = 0; j<C.size(); j++) {
				//the cost from 0 to 1 is actually stored at D[0],
				//so to access the cost from 0 to i, we minus 1
				if (D[C[j]-1] < D[min_node]) {
					min_node = C[j]-1;
				}
			}
			//Because we have minus 1 to fit D as above,
			//we need to plus 1 to get the correct node
			min_node++;

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
				D[C[j]-1] = min(D[C[j]-1], D[min_node-1] + matrix[min_node][C[j]]);
			}
		}

		cout<<"This is the minimum cost to get from 0 to other nodes: "<<endl;
		cout<<"(0 = s;    1 = t;    2 = x;    3 = y;    4 = z)"<<endl;
		for (int i = 0; i<D.size(); i++) {
			cout<<"0 to "<<i+1<<": "<<D[i]<<endl;
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

	g.dijkstra();

}