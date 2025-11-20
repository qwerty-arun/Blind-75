/*
PROBLEM STATEMENT:
Given an integer array 'nums', return 'true' if any value appears at least 
twice in the array, and return false if every element is distinct

Example: 
1) nums = [1,2,3,1] will result in 'true'
2) nums = [1,2,3,4] will result in 'false'

Recommended Time and Space: O(n) and O(n)
*/

// Brute Force: Time O(n^2) and Space O(1)

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    bool hasDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};


// Sorting: Time O(nlogn) and Space O(n) or O(1)

class Solution2 {
public:
    bool hasDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        return false;
    }
};

// Hash Set: Time and Space: O(n)
class Solution3 {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};

// Hash Set Length: Time O(n) and Space O(n)
class Solution4 {
public:
    bool hasDuplicate(vector<int>& nums) {
        return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
};

int main()
{
    Solution1 soln1;
    Solution2 soln2;
    Solution3 soln3;
    Solution4 soln4;
    vector<int> nums = {1,2,3,1};
    cout <<soln1.hasDuplicate(nums)<<"\n";
    cout <<soln2.hasDuplicate(nums)<<"\n";
    cout <<soln3.hasDuplicate(nums)<<"\n";
    cout <<soln4.hasDuplicate(nums)<<"\n";
}