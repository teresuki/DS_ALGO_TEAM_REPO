#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define COUNT 10

class Node {
public:
	char c; //character
	int f; //frequency
	Node* left = nullptr; //left child
	Node* right = nullptr; //right child
	Node* parent = nullptr; //parent

	Node(char c, int f)
	: c(c), f(f) {}
};

class Huffman {
public:
	vector<Node*> list; //frequency list
	map<char, int> code; //characters and their corresponding Huffman codes
	int num_char; //number of chars

	//destructor to dellocate all the memory taken up by tree nodes
	~Huffman() {
		for (int i = 0; i<list.size(); i++) {
			delete(list[i]);
		}
	}

	//turn a string s into the frequency list
	void init_freq(string s) {
		for (int i = 0; i<s.length(); i++) {
			bool exist = false;
			Node* item;
			for (int j = 0; j<list.size(); j++) {
				if (s[i]==(list[j]->c)) {
					exist = true;
					item = list[j];
					break;
				}
			}

			if (exist) {
				(item->f)++;
			}
			else {
				Node* temp = new Node(s[i],1);
				list.push_back(temp);
			}
		}
		num_char = list.size();
	}

	void print_freq() {
		cout<<"This is the frequency list: "<<endl;
		for (int i = 0; i<list.size(); i++) {
			cout<<"\t"<<list[i]->c<<": "<<list[i]->f<<endl;
		}
	}

	Node* extract_min() {
		int min = 0;
		for (int i = 0; i<list.size(); i++) {
			if (list[i]->f < list[min]->f) {
				min = i;
			}
		}
		Node* temp = list[min];
		list.erase(list.begin() + min);
		return temp;
	}
	void printArray(int arr[], int n) {
		int i;
		for (i = 0; i < n; ++i)
		cout << arr[i];

		cout << "\n";
	}
	void printHCodes(Node *root, int arr[], int top) {
		if (root->left) {
			arr[top] = 0;
			printHCodes(root->left, arr, top + 1);
		}
		if (root->right) {
			arr[top] = 1;
			printHCodes(root->right, arr, top + 1);
		}
		if (!((root->left)||(root->right))) {
			cout << root->c << "  | ";
			printArray(arr, top);
		}
	}

	void encoding() {
		while (list.size()>1) {
			//extract two min nodes
			Node* x = extract_min();
			Node* y = extract_min();

			//special character to denote this doesn't contain a character, i.e, not a leaf
			Node* z = new Node('$', x->f + y->f);

			z->left = x;
			z->right = y;
			x->parent = z;
			y->parent = z;

			list.push_back(z);
		}

		cout<<"This is Huffman encoding table: "<<endl;
		int arr[10];
		printHCodes(list[0],arr,0);
	}
};

int main() {
	Huffman h;
	h.init_freq("floccinaucinihilipilification");
	h.print_freq();
	h.encoding();
}