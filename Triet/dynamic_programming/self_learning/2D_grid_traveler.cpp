//Say that you are a travller on a 2D grid. You begin in the
//top-left corner and your goal is to move to the bottom right
//corner of the grid. You can only move down or right.
//How many ways you can travel to the goal on a m*n grid
#include <iostream>
#include <cmath>

using namespace std;

int cal_possible_way(int m, int n)
{
	if(m == 1 && n == 1) return 1;
	if(m ==0 || n==0) return 0;
	else return cal_possible_way(m-1,n) + cal_possible_way(m,n-1);
}


int mem_possible_way(int m,int n)
{
	//since this is C++ and not JS so we can not use the hash table to implement our code
	//we have to get a bit more creative
	int mem[m+1][n+1];  //added 1 because there is the case that the remaining square having dimension of 0s.

	for(int row=0; row <= m; row ++)
	{
		for(int col=0; col <= n; col++)
		{
			mem[row][col] = -1;
		}
	}

	for(int row=0; row <= m; row ++)
	{
		for(int col=0; col <= n; col++)
		{
			if((mem[row][col]) < 0 )
			{
				if(row == 1 && col ==1) {mem[row][col] = 1;}
				else if(row == 0 || col ==0) {mem[row][col] = 0;}
					else mem[row][col] = mem[row-1][col] + mem[row][col-1];
			}
		}
	}
	return mem[m][n];

}

int main()
{

	cout<<mem_possible_way(4,3)<<'\n';
	// cout<<cal_possible_way(18,18)<<'\n';
}