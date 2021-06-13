#pragma once

using namespace std;

struct Node
{
	float value;
	Node *next ;
	Node *previous ;
	Node(int value): value(value) {}
};

// Node **head needs to be a double pointer because it is pointing to Node *head on stack which is already a pointer
void insert_after(Node **head, float new_value)
{
	//allcating a memory of a new node on heap
	Node *new_node = new Node(new_value);

	//if there isn't any node added to head yet
	if( *head == nullptr)
	{
		(*head) = new_node;	
		new_node->previous = nullptr;
		new_node->next = nullptr;
		return;
	}

	//if there is already a node added to the chain
	if( *head != nullptr)
	{
			// cout <<"going IN" <<'\n';
		// we need to find the node that is the last node in the chain 
		Node *last = *head;
		while ( last->next != nullptr) // if the next node of the chain exist move to it
		{
			last = last->next;
		}

		last->next = new_node; // link the new node to the last node in the chain
		new_node->previous = last; // connect previous to the last node
		new_node->next = nullptr;
		return;
	}

}

// search for a node and return the address of the wanted node
Node *search_node(Node **head, float wanted_value)
{
	Node *current = *head;
	while( current->value != wanted_value && current->next != nullptr)
	{
		// cout <<"go in" <<'\n';
		current = current->next;
	}
	if (current->value == wanted_value) return current;
	else{
		cout <<"Node with that value doesn't exist" <<'\n';
		return nullptr;
	} 
}

void delete_node(Node **head, float wanted_value)
{
	Node *current = *head;
	Node *previous_node = nullptr;
	Node *next_node = nullptr;
	while( current->value != wanted_value && current->next != nullptr)
	{
		// cout <<"go in" <<'\n';
		current = current->next;
	}
	if (current->value != wanted_value)
	{
		cout <<"Node with that value doesn't exist" <<'\n';
		return;
	} 

	if( current->value == wanted_value)
	{
		//if the deleted node is in middle of the chain
		if(current->previous != nullptr && current->next != nullptr)
		{
			previous_node = current->previous;
			next_node = current->next;

			previous_node->next = next_node;
			next_node->previous = previous_node;

			delete current;
		}

		//if deleted node is at the start of the chain
		if(current->previous == nullptr && current->next != nullptr)
		{
			next_node = current->next;

			*head = next_node;
			next_node->previous = nullptr;

			delete current;
		}

		//if deleted node is at the end of the chain
		if(current->previous != nullptr && current->next == nullptr)
		{
			previous_node = current->previous;

			previous_node->next = nullptr;

			delete current;
		}

		//if deleted node is the only node in the chain
		if( current->previous == nullptr && current->next == nullptr)
		{
			*head = nullptr;
			delete current;
		}
	}
}

// display the linked list begin to end
void display_dlink(Node *current)
{
	while(current != nullptr)
	{
		cout << current->value <<"---";
		current = current->next; // here we are changing the address of current's memory to the address value stored in (*current).next 
	}
	if( current == nullptr) cout <<"null";
	putchar('\n');
}