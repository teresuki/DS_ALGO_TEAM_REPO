#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

class Node {
public:
	int key;
	//0 is black, 1 is red
	bool colour = 0;
	Node* left = nullptr; //left child
	Node* right = nullptr; //right child
	Node* parent = nullptr; //parent
	Node(int key): key(key) {}
};

class Tree {
public:
	Node* root = nullptr;
	void left_rotate(Node* x) {
		if(x->right != nullptr) {
			Node* y = x->right;
			x->right = y->left;
			if (y->left != nullptr) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr) {
				root = y;
			}
			else if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}
		else {
			cout<<"Cannot left rotate!"<<endl;
		}
	}
	void right_rotate(Node* x) {
		if(x == x->parent->left) {
			Node* y = x->parent;
			y->left = x->right;
			if (x->right != nullptr) {
				x->right->parent = y;
			}
			x->parent = y->parent;
			if (y->parent == nullptr) {
				root = x;
			}
			else if (y == y->parent->left) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
			x->right = y;
			y->parent = x;
		}
		else {
			cout<<"Cannot right rotate!"<<endl;
		}
	}
	void insert_fixup(Node* z) {
		while ((z->parent != nullptr) && (z->parent->colour == 1)) {
			if (z->parent->parent->left!=nullptr && z->parent == z->parent->parent->left) {
				Node* y = z->parent->parent->right;
				if (y!=nullptr && y->colour == 1) {
					z->parent->colour = 0;
					y->colour = 0;
					z->parent->parent->colour = 1;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {
					z = z->parent;
					left_rotate(z);
				}
				else {
					z->parent->colour = 0;
					z->parent->parent->colour = 1;
					right_rotate(z->parent->parent);
				}
			}
			else if (z->parent->parent->right!=nullptr && z->parent == z->parent->parent->right) {
				Node* y = z->parent->parent->left;
				if (y!=nullptr && y->colour == 1) {
					z->parent->colour = 0;
					y->colour = 0;
					z->parent->parent->colour = 1;
					z = z->parent->parent;
				}
				else if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				else {
					z->parent->colour = 0;
					z->parent->parent->colour = 1;
					left_rotate(z->parent->parent);
				}
			}
			else {
				break;
			}
		}
		root->colour = 0;
	}
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
		z->colour = 1;
		insert_fixup(z);
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
	void inorder_walk(Node* x) {
		if (x!=nullptr) {
			inorder_walk(x->left);
			cout<<x->key;
			if (x->colour == 0) {
				cout<<"B";
			}
			else {
				cout<<"R";
			}
			cout<<" ";
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

	cout<<endl<<"Inorder walk: ";
	T.inorder_walk(T.root);
	cout<<endl<<endl;

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