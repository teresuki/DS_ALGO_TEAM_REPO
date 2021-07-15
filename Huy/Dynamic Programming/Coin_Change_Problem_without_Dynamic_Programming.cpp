// Ex_2 -- The 2nd solution without using dynamic programming
/* Coding with Rush and a lot of Technical Debts and Flaws */
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
using namespace std;

int main(void)
{
    int n = 3, N = 8;
    int d[n] = {6, 4, 1};

    int min_amount_of_coin = 99999999;
    for(int i = 0; i < n; i++)
    {
        int coin_count = 0;

        int j = i;
        int M = N;
        while(M != 0)   // assume min denominator = 1
        {
            coin_count += M / d[j];
            M %= d[j];
            j++;
        }
        if((coin_count != 0) && (coin_count < min_amount_of_coin))  // assume that N >
            min_amount_of_coin = coin_count;
    }

    cout << min_amount_of_coin << endl;

    return 0;
}
