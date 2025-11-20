/*
LONGEST CONSECUTIVE SEQUENCE:
Return length of longest consecutive sequence of elements that can be formed.
*/

#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;

class Solution1 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> mp;
        int res = 0;
        for(int num: nums)
        {
            if(!mp[num])
            {
                mp[num] = mp[num-1] + mp[num+1] + 1;
                mp[num - mp[num-1]] = mp[num];
                mp[num + mp[num+1]] = mp[num];
                res = max(res, mp[num]);
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;

        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int length = 1;
                while (numSet.find(num + length) != numSet.end()) {
                    length++;
                }
                longest = max(longest, length);
            }
        }
        return longest;
    }
};

int main()
{
    vector<int> nums = {0, 4, 6, 7, 1, 5, 2, 3};
    Solution1 soln1; //Hash map
    Solution2 soln2; //Hash set
    cout<<soln1.longestConsecutive(nums);
    cout<<soln2.longestConsecutive(nums);
    return 0;
}