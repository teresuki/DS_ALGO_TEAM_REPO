#include <string>
#include <array>
#include <iostream>

using namespace std;

void minCoin(int amount) {
	//d stores denominations
	//d_count stores #coins per denomination
	array<int, 4> d = {1,10,25,100};
	array<int, 4> d_count = {0,0,0,0};

	int t[4][amount+1];
	for (int i = 0; i<d.size(); i++) {
		t[i][0] = 0;
	}

	//calculating table values and find the min #coins
	for (int i = 0; i<d.size(); i++) {
		for (int j = 1; j<amount+1; j++) {
			if (i==0) {
				t[i][j] = t[i][j-1] + 1;
			}
			else if (d[i] > j) {
				t[i][j] = t[i-1][j];
			}
			else {
				t[i][j] = min(t[i][j-d[i]] + 1, t[i-1][j]);
			}
		}
	}
	//count each type of coin
	int x = d.size() - 1;
	int y = amount;
	while(y>0) {
		if(t[x][y]==t[x-1][y]) {
			x=x-1;
		}
		if(t[x][y]==(t[x][y-d[x]]+1)) {
			d_count[x]++;
			y=y-d[x];
		}
	}

	//print out results
	cout<<"We need a total of "<<t[d.size()-1][amount]<<" coins:"<<endl;
	cout<<"\t"<<d_count[0]<<" penny(s)."<<endl;
	cout<<"\t"<<d_count[1]<<" dime(s)."<<endl;
	cout<<"\t"<<d_count[2]<<" quarter(s)."<<endl;
	cout<<"\t"<<d_count[3]<<" dollar(s)."<<endl;
	
}


int main() {
	int change;
	cout<<"How much is the change?"<<endl;
	cin>>change;
	minCoin(change);
}