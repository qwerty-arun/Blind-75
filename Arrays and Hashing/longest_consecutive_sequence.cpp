/*
LONGEST CONSECUTIVE SEQUENCE:
Return length of longest consecutive sequence of elements that can be formed.
*/

#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
using namespace std;

class Solution {
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

int main()
{
    vector<int> nums = {0, 4, 6, 7, 1, 5, 2, 3};
    Solution soln;
    cout<<soln.longestConsecutive(nums);
    return 0;
}