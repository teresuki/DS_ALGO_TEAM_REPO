// Given an array see and a number write a function that can discern whether or not
//that number is the sum of the numbers in the array
#include <iostream>
#include <vector>
#include <map>

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

class Cansum
{
	private:
	std::map<int,bool> stored_ans;
	public:
	bool compute_cansum(int target,std::vector<int> array)
	{
		if(stored_ans.find(target) != stored_ans.end()) return stored_ans.find(target)->second;
		if(target == 0 ) return true;
		if(target < 0 ) return false;

		for(int i=0; i < array.size();i++)
		{
			int remainder = target - array[i];
			if(compute_cansum(remainder,array) ==true ) this->stored_ans.insert(std::pair<int,bool>(remainder,true));
			else this->stored_ans.insert(std::pair<int,bool>(remainder,false));
		}
	}

};

int main()
{

	std::vector<int> array1 = {2,3};
	std::vector<int> array2 = {5,3,4,7};
	std::vector<int> array3 = {2,4};
	std::vector<int> array4 = {2,3,5};
	std::vector<int> array5 = {7,14};

	// std::cout<< can_sum(7,array2) <<'\n';
	// std::cout<< can_sum(7,array3) <<'\n';
	// std::cout<< can_sum(8,array4) <<'\n';
	// // std::cout<< can_sum(300,array5) <<'\n';

	Cansum C1;
	std::cout<<C1.compute_cansum(7,array1)<<'\n';
	std::cout<< can_sum(7,array1) <<'\n';

}