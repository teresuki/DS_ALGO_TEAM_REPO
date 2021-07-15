#include <iostream>

using namespace std;

int dynamic_fib(int n)
{
	int f[n+1];
	for(int i =0; i <= n; i++)
	{
		if(i <= 1) f[i] = i;
		else f[i] = f[i-1] + f[i-2];
	}
	return f[n];
}

int main()
{
	cout << dynamic_fib(30) <<'\n';
	
}