/*
PROBLEM STATEMENT:

Given an array `nums` and a `target`, return the indices `i` and `j` such that
`nums[i] + nums[j] == target and i != j`

You may assume that every input has exactly one pair of indices i and j that
satisfy the condition.

Return the answer with smaller index first.
Example 1: [3,4,5,6] and target = 7 will be [0,1]
Example 2: [4,5,6] and target = 10 will be [0,2]

Aim: Time: O(n) and Space: O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Brute Force: Time: O(n^2) and Space: O(1)
class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};

// Sorting: Time: O(nlogn) and Space: O(n)
class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> A;
        for (int i = 0; i < nums.size(); i++) {
            A.push_back({nums[i], i});
        }

        sort(A.begin(), A.end());

        int i = 0, j = nums.size() - 1;
        while (i < j) {
            int cur = A[i].first + A[j].first;
            if (cur == target) {
                return {min(A[i].second, A[j].second), 
                        max(A[i].second, A[j].second)};
            } else if (cur < target) {
                i++;
            } else {
                j--;
            }
        }
        return {};
    }
};

// Hash Map (Two Pass): Time: O(n) and Space: O(n)
class Solution3 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;  // val -> index

        for (int i = 0; i < nums.size(); i++) {
            indices[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (indices.count(diff) && indices[diff] != i) {
                return {i, indices[diff]};
            }
        }

        return {};
    }
};

// Hash Map (One pass): Time: O(n) and Space: O(n)
class Solution4 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> prevMap; //value : index

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];
            if (prevMap.find(diff) != prevMap.end()) {
                return {prevMap[diff], i};
            }
            prevMap.insert({nums[i], i});
        }
        return {};
    }
};

int main()
{
    Solution1 soln1;
    Solution2 soln2;
    Solution3 soln3;
    Solution4 soln4;

    vector<int> nums = {3,4,5,6};
    int target = 9;

    vector<int> ans1 = soln1.twoSum(nums, target);
    cout<<ans1[0] << " and " <<ans1[1]<<"\n";

    vector<int> ans2 = soln2.twoSum(nums, target);
    cout<<ans2[0] << " and " <<ans2[1]<<"\n";

    vector<int> ans3 = soln3.twoSum(nums, target);
    cout<<ans3[0] << " and " <<ans3[1]<<"\n";

    vector<int> ans4 = soln3.twoSum(nums, target);
    cout<<ans4[0] << " and " <<ans4[1]<<"\n";
    return 0;
}