#include <iostream>
#include <memory>
#include <cmath>

struct Node
{
	bool is_red;
	float value = NAN;
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;
	std::shared_ptr<Node> parent = nullptr;
	Node(float value): value(value) {}
};

class RBtree
{
	private:

	std::shared_ptr<Node> root = nullptr;
	void print_function(Node **root, std::string indent,bool print_right)
	{
		if(*root != nullptr)
		{
			std::cout << indent;
			if(print_right)
			{
				std::cout<<"R---"; //left side of the tree
				indent += "\t";
			}
			else
			{
				std::cout <<"L---";
				indent += "\t";
			}
			std::string color;
			if((*root)->isRed == true) color = "RED";
			else color = "BLACK";
			std::cout << (*root)->value <<"("<< color << ")"<<'\n';
			print_function( &((*root)->left)  ,indent,false);
			print_function( &((*root)->right) ,indent,true);
		}
	}

	public:
	void insertion_node(float input_value)
	{
		std::shared_ptr<Node> new_node (new Node(input_value));
		
		new_node->is_red = true;

		std::shared_ptr<Node> current_node = this->root;

		std::shared_ptr<Node> parent_current_node = nullptr;

		while(current_node != nullptr )
		{
			parent_current_node = current_node;

			if(new_node->value <= current_node->value ) current_node = current_node->left;
			else if(new_node->value >current_node->value) current_node = current_node->right;
		}

		new_node->parent = parent_current_node;

		if(parent_current_node == nullptr) this->root = new_node;

		else if(new_node->value <= parent_current_node->value) parent_current_node->left = new_node;
		else if(new_node->value > parent_current_node->value ) parent_current_node->right = new_node;

	}

		void print_tree()
	{
		if(this->root != nullptr)
		{
			print_function( &(this->root) ,"",true);
		}
		else
		{
			std::cout<<"This tree doesn't have any nodes yet"<<'\n';
		}
	}
};

int main()
{
	RBtree A1;

	A1.insertion_node(3);

	return 0;
}

