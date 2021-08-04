#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Node {
public:
	int k;
};

//priority queue is implemented using heap
//items inside are pairs, with pair.first is the index/node, and pair.second is the key
class MinPriorityQueue {	
public:
	vector<pair<int,int*>> queue;

	void heapify(int i) {
		int smallest = i;
		int left = i*2 + 1;
		int right = i*2 + 2;
		if ((left<queue.size()) && (*queue[left].second < *queue[smallest].second)) {
			smallest = left;
		}
		if ((right<queue.size()) && (*queue[right].second <*queue[smallest].second)) {
			smallest = right;
		}
		if (smallest!=i) {
			swap(queue[i], queue[smallest]);
			heapify(smallest);
		}
	}
	//using the heapify() method above, we wrap it in a for loop to
	//heapify through all nodes
	void heapify_all() {
		for (int i = (queue.size()/2) - 1; i>=0; i--) {
			heapify(i);
		}
	}

	void insert(int index, int* key) {
		pair<int,int*> p(index,key);
		if (queue.size() == 0) {
			queue.push_back(p);
		}
		else {
			queue.push_back(p);
			heapify_all();
		}
	}
	int extract_min() {
		int temp = queue[0].first;
		queue.erase(queue.begin());
		heapify_all();
		return temp;
	}
	void print() {
		for (int i = 0; i<queue.size(); i++) {
			cout<<queue[i].first<<":"<<*queue[i].second<<endl;
		}
	}
	int size() {
		return queue.size();
	}
	bool contain(int index) {
		for (int i = 0; i<queue.size(); i++) {
			if (index == queue[i].first) {
				return true;
			}
		}
		return false;
	}
};

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
		MinPriorityQueue Q;
		for (int i = 0; i<numNode; i++) {
			Q.insert(i, &k[i]);
		}

		while (Q.size() != 0) {
			int u = Q.extract_min();
			for (int v = 0; v<numNode; v++) {
				if(matrix[u][v]>0) {
					if ((Q.contain(v)) && (matrix[u][v] < k[v])) {
						p[v] = u;
						k[v] = matrix[u][v];
					}
				}
			}
			//because there's a change to k so we must heapify
			Q.heapify_all();
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