#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool compare_increasing(int const a , int const b)
{
	return a <= b;
}

bool compare_decreasing(int const a , int const b)
{
	return a > b;
}

void merge(vector<int> &array, int const begin, int const mid, int const end, bool compare (int const a, int const b) )
{
	int no_first_array = mid - begin +1;
	int no_second_array = end - mid;

	int first_array[no_first_array], second_array[no_second_array];

	//copy the two halves into the two arrays
	for(int i=0; i < no_first_array; i++)
		first_array[i] = array[begin+i];	

	for(int j = 0; j < no_second_array; j++)
		second_array[j] = array[mid + 1 + j];	

	int index_first_array = 0;
	int index_second_array = 0;
	int index_merged_array = begin;

	while(index_first_array < no_first_array && index_second_array < no_second_array)	
	{
		if(compare(first_array[index_first_array],second_array[index_second_array]))
		{
			array[index_merged_array] = first_array[index_first_array];
			index_first_array++;	
		}
		else
		{
			array[index_merged_array] = second_array[index_second_array];
			index_second_array++;	
		}
		index_merged_array++;
	}

	//fill in the remaining elements in the two arrays
	while(index_first_array < no_first_array)
	{
		array[index_merged_array] = first_array[index_first_array];
		index_first_array++;
		index_merged_array++;	
	}

	while(index_second_array < no_second_array)
	{
		array[index_merged_array] = second_array[index_second_array];
		index_second_array++;
		index_merged_array++;	
	}
	
}

void merge_sort(vector<int> &array,int const begin, int const end,bool compare(int const a, int const b))
{
	if(begin >= end) return; // this is the terminating condition for when two smaller array are of size one

	int mid = floor((begin+end)/2);
	merge_sort(array,begin,mid,compare);
	merge_sort(array,mid+1,end,compare);
	merge(array,begin,mid,end,compare);
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

	vector<int> array = {32,25,5,6,19,20,1,7};
	merge_sort(array,0,(array.size()-1),compare_increasing);
	print_array(array);
	
	vector<int> array2 = {32,25,5,6,19,20,1,7};
	merge_sort(array2,0,(array2.size()-1),compare_decreasing);
	print_array(array2);
}