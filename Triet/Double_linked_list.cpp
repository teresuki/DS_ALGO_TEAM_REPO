//17447
// in this coding demonstration every node is on heap
#include <iostream>

using namespace std;

struct Node
{
	Node *next;
	Node *previous;
	float value;
	Node(float value): value(value) {}
};

void Linker()
{
	
}

int main()
{
	Node *N1 = new Node(1);
	Node *N2 = new Node(2);

	Node array[] = {*N1,*N2};

	return 0;
}