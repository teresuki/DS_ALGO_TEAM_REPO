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
	void print_function(std::shared_ptr<Node> root, std::string indent,bool print_right)
	{
		if(root != nullptr)
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
			if((root)->is_red == true) color = "RED";
			else color = "BLACK";
			std::cout << (root)->value <<"("<< color << ")"<<'\n';
			print_function( ((root)->left)  ,indent,false);
			print_function( ((root)->right) ,indent,true);
		}
	}

	void rotate_left( std::shared_ptr<Node> x)
	{
		std::shared_ptr<Node> y = x->right;
		x->right = y->left;
		if(y->left != nullptr) y->left->parent = x;
		y->parent = x->parent;
		if(x->parent == nullptr) this->root = y;
		else if( x ==  y->parent->left) x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotate_right(std::shared_ptr<Node> y)
	{
		std::shared_ptr<Node> x = y->left;
		y->left = x->right;
		if (x->right != nullptr) x->right->parent = y;
		x->parent = y->parent;
		if(y->parent == nullptr) this->root = x;
		else if (y == y->parent->right) y->parent->right = x;
		else y->parent->left = x;
		x->right = y;
		y->parent = x;
	}

	void fix_insert(std::shared_ptr<Node> node)
	{
		std::shared_ptr<Node> uncle_node;
		while(node->parent != nullptr  && node->parent->is_red == true)
		{
			if(node->parent ==  node->parent->parent->left)
			{
				uncle_node = node->parent->parent->right;
				//case 1
				if(uncle_node->is_red == true)
				{
					node->parent->is_red = false;
					uncle_node->is_red = false;
					node->parent->parent->is_red = true;
					node = node->parent->parent;
				}

				//case 2
				else
				{
					if(node == node->parent->right)
					{
						node = node->parent;
						rotate_left(node);
					}
					//case 3 
					node->parent->is_red = false;
					node->parent->parent->is_red = true;
					rotate_right(node->parent->parent);
				}
			}
			else // if the parent node is a subtree on the right
			{
				uncle_node = node->parent->parent->left;
				//case 4
				if(uncle_node->is_red == true)
				{
					node->parent->is_red = false;
					uncle_node->is_red = false;
					node->parent->parent->is_red = true;
					node = node->parent->parent;
				}
				//case 5
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotate_right(node);
					}
				//case 6
					node->parent->is_red = false;
					node->parent->parent->is_red = true;
					rotate_left(node->parent->parent);
				}
			}
			if (node == this->root) break;
		}
		this->root->is_red = false;
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

		fix_insert(new_node);
	}

		void print_tree()
	{
		if(this->root != nullptr)
		{
			print_function( this->root ,"",true);
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

	// A1.insertion_node(3);

	A1.insertion_node(11);
    A1.insertion_node(2);
    A1.insertion_node(14);
    A1.insertion_node(1);
    A1.insertion_node(7);
    A1.insertion_node(5);
    A1.insertion_node(8);

    A1.insertion_node(12);
    A1.insertion_node(10);
	A1.print_tree();
	return 0;
}

