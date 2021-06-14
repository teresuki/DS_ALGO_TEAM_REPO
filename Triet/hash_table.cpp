#include <iostream>
#include <cmath>
#include "dlink_list.hpp"
#include <string.h>

#define SIZE 3
#define SIZE_linear 4


using namespace std;

// A unit is each element that we need to put into the hash table
struct Unit
{
	string key;
	float value;
	Unit(string key,float value): key(key), value(value) {}
};	

// return us the index of the hash table
int hash_function(string key)
{
	//first we need to turn the string into ASCII value
	int key_ASCII = 0;

	for(int i =0; i < key.size() ; i++)
	{
		key_ASCII += static_cast<int>(key[i]);
	}
	key_ASCII = key_ASCII % SIZE;
	// cout << key_ASCII <<'\n';
	return key_ASCII;
}

// add hash using linked list to avoid collision
void add_hash_table(Unit input, Node *hash_table[SIZE])
{
	// get the index
	int index = hash_function(input.key);

	
	insert_after(&hash_table[index], input.value);
}


//Search for the node with the specific key and value
Node *search_linked_list(Unit wanted,Node *hash_table[SIZE])
{
	int wanted_index = hash_function(wanted.key);

	return search_node(&hash_table[wanted_index],wanted.value);
}

void delete_linked_list(Unit wanted,Node *hash_table[SIZE])
{
	int wanted_index = hash_function(wanted.key);

	delete_node(&hash_table[wanted_index], wanted.value);
}

void print_hash_table(Node *hash_table[])
{
	for(int i=0; i < SIZE; i ++)
	{
		cout<< i <<":  ";
		display_dlink(hash_table[i]);
	}
	// display_dlink(hash_table[1]);
}

//----------------------------------------------------------------------------------------------------
void add_hash_linear(Unit input, Node *hash_linear[SIZE_linear])
{
	int index = hash_function(input.key);
	static int times_probed =0;
	if(hash_linear[index] == nullptr)
	{
		insert_after(&hash_linear[index],input.value);
	}
	else 
	{
		while(hash_linear[index] != nullptr)
		{
			index++;
			times_probed++;
			if (index >= SIZE_linear) index = index % SIZE_linear;

			if(hash_linear[index] == nullptr) 
			{
				insert_after(&hash_linear[index],input.value);
				return;
			}

			if(times_probed >= SIZE_linear)
			{
				std::cout <<"Not enough memory space for this value, can't add"<<'\n';
				return;
			}
		}
	}
}

Node *search_hash_linear(Unit wanted,Node *hash_linear[SIZE_linear])
{
	int wanted_index = hash_function(wanted.key);
	int times_probed =0;

	Node *result;

	if(hash_linear[wanted_index] != nullptr && search_node(&hash_linear[wanted_index],wanted.value) != nullptr)
	{
		result = hash_linear[wanted_index];
	}
	else
	{
		while (hash_linear[wanted_index] == nullptr || search_node(&hash_linear[wanted_index],wanted.value) == nullptr)
		{
			wanted_index++;
			times_probed++;

			if (wanted_index >= SIZE_linear) wanted_index = wanted_index % SIZE_linear;


			if(hash_linear[wanted_index] != nullptr && search_node(&hash_linear[wanted_index],wanted.value) != nullptr)
			{
				result = hash_linear[wanted_index];
				break;
			}

			if(times_probed >= SIZE_linear)
			{
				std::cout<<"NO such nodes exist from search" <<'\n';
				result = nullptr;
				break;
			}
		} 
	}

	return result;
}

void delete_hash_linear(Unit wanted, Node *hash_linear[SIZE_linear])
{
	int wanted_index = hash_function(wanted.key);

	int times_probed =0;

	if(hash_linear[wanted_index] != nullptr && search_node(&hash_linear[wanted_index],wanted.value) != nullptr)
	{
		delete_node(&hash_linear[wanted_index],wanted.value);
	}
	else
	{
		while(hash_linear[wanted_index] == nullptr ||  search_node(&hash_linear[wanted_index],wanted.value) == nullptr)
		{
			wanted_index++;
			times_probed++;

			if (wanted_index >= SIZE_linear) wanted_index = wanted_index % SIZE_linear;

			if(hash_linear[wanted_index] != nullptr && search_node(&hash_linear[wanted_index],wanted.value) != nullptr)
			{
				delete_node(&hash_linear[wanted_index],wanted.value);
				break;
			}
			if(times_probed >= SIZE_linear)
			{
				std::cout<<"NO such nodes exist from delete" <<'\n';
				break;
			}


		}
	}
}


void print_hash_linear(Node *hash_table[])
{
	for(int i=0; i < SIZE_linear; i ++)
	{
		std::cout<< i <<":  ";
		display_dlink(hash_table[i]);
	}
	// display_dlink(hash_table[1]);
}
	
int main()
{
	// create an array full of pointers to Node which will be out hash table
	// array<Node *,SIZE> hash_table;
	Node *hash_table[SIZE];

	// fill each elements in our hash table with nullptr
	for(int i =0; i < SIZE; i++)
	{
		Node *head = nullptr;
		hash_table[i] = head;
	}

	Unit U1("abcd",1);
	Unit U2("bbcd",2);
	Unit U3("cbcd",3);
	Unit U4("dbcd",4);

	add_hash_table(U1,hash_table);
	add_hash_table(U2,hash_table);
	add_hash_table(U3,hash_table);
	add_hash_table(U4,hash_table);

	print_hash_table(hash_table);

	std::cout<<"----------------------------------------------------------------------------------------------------"<<'\n';

	delete_linked_list(U1,hash_table);
	
	print_hash_table(hash_table);

	// finding the location of the node containing U3 and printing U3's value (which is 3)
	Node *pU3 = search_linked_list(U3,hash_table);
	std::cout <<"Printing the value of U3: " <<pU3->value <<'\n';

//----------------------------------------------------------------------------------------------------
// hash table using linear probing
	std::cout<<"----------------------------------------------------------------------------------------------------"<<'\n';

	Node *Hash_linear[SIZE_linear];

	for(int i =0; i < SIZE_linear; i++)
	{
		Node *head = nullptr;
		Hash_linear[i] = head;
	}
	Unit U5("efcg",5);

	 add_hash_linear(U1,Hash_linear);
	 add_hash_linear(U2,Hash_linear);
	 add_hash_linear(U3,Hash_linear);
	 add_hash_linear(U4,Hash_linear);
	 add_hash_linear(U5,Hash_linear);

	print_hash_linear(Hash_linear);

	std::cout<<"----------------------------------------------------------------------------------------------------"<<'\n';

	delete_hash_linear(U4,Hash_linear);

	print_hash_linear(Hash_linear);

	Node *find = search_hash_linear(U4,Hash_linear);
	if (find != nullptr)  std::cout << find->value <<'\n';

	std::putchar('\n');
	return 0;
}