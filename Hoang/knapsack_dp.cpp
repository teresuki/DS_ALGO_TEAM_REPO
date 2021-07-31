#include <iostream>
using namespace std;

#define W 10 // Maximum capacity of Knapsack
#define N 6 // Numbers of items

int Knapsack()
{
   int w[] = {3, 2, 6, 1, 7, 4}; // items' weights
   int v[] = {7, 10, 2, 3, 2, 6}; // items' values
   int K[N][W+1];
   for(int i = 0; i < N; ++i)
       K[i][0] = 0;
   for(int j = 1; j <= W; ++j)
   {
       if(j < w[0]) K[0][j] = 0;
       else         K[0][j] = v[0];
   }
   for(int i = 1; i < N; ++i)
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
   return K[N-1][W];
}

int main()
{
    cout << Knapsack() << endl;
}