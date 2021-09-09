#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int partition(vector<int>&array, int const low, int const high)
{
	int pivot = array[low];
	int runner_left = 1, runner_right=high;

	while(runner_left < runner_right) // the two index does not overstep each others 
	{
		while(array[runner_left] <= pivot && runner_left < high) runner_left++;

		while(array[runner_right] > pivot && runner_right >= 1)	 runner_right--;

		if( runner_left < runner_right) swap(array[runner_left],array[runner_right]); 	
	}
	swap(array[low],array[runner_right]);
	return runner_right;

}

void quick_sort(vector<int> &array,int const begin, int const end)
{
	if(begin < end )
	{
		int pivot_index = partition(array,begin,end);

		quick_sort(array,begin,pivot_index-1); //sort the left side of the pivot
		quick_sort(array,pivot_index+1,end); //sort the right side of the pivot
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
	vector<int> array = {32,25,5,6,19,20,1,7};
	quick_sort(array,0,array.size()-1);
	print_array(array);
}