// Find two number in an ascending order array that adds to a specific target
// Example: [2, 7, 11, 15] and target = 9 => [1,2]
// Example: [2, 3, 4] and target = 6 => [1, 3]

#include<vector>
#include<iostream>
using namespace std;

vector<int> twoSum_2(vector<int>& numbers, int target){
    int left = 0, right = numbers.size()-1;
    while(left < right){
        int sum = numbers[left] + numbers[right];
        if(sum == target)
            return {left+1, right+1};
        else if (sum < target)
            left++;
        else
            right--;
    }
    return {};
}

int main(){
    vector<int> nums = {2, 7, 11, 15};
    vector<int> ans = twoSum_2(nums, 9);
    for(auto index: ans){
        cout<<index<<" ";
    }
    cout<<endl;
}