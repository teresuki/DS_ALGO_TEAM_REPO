#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<char,int> test;

	test.insert(pair<char,int>('a',3));
	
	auto instant = test.find('b');

	instant->second++;

	cout << instant->first << '\t' <<instant->second <<'\n';

}