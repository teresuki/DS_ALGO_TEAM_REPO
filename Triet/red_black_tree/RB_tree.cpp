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

void rotate_right(Node **root, Node **x)
{
	Node *y = (*x)->left;
	(*x)->left = y->right;
	if(y->right !=  nullptr) y->right->parent = *x;
	y->parent = (*x)->parent;

	if( (*x)->parent == nullptr ) *root = y;
	else if( *x == (*x)->parent->right ) (*x)->parent->right =y;
	else (*x)->parent->left = y;

	y->right = *x;
	(*x)->parent = y;
}

void RB_insert_fixup(Node **z, Node **root, Node **parent_current_node)
{
	while( (*z)->parent->isRed == true )
	{
		if( (*z)->parent == (*z)->parent->parent->left)
		{
			(*parent_current_node) = (*z)->parent->parent->right;
			if( (*parent_current_node)->isRed == true)
			{
				(*z)->parent->isRed = false;
				(*parent_current_node)->isRed = false;
				(*z)->parent->parent->isRed = true;
				(*z) = (*z)->parent->parent;
			}
			else if ( (*z) == (*z)->parent->right )
			{
				(*z) = (*z)->parent;
				rotate_left(&(*root) , &(*z) );
			}
			(*z)->parent->isRed == false;
			(*z)->parent->parent->isRed = true;
			rotate_right(&(*root),&( ((*z)->parent->parent) ) );
		}
		else
		{
			//double check this WIP
			(*parent_current_node) = (*z)->parent->parent->left;
			if((*parent_current_node)->isRed == true)
			{
				(*z)->parent->isRed = false;
				(*parent_current_node)->isRed = false;
				(*z)->parent->parent->isRed = true;
				(*z) = (*z)->parent->parent;
			}
			else if( (*z) == (*z)->parent->left )
			{
				(*z) = (*z)->parent;
				rotate_right(&(*root), &(*z));
			}
			(*z)->parent->isRed = false;
			(*z)->parent->parent->isRed = true;
			rotate_left(&(*root),&( ((*z)->parent->parent) ) );
		}
	}
	(*root)->isRed = false;
}

struct RBtree
{
	Node *root = new Node;
	//Constructor's parameter is the value for the root node's value =
	RBtree(float root_value)
	{
		this->root->isRed = false;
		this->root->value = root_value;
	}

	void insertion(float input_value)
	{
		Node *new_node = new Node(input_value);

		//default the new node added naively will be red
		new_node->isRed= true;

		Node *current_node = root;

		Node *parent_current_node = nullptr;

		while(current_node != nullptr)
		{
			//if smaller or equal goes left
			parent_current_node = current_node;

			if(current_node != nullptr && new_node->value <= current_node->value)
			{
				current_node = current_node->left;
			}
			
			if(current_node != nullptr && new_node->value > current_node->value)
			{
				current_node = current_node->right;
			}
		}

		if(new_node->value <= parent_current_node->value)
		{
			new_node->parent = parent_current_node;
			parent_current_node->left = new_node;
		}

		if(new_node->value > parent_current_node->value)
		{
			new_node->parent = parent_current_node;
			parent_current_node->right = new_node;
		}

	RB_insert_fixup( &(this->root), &new_node, &parent_current_node);
	}

};

int main()
{
	RBtree A1(7.0);

	A1.insertion(8);
	A1.insertion(6);
}