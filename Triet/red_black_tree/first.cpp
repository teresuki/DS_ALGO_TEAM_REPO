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

		Node *current_node;
		current_node = root;

		Node *parent_current_node;

		while(current_node != nullptr)
		{
			//if smaller or equal goes left
			if(current_node != nullptr && new_node->value <= current_node->value)
			{
				parent_current_node = current_node;
				current_node = current_node->left;
			}
			
			if(current_node != nullptr && new_node->value > current_node->value)
			{
				parent_current_node = current_node;
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


		
	}

};

int main()
{
	RBtree A1(7.0);

	A1.insertion(8);
	A1.insertion(6);
}