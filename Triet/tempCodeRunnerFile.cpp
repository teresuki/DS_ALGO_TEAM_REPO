#include <iostream>

int main()
{
	int x = 10;
	int *px = &x;

	int **ppx = &px;

	int *ppx_node = *ppx;

	std::cout << *ppx_node <<'\n';
}