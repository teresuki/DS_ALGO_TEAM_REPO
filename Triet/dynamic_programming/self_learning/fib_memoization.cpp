#include <iostream>

int fib(int n)
{
	if(n <= 2) return 1;
	return fib(n-1) + fib(n-2);
}

int mem_fib(int n)
{
	int mem[n];
	for(int i=0; i < n; i++)
	{
		if(i<=1) mem[i]=1;
		else mem[i] = mem[i-1] + mem[i-2];
	}
	return mem[n-1];
}

int main()
{
	std::cout<<fib(10)<<'\n';
	std::cout<<mem_fib(10)<<'\n';
	return 0;
}