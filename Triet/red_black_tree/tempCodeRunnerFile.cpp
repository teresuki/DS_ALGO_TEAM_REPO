#include <iostream>
#include <memory>

using namespace std;

struct Node {};

int main()
{
	// Node A = new Node;

	shared_ptr<Node> A(new Node);

	cout << &A << '\n';
	cout << A << '\n';

	Node *B = new Node;
}