#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

class Node {
public:
	int key;
	Node* left = nullptr; //left child
	Node* right = nullptr; //right child
	Node* parent = nullptr; //parent
	Node(int key): key(key) {}
};

class Tree {
public:
	Node* root = nullptr;
	void insert(Node* z) {
		Node* y = nullptr;
		Node* x  = root;
		while (x!=nullptr) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y==nullptr) {
			root = z;
		}
		else if(z->key < y->key) {
			y->left = z;
		}
		else {
			y->right = z;
		}
	}
	Node* search(int k) {
		Node* x = root;
		while (x!=nullptr && k!=x->key) {
			if(k<x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		return x;
	}
	Node* maximum() {
		Node* x = root;
		while ((x->right)!=nullptr) {
			x = x->right;
		}
		return x;
	}
	Node* minimum() {
		Node* x = root;
		while ((x->left)!=nullptr) {
			x = x->left;
		}
		return x;
	}
	Node* successor(Node* x) {
		if (x->right != nullptr) {
			x = x->right;
			while ((x->left)!=nullptr) {
				x = x->left;
			}
			return x;
		}
		else {
			Node* y = x->parent;
			while ((y!=nullptr) && (x==y->right)) {
				x = y;
				y = x->parent;
			}
			return y;
		}
	}
	Node* predecessor(Node* x) {
		if (x->left != nullptr) {
			x = x->left;
			while ((x->right)!=nullptr) {
				x = x->right;
			}
			return x;
		}
		else {
			Node* y = x->parent;
			while ((y!=nullptr) && (x==y->left)) {
				x = y;
				y = x->parent;
			}
			return y;
		}
	}
	void transplant(Node* u, Node* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		if (v != nullptr) {
			v->parent = u->parent;
		}
	} 
	void delete_node(Node* z) {
		if (z->left == nullptr) {
			transplant(z, z->right);
		}
		else if(z->right == nullptr) {
			transplant(z, z->left);
		} 
		else {
			Node* y = z->right;
			while ((y->left)!=nullptr) {
				y = y->left;
			}
			if (y->parent != z) {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			else {
				transplant(z, y);
			}
			y->left = z->left;
			y->left->parent = y;
		}
	}
	void inorder_walk(Node* x) {
		if (x!=nullptr) {
			inorder_walk(x->left);
			cout<<x->key<<"   ";
			inorder_walk(x->right);
		}
	}
};

int main() {
	Tree T;

	//construct tree from user input
	vector<Node> nodes;
	cout<<"Please input the keys for the tree. Input 'e' to stop."<<endl<<endl;
	string input_string;
	while (true) {
		cout<<"Enter key: ";
		cin>>input_string;
		if (input_string.compare("e")==0) {break;}
		nodes.push_back(Node(stoi(input_string)));
	}

	for (int i = 0; i<nodes.size(); i++) {
		T.insert(&nodes.at(i));
	}

	//print out all the nodes before and after deletion of 13
	cout<<endl<<"Inorder walk: ";
	T.inorder_walk(T.root);
	cout<<endl;

	T.delete_node(T.search(13));

	cout<<endl<<"Inorder walk: ";
	T.inorder_walk(T.root);
	cout<<endl;

	cout<<"Tree's maximum is "<<(T.maximum())->key<<endl;
	cout<<"Tree's minimum is "<<T.minimum()->key<<endl;

	//ask for a key, print out information about that node
	int user_input;
	cout<<endl<<endl<<"Which key do you want?"<<endl;
	cin>>user_input;
	if ((T.search(user_input)->parent)!=nullptr) {
		cout<<"Parent's key is "<<(T.search(user_input)->parent)->key<<endl;
	}
	if ((T.search(user_input)->left)!= nullptr) {
		cout<<"Left child's key is "<<(T.search(user_input)->left)->key<<endl;
	}
	if ((T.search(user_input)->right)!= nullptr) {
		cout<<"Right child's key is "<<(T.search(user_input)->right)->key<<endl;
	}
	if ((T.successor(T.search(user_input)))!=nullptr) {
		cout<<"Successor's key is "<<(T.successor(T.search(user_input)))->key<<endl;
	}
	if ((T.predecessor(T.search(user_input)))!=nullptr) {
		cout<<"Predecessor's key is "<<(T.predecessor(T.search(user_input)))->key<<endl;
	}
}