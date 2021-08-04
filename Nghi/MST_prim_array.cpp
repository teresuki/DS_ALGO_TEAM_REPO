#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

//Graph is represented by adjacency matrix
class Graph {
public:
	int numNode;
	vector<vector<int>> matrix;

	Graph(int numNode): numNode(numNode) {
		for (int i = 0; i<numNode; i++) {
			vector<int> temp;
			for (int j = 0; j<numNode; j++) {
				temp.push_back(0);
			}
			matrix.push_back(temp);
		}
	}

	void addEdge(int a, int b, int weight) {
		matrix[a][b] = weight;
		matrix[b][a] = weight;
	}

	void prim_MST() {
		vector<int> k;
		vector<int> p;
		for (int i = 0; i<numNode; i++) {
			k.push_back(INT_MAX);
		}
		for (int i = 0; i<numNode; i++) {
			p.push_back(-1); //-1 to denote non-existent node, i.e NIL
		}

		k[0] = 0;

		//create a min priority queue with all k[i]
		vector<pair<int,int*>> Q;

		for (int i = 0; i<numNode; i++) {
			Q.push_back(std::make_pair(i, &k[i]));
		}

		while (Q.size()>0) {
			//extract min
			int u = 0;
			int min_index = 0; //record the index of the min
			for (int i = 0; i<Q.size(); i++) {
				if (*Q[i].second < *Q[min_index].second) {
					u = Q[i].first;
					min_index = i;
				} 
			}
			Q.erase(Q.begin() + min_index);

			for (int v = 0; v<numNode; v++) {
				if(matrix[u][v]>0) {
					//check if Q contains v
					bool contain_v = false;
					if (Q.size()>0) {
						for (int i = 0; i<Q.size(); i++) {
							if (v==Q[i].first) {
								contain_v = true;
							}
						}
					}
					if ((contain_v) && (matrix[u][v] < k[v])) {
						p[v] = u;
						k[v] = matrix[u][v];
					}
				}
			}
		}


		cout<<"These edges belong to the MST: "<<endl;
		for (int i = 1; i<k.size(); i++) {
			cout<<i<<" to "<<p[i]<<": "<<k[i]<<endl;
		}
	}
};

int main() {
	
	Graph g(8);
	g.addEdge(0,1,12);
	g.addEdge(0,2,5);
	g.addEdge(0,3,4);
	g.addEdge(1,2,9);
	g.addEdge(1,3,11);
	g.addEdge(2,3,2);
	g.addEdge(2,4,2);
	g.addEdge(2,5,4);
	g.addEdge(3,4,7);
	g.addEdge(3,6,1);
	g.addEdge(4,6,3);
	g.addEdge(4,7,6);
	g.addEdge(5,6,8);
	g.addEdge(5,7,1);

	g.prim_MST();

}