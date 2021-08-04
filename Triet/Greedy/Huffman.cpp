#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Node
{
	int frequency=0;
	char character='\0';
	Node *left = nullptr;
	Node *right = nullptr;
};

class Document
{
	private:
	map<char,int> frequency_of_char;
	Node *root = nullptr;

	public:
	void insert_plain_text()
	{
		string usr_input;
		cout<<"Enter the input text: ";
		cin >> usr_input;


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
		//transfer the frequenc tree to vector
		vector<pair <int,char> > the_list;
		for(auto itr = frequency_of_char.begin(); itr != frequency_of_char.end(); itr++)
		{
			the_list.push_back({itr->second,itr->first});
		}
		

		for(int i =0; i < the_list.size(); i++)
		{
			cout<<the_list[i].first <<'\t' << the_list[i].second <<'\n';
		}

	}

};

int main()
{
	Document D1;

	D1.insert_plain_text();
	D1.build_frequency_tree();	

}