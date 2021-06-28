#include <iostream>
#include <cmath>

struct Node
{
	bool isRed;
	float value = NAN;
	Node *parent = nullptr;
	Node *left = nullptr;
	Node *right = nullptr;
	Node(){}
	Node(float value): value(value) {}
};

void rotate_left(Node **root, Node **x)
{
	Node *y = (*x)->right;
	(*x)->right = y->left;
	if (y->left != nullptr) y->left->parent = *x;
	y->parent = (*x)->parent;
	if( (*x)->parent == nullptr) *root = y;
	else if(*x == (*x)->parent->left ) (*x)->parent->left = y;
	else (*x)->parent->right = y;

	y->left = *x;
	(*x)->parent = y;
}



int main()
{
	Node *root = new Node(7);
	Node *z = new Node(11);
	Node *A9 = new Node(9);
	Node *A18 = new Node(18);
	Node *B14 = new Node(14);
	Node *B19 = new Node(19);

	root->right = z;
	z->parent = root;
	z->left = A9;
	z->right =A18;	

	A18->parent = z;
	A18->left = B14;
	A18->right = B19;

	rotate_left(&root,&z);

	std::cout << root->value <<'\n';
	std::cout << root->right->value <<'\n';
	std::cout << root->right->left->value <<'\n';
}