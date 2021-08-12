// Need to test

#include <iostream>
#include <algorithm>
using namespace std;

int d[4] = {1, 10, 25, 100};
int make_change(int i, int j)
{
    if(i == 0 && j == 0)
        return 0;

    if(i == 0)
        return make_change(i, j - d[i]) + 1;

    if(j == 0)
        return 0 ;

    if(j < d[i])
        return make_change(i - 1, j);

    return min(make_change(i - 1, j), make_change(i, j - d[i]) + 1) ;
}

int main(void)
{
    int result = make_change(3, 23);

    cout << result;

    return 0;
}
