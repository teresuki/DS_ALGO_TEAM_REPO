#include <iostream>
#include <vector>

using namespace std;

//W is the maxium weight of the knapsack
//i is the number of first n coin in v used.
//W is the weight of each type of coins
//v is the value of each type of coins
int recursive_knapsack(int W, int i ,int w[], int v[])
{
	//base case initialize to 0
	if( i==0 ) //if we use none first coin or our knapsack cant hold anything then the value must be 0
		return (W < w[0] ? 0:v[0]);

	if(w[i-1] > W) //we use i-1 instead of i is because the index of a C++ array start with 0 so the first coin is at index 0
		return recursive_knapsack(W,i-1,w,v);
	else
		return max(recursive_knapsack(W,i-1,w,v), (v[i-1] +recursive_knapsack(W-w[i-1] ,i-1,w,v) ) );
}

int dynamic_knapsack(int W, int i, int w[], int v[])
{
	int K[i][W+1];
	for(int run =0; run < i; run++) K[run][0] = 0;
	for(int j=0; j <= W; j ++) 
	{
		if(w[0] <=j) K[0][j] = v[0];
		else K[0][j] = 0;
	}
	for(int run = 1; run < i; run ++)
	{
		for(int j=1; j <= W; j++)
		{
			if(j >= w[run] && K[run-1][j-w[run]] +v[run] > K[run-1][j])
			K[run][j] = K[run-1][j-w[run]] + v[run];
			else K[run][j] = K[run-1][j];
		}
	}
	return K[i-1][W];
}

int finding_knapsack(int W, int i, int w[], int v[])
{
	int Ka[i][W+1];
	for (int row = 0;row  < i; row ++)
	{
		for(int col =0;  col < W+1; col++)
		{
			Ka[row][col] = -1;
		}
	}
	return Ka[i-1][W];
}


int main()
{


	int i = 6;
	int W = 10;
	int w[] = {6,5,4,2,2};
	int v[] = {6,3,5,4,6};

	cout<< recursive_knapsack(W,i,w,v)<<'\n';
	cout<< dynamic_knapsack(W,i,w,v)<<'\n';
	cout<< finding_knapsack(10,6,w,v)<<'\n';

	return 0;
}	