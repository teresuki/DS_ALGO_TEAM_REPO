#include <iostream>
#include <vector>
#include <map>

using namespace std;

// int cmpfunc (const pair<int.char> * a, const void * b) {
//    return ( (pair<int,char>*)a->first - *(int*)b );
// }
int comp(const pair<int,char>  a , const pair <int,char> b)
{
	return (    a->first - b->first     );
}

int main()
{
	vector<pair <int, char > > the_list;

	the_list.push_back({1,'a'});
	the_list.push_back({2,'b'});
	the_list.push_back({3,'c'});

}