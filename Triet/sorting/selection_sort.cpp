#include <iostream>
#include <vector>

//Best, Average, worst case = O(n^2)

using namespace std;

bool compare_increasing(const int *a, const int *b)
{
	return *a > *b;
}

bool compare_decreasing(const int *a, const int *b)
{
	return *a < *b;
}

void selection_sort(vector<int> &array, bool compare(const int* a, const int* b))
{		
	for(int sorted_part = 0; sorted_part < array.size()-1; sorted_part++)
	{
		int index_of_min=sorted_part;
		for(int unsorted_part = sorted_part+1; unsorted_part < array.size(); unsorted_part++)
		{
			if(compare(&array[index_of_min],&array[unsorted_part])) index_of_min = unsorted_part;
		}
		swap(array[sorted_part],array[index_of_min]);
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
	selection_sort(array,compare_increasing);
	print_array(array);

	vector<int> array2 = {5,6,19,20,1,7};
	selection_sort(array2,compare_decreasing);
	print_array(array2);
}