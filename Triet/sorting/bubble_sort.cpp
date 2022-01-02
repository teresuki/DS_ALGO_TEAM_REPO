#include <iostream>
#include <vector>

//Worst case and average case time complexity is O(n^2)
// best case time complexity is O(n) 

using namespace std;

int compare_increasing(const void * a, const void *b)
{
	return ( *(int*)a - *(int*)b );
}

int compare_decreasing(const void * a, const void *b)
{
	return -( *(int*)a - *(int*)b );
}

void bubble_sort(vector<int> &array, int compare (const void *, const void *))
{
	for(int number=0; number < array.size(); number++)
	{
		for(int runner=number+1; runner < array.size(); runner++ )
		{
			if(compare(&array[number],&array[runner]) > 0) swap(array[runner],array[number]);
		}
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
	bubble_sort(array, compare_decreasing);
	print_array(array);

	vector<int> array2 = {5,6,19,20,1,7};
	bubble_sort(array2,compare_increasing);
	print_array(array2);
}