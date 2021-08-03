// Given an array see and a number write a function that can discern whether or not
//that number is the sum of the numbers in the array
#include <iostream>
#include <vector>
#include <unordered_map>

bool can_sum(int target,std::vector<int> array)
{
	bool has_final_result = false;
	//base case
	if(target == 0 ) return true;
	if(target < 0 ) return false;
	for(int i=0; i < array.size();i++)
	{
		int remainder = target - array[i];
		if (can_sum(remainder,array)== true) 
		{
			has_final_result = true;
			break;
		}
	}
	if(has_final_result == true) return true;
	else return false;
}

// bool mcan_sum(int target,std::vector<int> array, std::unordered_map<int,int> um_remain)
// {
// 	if(um_remain.find(target) != um_remain.end() ) return 
// 	if(target == 0 ) return true;
// 	if(target < 0 ) return false;
// }


int main()
{

	std::unordered_map<int,int> um_remain;
	um_remain[3] = 1;
	um_remain[4] = 2;
	if (um_remain.find(3) != um_remain.end()) std::cout<< um_remain.at(3) <<'\n';
	// std::vector<int> array1 = {2,3};
	// std::vector<int> array2 = {5,3,4,7};
	// std::vector<int> array3 = {2,4};
	// std::vector<int> array4 = {2,3,5};
	// std::vector<int> array5 = {7,14};
	// std::cout<< can_sum(7,array1) <<'\n';
	// std::cout<< can_sum(7,array2) <<'\n';
	// std::cout<< can_sum(7,array3) <<'\n';
	// std::cout<< can_sum(8,array4) <<'\n';
	// std::cout<< can_sum(300,array5) <<'\n';

}