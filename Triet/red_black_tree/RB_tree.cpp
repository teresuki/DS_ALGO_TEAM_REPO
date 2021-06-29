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

	// for some weird reason when transferring the address of (*x)->parent to y->parrent the whole Node **x got erase, no pointer value and not even NAN
	//for value, hence I have created a dummy x_copy so that it still retain the information in x, after x is deleted 
	Node *x_copy = *x;
	x_copy = *x; // passing the value of x into x_copy via default copy constructor
	y->parent = (*x)->parent;

	if( (x_copy)->parent == nullptr) *root = y;
	else if(x_copy == (x_copy)->parent->left ) (x_copy)->parent->left = y;
	else (x_copy)->parent->right = y;

	y->left = x_copy;
	(x_copy)->parent = y;
}

void rotate_right(Node **root, Node **x)
{
	Node *y = (*x)->left;
	(*x)->left = y->right;
	if(y->right !=  nullptr) y->right->parent = *x;
	Node *x_copy = new Node;
	x_copy = *x;
	y->parent = ((*x)->parent);

	if( (x_copy)->parent == nullptr ) *root = y;
	else if( x_copy == (x_copy)->parent->right ) (x_copy)->parent->right =y;
	else (x_copy)->parent->left = y;

	y->right = x_copy;
	(x_copy)->parent = y;
}

// z is the new_node
// y is the parent_current_node
void RB_insert_fixup(Node **z, Node **root, Node **parent_current_node)
{
	while( (*z)->parent != nullptr  && (*z)->parent->isRed == true )
	{
		if( (*z)->parent->parent != nullptr && (*z)->parent == (*z)->parent->parent->left)
		{
			(*parent_current_node) = (*z)->parent->parent->right;
			if( (*parent_current_node) != nullptr && (*parent_current_node)->isRed == true )
			{
				(*z)->parent->isRed = false;  //case 1
				(*parent_current_node)->isRed = false; //case 1
				(*z)->parent->parent->isRed = true; //case 1
				(*z) = (*z)->parent->parent; //case 1
			}
			else if ( (*parent_current_node) == nullptr && (*z) == (*z)->parent->right )
			{
				(*z) = (*z)->parent;  //case 2
				rotate_left(&(*root) , &(*z) ); //case 2
			}
			(*z)->parent->isRed == false; //case 3
			(*z)->parent->parent->isRed = true; //case 3
			rotate_right(&(*root),&( ((*z)->parent->parent) ) ); //case 3
		}
		else if ( (*z)->parent->parent != nullptr && (*z)->parent == (*z)->parent->parent->right )
		{
			(*parent_current_node) = (*z)->parent->parent->left;
			if( (*parent_current_node) !=nullptr  && (*parent_current_node)->isRed == true)
			{
				(*z)->parent->isRed = false;
				(*parent_current_node)->isRed = false;
				(*z)->parent->parent->isRed = true;
				(*z) = (*z)->parent->parent;
			}
			else if( (*parent_current_node) == nullptr && (*z) == (*z)->parent->left )
			{
				(*z) = (*z)->parent;
				rotate_right(&(*root), &(*z));
			}
			(*z)->parent->isRed = false;
			(*z)->parent->parent->isRed = true;
			rotate_left(&(*root),&( ((*z)->parent->parent) ) );
		}
		if ((*z)->parent->parent == nullptr ) break;
	}
	(*root)->isRed = false;
}

struct RBtree
{
	Node *root = nullptr;
	//Constructor's parameter is the value for the root node's value =

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

			if(new_node->value <= current_node->value)
			{
				current_node = current_node->left;
			}
			
			else if(new_node->value > current_node->value)
			{
				current_node = current_node->right;
			}
		}

		new_node->parent = parent_current_node;
		if(parent_current_node == nullptr) this->root = new_node;
		else if(new_node->value <= parent_current_node->value)
		{
			parent_current_node->left = new_node;
		}
		else if(new_node->value > parent_current_node->value)
		{
			parent_current_node->right = new_node;
		}

	RB_insert_fixup(&new_node,&(this->root),&parent_current_node);
	}

};

int main()
{
	RBtree A1;

	A1.insertion(8);
	A1.insertion(6);
	A1.insertion(3);


}