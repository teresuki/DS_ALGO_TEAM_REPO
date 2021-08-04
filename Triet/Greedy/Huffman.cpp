#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct comp {
    template <typename T>
  
    // Comparator function
    bool operator()(const T& l,
                    const T& r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
    }
};
  
// Function to sort the map according
// to value in a (key-value) pairs
void sort_by_second_value(map<char, int>& M)
{
  
    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<char, int>, comp> S(M.begin(),
                                   M.end());
  
    // Print the sorted value
    for (auto& it : S) {
        cout << it.first << '\t'
             << it.second << endl;
    }
}

class Document
{
	private:
	// vector< pair<char,
	map<char,int> frequency_of_char;

	public:
	void insert_plain_text()
	{
		string usr_input;
		cout<<"Enter the input text: ";
		cin >> usr_input;


		for(int c=0; c < usr_input.size(); c++)
		{
			if( this->frequency_of_char.find(usr_input[c]) == frequency_of_char.end())
			{
				frequency_of_char.insert(pair<char,int>(usr_input[c],1));
			}
			else
			{
				auto existed_char = frequency_of_char.find(usr_input[c]);
				existed_char->second++;
			}
		}

		sort_by_second_value(frequency_of_char);


	}

};

int main()
{
	Document D1;

	D1.insert_plain_text();

}