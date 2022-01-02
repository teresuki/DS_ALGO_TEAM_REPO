#include <iostream>
#include <memory>
#include <cmath>

struct Node
{
	float value = NAN;
	Node *left = nullptr;
	Node *right = nullptr;
	Node *parent = nullptr;

	Node(float value): value(value) {}

};

class Btree
{
	private:
	Node *root = nullptr;

	void print_function(Node **current_root ,std::string indent,bool print_right)
	{
		if( *current_root != nullptr)
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
			std::cout << (*current_root)->value <<'\n';
			print_function( &(*current_root)->left,indent,false);
			print_function( &(*current_root)->right ,indent,true);
		}
	}

	Node *tree_minimum_node(Node **subtree_root)
	{
		Node *minimum_node = *subtree_root;

		while(minimum_node->left != nullptr) minimum_node = minimum_node->left;

		return minimum_node;
	}


	void transplant_tree(Node **replaced_tree, Node **transplanter_tree)
	{
		// The deleted entire subtree functions is to deleted the replaced tree in order to prevent memory leak

		if((*replaced_tree)->parent == nullptr) 
		{
			this->root = *transplanter_tree;
		}

		else if (*replaced_tree == (*replaced_tree)->parent->left )
		{
			(*replaced_tree)->parent->left = *transplanter_tree;	
		}
		else 
		{
			(*replaced_tree)->parent->right = *transplanter_tree;
		}

		if (*transplanter_tree != nullptr) (*transplanter_tree)->parent = (*replaced_tree)->parent;

	}

	public:
	void tree_insert(float value)
	{
		Node *new_node = new Node(value);

		if(this->root == nullptr) root = new_node;
		else 
		{
			Node *current_node = root;

			Node *parrent_current_node = nullptr;

			while(current_node !=  nullptr)
			{
				parrent_current_node = current_node;
				
				if(new_node->value <= current_node->value) current_node = current_node->left;

				else if (new_node->value > current_node->value) current_node = current_node->right;

			}
			new_node->parent = parrent_current_node;

			if(new_node->value <= parrent_current_node->value) parrent_current_node->left = new_node;

			else if (new_node->value > parrent_current_node->value) parrent_current_node->right = new_node;
		}
	}

	void tree_delete_node(Node *wanted_node)
	{
		if( wanted_node->left == nullptr ) transplant_tree(&wanted_node, &(wanted_node->right));
		
		else if(wanted_node->right == nullptr) transplant_tree(&wanted_node,&(wanted_node->left));
		else 
		{
			Node *new_root = tree_minimum_node(&(wanted_node->right));
			if(new_root->parent != wanted_node)
			{
				transplant_tree(&new_root,&(new_root->right));
				new_root->right = wanted_node->right;
				new_root->right->parent = new_root;
			}
			transplant_tree(&wanted_node,&new_root);
			new_root->left = wanted_node->left;
			new_root->left->parent = new_root;
		}
	}

	//if that node does not exist will return a nullpointer 
	Node *search_node(float value)
	{
		Node *current_node = this->root;

		while(current_node != nullptr && current_node->value != value)
		{
			if(value <= current_node->value) current_node = current_node->left;
			
			else if(value > current_node->value) current_node = current_node->right;
		}

		return current_node;
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
	Btree A1;
	A1.tree_insert(7);
	A1.tree_insert(3);
	A1.tree_insert(8);
	A1.tree_insert(11);
	A1.tree_insert(1);
	// djaksldjakljdaksjdkasj

	A1.print_tree();
	Node *to_be_deleted = A1.search_node(8);

	A1.tree_delete_node(to_be_deleted);
	A1.print_tree();
	return 0;
}