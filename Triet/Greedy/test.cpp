#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


int main()
{
	map<char,string> char_huff;

	char_huff.insert(pair<char,string>('a',"00"));
	char_huff.insert(pair<char,string>('b',"11"));

	map<char,string>::iterator test = char_huff.find('a');
	cout << test->second <<'\n';


}