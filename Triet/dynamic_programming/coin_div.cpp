#include <iostream>
#include <vector>

using namespace std;

int coin_exchange( int n, int N, vector<int> d)
{

	int t[n][N+1]; // N+1 because there is the extra 0 money to be exchanged column
	//initialize the base case all with 0
	for (int i=0; i < n; i++) { t[i][0] = 0; }
		for(int i =0; i < n; i ++)
		{
			for(int j =1; j <= N; j ++)
			{
				if(i==0) t[i][j] = t[i][j-d[i]] +1;
				else if (j < d[i]) t[i][j] = t[i-1][j];
				else t[i][j] = min(t[i-1][j], t[i][j-d[i]]+1);
			}
		}
	return t[n-1][N];
}

int main()
{
	vector<int>d = {1,4,6};
	cout << coin_exchange(3,12,d) <<'\n';
}