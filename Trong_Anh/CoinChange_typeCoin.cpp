#include <iostream>

using namespace std;

void coin_change(int n, int N)
{
    int d[] = {1, 10, 25, 100};
    int t[n][N+1];
    //Create 3D array of coin type that needs to be change
    int coinType[n][N+1][n];

    /* Base case: No money */
    for(int i = 0; i < n; ++i)
    {
        t[i][0] = 0;
        for(int k = 0; k < n; ++k)
        coinType[i][0][k] = 0;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            //In case we have only penny
            if(i == 0)
            {
                t[i][j] = t[i][j-d[i]] + 1;
                coinType[i][j][0] = j;
                for(int k = 1; k < n; ++k) coinType[i][j][k] = 0;
            }
            //In case the value have to pay smaller than the value of the coin we have
            else if(j < d[i])
            {
                t[i][j] = t[i-1][j];
                for(int k = 0; k < n; ++k)
                 coinType[i][j][k] = coinType[i-1][j][k];
            }
            //In other case
            else
            {
                //Not using "min" function to demonstrate the cointype loop easier
                if(t[i-1][j] < t[i][j-d[i]] + 1)
                {
                    t[i][j] = t[i-1][j];
                    for(int k = 0; k < n; ++k)
                        coinType[i][j][k] = coinType[i-1][j][k];
                }
                else
                {
                    t[i][j] = t[i][j-d[i]] + 1;
                    for(int k = 0; k < n; ++k)
                        coinType[i][j][k] = coinType[i][j-d[i]][k];
                        coinType[i][j][i]++;
                }
            }
        }
    }

    cout << "Only need " << t[n-1][N] << " coin (s) to pay. Including: " << endl;
    cout << coinType[n-1][N][3] << " dollar(s)." << endl;
    cout << coinType[n-1][N][2] << " quater(s)." << endl;
    cout << coinType[n-1][N][1] << " dime(s)." << endl;
    cout << coinType[n-1][N][0] << " penny(ies)." << endl;

}

int main()
{
    int n, N;

    cout << "Enter 1 if you only have dollars."<< endl;
    cout << "Enter 2 if you have dollars and quaters."<< endl;
    cout << "Enter 3 if you have dollars, quaters and dimes."<< endl;
    cout << "Enter 4 if you have all types of coin." << endl;
    cout << "Your number: ";   cin >> n;


    cout << "The value you need to pay: "; cin >> N;

    coin_change(n,N);
    return 0;
}
