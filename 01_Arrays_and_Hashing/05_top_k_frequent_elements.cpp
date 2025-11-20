/*
PROBLEM STATEMENT:

Given an integer array `nums` and an integer `k`, return the `k` most 
frequent elements within the array.

Example 1: nums = [1,2,2,3,3,3], k = 2 => [2,3]

Example 2: nums = [7,7], k = 1 => [7]

Recommended: Time of O(n) and Space of O(n)
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<queue>

using namespace std;

// Sorting: Time O(nlogn) and Space O(n)
class Solution1 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }

        vector<pair<int, int>> arr;
        for (const auto& p : count) {
            arr.push_back({p.second, p.first});
        }
        sort(arr.rbegin(), arr.rend());

        vector<int> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(arr[i].second);
        }
        return res;
    }
};

// Min-heap: Time O(nlogk) and Space O(n+k)
class Solution2 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        for (auto& entry : count) {
            heap.push({entry.second, entry.first});
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<int> res;
        for (int i = 0; i < k; i++) {
            res.push_back(heap.top().second);
            heap.pop();
        }
        return res;
    }
};

// Bucket Sort: Time O(n) and Space O(n)
class Solution3 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        vector<vector<int>> freq(nums.size() + 1);

        for (int n : nums) {
            count[n] = 1 + count[n];
        }
        for (const auto& entry : count) {
            freq[entry.second].push_back(entry.first);
        }

        vector<int> res;
        for (int i = freq.size() - 1; i > 0; --i) {
            for (int n : freq[i]) {
                res.push_back(n);
                if (res.size() == k) {
                    return res;
                }
            }
        }
        return res;
    }
};

int main()
{
    vector<int> nums = {1, 2, 2, 3, 3};
    int k = 2;
    Solution1 soln1;
    vector<int> ans1 = soln1.topKFrequent(nums, k);
    for(auto element : ans1)
        cout<<element<<" ";
    cout<<"\n";

    Solution2 soln2;
    vector<int> ans2 = soln1.topKFrequent(nums, k);
    for(auto element : ans2)
        cout<<element<<" ";
    cout<<"\n";

    Solution3 soln3;
    vector<int> ans3 = soln1.topKFrequent(nums, k);
    for(auto element : ans3)
        cout<<element<<" ";
    cout<<"\n";
    return 0;
}