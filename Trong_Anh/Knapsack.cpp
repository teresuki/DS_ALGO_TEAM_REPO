#include <iostream>

using namespace std;

//W: sack's maximum capacity
//N: number of items
void Knapsack(int W)
{
    //weights of items
   int w[] = {3, 2, 6, 1, 7, 4};
    //value of items
   int v[] = {7, 10, 2, 3, 2, 6};
   int n = sizeof (v)/sizeof (v[0]);
   //create a 2D array
   int K[n][W+1];

   //base case: no item
   for(int i = 0; i < n; ++i)
       K[i][0] = 0;

    //other cases
   for(int j = 1; j <= W; ++j)
   {
       if(j < w[0])
            K[0][j] = 0;
       else
            K[0][j] = v[0];
   }

   for(int i = 1; i < n; ++i)
   {
       for(int j = 1; j <= W; ++j)
       {
         if(j >= w[i] && K[i-1][j-w[i]] + v[i] > K[i-1][j])
         {
             K[i][j] = K[i-1][j-w[i]] + v[i];
         }
         else
            K[i][j] = K[i-1][j];
       }
   }
   cout << "The maximum value you can get is " << K[n-1][W] <<"."<< endl;
}

int main()
{
    int W;
    cout << "You've entered informations about your items. Please enter your sack's capacity: ";
    cin >> W;
    Knapsack(W);
}
