#include <iostream>
#include <array>
#include "dlink_list.hpp"
#include <string.h>

#define SIZE 3


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

void print_hash_table(Node *hash_table[SIZE])
{
	for(int i=0; i < SIZE; i ++)
	{
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


	return 0;
}