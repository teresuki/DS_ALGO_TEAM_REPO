#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#define COUNT 10
struct Node
{
	int frequency=0;
	char character='\0';
	Node *left = nullptr;
	Node *right = nullptr;
	Node(){}
	Node(char character, int frequency) 
	{
		this->character = character;
		this->frequency = frequency;
	}
	Node(char character,int frequency, Node *left, Node *right)
	{
		this->character = character;
		this->frequency = frequency;
		this->left = left;
		this->right = right;
	}
};

bool compare_node_freqency(const Node &a,const Node &b)
{
	return ( a.frequency >  b.frequency );
}

class Document
{
	private:
	string usr_input;
	map<char,int> frequency_of_char;
	map<char,string> char_huff;
	vector<Node> the_list;
	Node *root = nullptr;

// Function to print binary tree in 2D
// It does reverse inorder traversal
	void print2DUtil(Node *root, int space)
	{
		// Base case
		if (root == NULL)
			return;
	
		// Increase distance between levels
		space += COUNT;
	
		// Process right child first
		print2DUtil(root->right, space);
	
		// Print current node after space
		// count
		cout<<endl;
		for (int i = COUNT; i < space; i++)
			cout<<" ";
		cout<<root->character<<":"<<root->frequency<<"\n";
	
		// Process left child
		print2DUtil(root->left, space);
	}
	
	// Wrapper over print2DUtil()
	void print2D(Node *root)
	{
		// Pass initial space count as 0
		print2DUtil(root, 0);
	}

	void insert_plain_text()
	{	
		cout<<"Enter the input text: ";
		cin >> this->usr_input;


		for(int c=0; c < usr_input.size(); c++)
		{
			if( this->frequency_of_char.find(usr_input[c]) == frequency_of_char.end())
			{
				frequency_of_char.insert(pair<char,int>(usr_input[c],1));
			}
			else
			{
				auto existed_char = frequency_of_char.find(usr_input[c]);
				existed_char->second++;
			}
		}

	}

	void build_frequency_tree()
	{
		for(auto itr = frequency_of_char.begin(); itr != frequency_of_char.end(); itr++)
		{
			the_list.push_back(Node(itr->first,itr->second));
		}

		sort(the_list.begin(),the_list.end(),compare_node_freqency);
		
		// for(int i =0; i < the_list.size(); i++)
		// {
		// 	cout<<the_list[i].character<<'\t' << the_list[i].frequency <<'\n';
		// }		

		while(the_list.size() >1 )
		{
			Node *z = new Node();

			Node last = the_list.back();
			Node *x = new Node(last.character,last.frequency,last.left,last.right);
			the_list.pop_back();

			Node penultimate = the_list.back();
			Node *y = new Node(penultimate.character,penultimate.frequency,penultimate.left,penultimate.right);
			the_list.pop_back();

			z->left = x;
			z->right = y;

			z->frequency = x->frequency + y->frequency;

			the_list.push_back(*z);

			sort(the_list.begin(),the_list.end(),compare_node_freqency);
		}
		this->root = &the_list[0];
		print2D(this->root);
	}

	void tree_traversal(Node *current_node, string huff_code)
	{
		if(current_node->character != '\0')
		{
			this->char_huff.insert(pair<char,string>(current_node->character,huff_code));
			huff_code.clear();
		}
		else
		{
			if(current_node->left != nullptr) tree_traversal(current_node->left,huff_code+='0');
			huff_code.pop_back();
			if(current_node->right != nullptr) tree_traversal(current_node->right,huff_code+='1');
		}
	}

	void map_char_huff_code()
	{
		string huff_code;
		if(this->root != nullptr) tree_traversal(this->root,huff_code);
		else cout<<"No tree to encode huffman code yet"<<'\n';

		for(auto itr = this->char_huff.begin(); itr != this->char_huff.end(); itr++ )
		{
			cout<<itr->first<<'\t'<<itr->second<<'\n';
		}
	}
	void translate_to_huffman()
	{
		cout <<"The Huffman coding of the string is: ";
		for(int i=0; i < usr_input.size(); i++)
		{
			map<char,string>::iterator output_huff = char_huff.find(usr_input[i]);
			cout<<output_huff->second;
		}
		putchar('\n');
	}

	public:
	void text_to_huffman()
	{
		insert_plain_text();
		build_frequency_tree();
		map_char_huff_code();
		translate_to_huffman();
	}

	void huffman_to_text()
	{

		string huff_text;
		cout<<"this function only works if you encode the text and decode with the same Document object"<<'\n';
		cout<<"Copy the output bit string above"<<'\n';
		cout<<"Enter the bit string you want to decode:";
		cin >> huff_text;
		Node *current_node = this->root;
		
		while(huff_text.size() >	0 )
		{
			if(current_node->character == '\0')
			{
			if(huff_text[0] == '0') {current_node = current_node->left;}
			if(huff_text[0] == '1') {current_node = current_node->right;}

				if(current_node->character != '\0' )
				{
					cout<<current_node->character;
					current_node = this->root;
				}
			
			}
			else
			{
				cout<<current_node->character;
				current_node = this->root;
			}
			huff_text.erase(0,1);
		}
		putchar('\n');
	}

};

int main()
{
	Document D1;

	// D1.insert_plain_text();
	// D1.build_frequency_tree();	
	// D1.map_char_huff_code();
	// D1.translate_to_huffman();
	D1.text_to_huffman();
	D1.huffman_to_text();
}