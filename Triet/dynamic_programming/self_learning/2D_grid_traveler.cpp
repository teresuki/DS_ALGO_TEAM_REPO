//Say that you are a travller on a 2D grid. You begin in the
//top-left corner and your goal is to move to the bottom right
//corner of the grid. You can only move down or right.
//How many ways you can travel to the goal on a m*n grid
#include <iostream>

using namespace std;

int cal_possible_way(int m, int n)
{
	if(m == 1 && n == 1) return 1;
	if(m ==0 || n==0) return 0;
	else return cal_possible_way(m-1,n) + cal_possible_way(m,n-1);
}

int mem_cal_possible_way(int m,int n)
{

}

int main()
{
	cout<<cal_possible_way(2,3)<<'\n';
}