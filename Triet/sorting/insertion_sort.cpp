#include <iostream>
#include <vector>

using namespace std;

bool compare_increasing(int const a , int const b)
{
	return a > b;
}

bool compare_decreasing(int const a , int const b)
{
	return a < b;
}
void insertion_sort(vector<int> &array, bool compare(int const a, int const b))
{
	for(int unsorted_part=1; unsorted_part < array.size(); unsorted_part++)
	{
		int sorted_part = unsorted_part - 1;
		int current_number = array[unsorted_part];		

		while(sorted_part >= 0 && compare(array[sorted_part], current_number))
		{
			array[sorted_part +1 ] = array[sorted_part];
			sorted_part--;
		}
		array[sorted_part +1 ] = current_number;
	}	
}

void print_array(vector<int> &array)
{
	for(int i=0; i < array.size(); i++)
	{
		cout<< array[i] << '\t';
	}
	putchar('\n');
}

int main()
{

	vector<int> array = {5,6,19,20,1,7};
	insertion_sort(array,compare_increasing);
	print_array(array);
	
	vector<int> array2 = {5,6,19,20,1,7};
	insertion_sort(array2,compare_decreasing);
	print_array(array2);
}