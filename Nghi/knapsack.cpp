#include <string>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

//this problem is similar to the coin problem
//we can think of the coin problem as the knapsack problem
//but with weights and values stay constant (= 1)
//plus, coin wants to find min, knapsack wants to find max

void knapsack(vector<int> w, vector<int> v, int n, int W) {
	//create an array with n rows and W+1 columns
	int k[n][W+1];
	int k_count[n];
	for (int i = 0; i<n; i++) {
		k_count[i] = 0;
	}
	
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<=W; j++) {
			//if only consider the first item, 
			//if weight of current item > current W 
			if (i==0) {
				if (w[i]>j) {
					k[i][j] = 0;
				}
				else {
					k[i][j] = v[i];
				}
				continue;
			}
			//if weight of current item > current W
			//we don't take current item, hence profit = previous row
			else if (w[i]>j) {
				k[i][j] = k[i-1][j];
			}
			//otherwise
			else {
				//the left side of the max function is similar to coin problem,
				//but the right side is different: we can add one maximun per item,
				//so if we need to jump to the previous i right away
				k[i][j] = max(k[i-1][j], k[i-1][j-w[i]] + v[i]);
			}
		}
	}
	//count what type it is
	int x = n-1;
	int y = W;

	while(y>0&&x>=0) {
		if(k[x][y]==k[x-1][y]) {
			x=x-1;
		}
		if(k[x][y]==(k[x-1][y-w[x]] + v[x])) {
			k_count[x]++;
			y=y-w[x];
			//similar to the max function, here we
			//have to decrease x
			x--; 
		}
	}
	cout<<"We can have a profit of "<<k[n-1][W]<<"."<<endl;
	cout<<"Out of "<<n<<" items (1-"<<n<<"):"<<endl;
	for (int i = 0; i<n; i++) {
		if(k_count[i]>0) {
			cout<<"There is item "<<i+1<<"."<<endl;
		}
	}

}


int main() {
	int n,W;
	cout<<"How many items do you want?"<<endl;
	cin>>n;
	cout<<"What is the maximum weight?"<<endl;
	cin>>W;
	vector<int> v;
	vector<int> w;
	for(int i = 0; i<n; i++) {
		v.push_back((rand()%10) + 1);
	}
	for(int i = 0; i<n; i++) {
		w.push_back((rand()%10) + 1);
	}
	cout<<"Your item values: "<<endl;
	for(int i = 0; i<n; i++) {
		cout<<v[i]<<"\t";
	}
	cout<<endl;
	cout<<"Yout item weights: "<<endl;
	for(int i = 0; i<n; i++) {
		cout<<w[i]<<"\t";
	}
	cout<<endl;
	knapsack(w,v,n,W);
}

// int main() {
// 	vector<int> v = {1,6,10,16};
// 	vector<int> w = {1,2,3,5};
// 	knapsack(w,v,v.size(),7);
// }