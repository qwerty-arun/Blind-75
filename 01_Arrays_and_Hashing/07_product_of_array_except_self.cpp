/*
Product of Array Except Self:
[1, 2, 3, 4] -> [48, 24, 12, 8]
Recommended Time and Space: O(n) and O(n)
*/

#include<iostream>
#include<vector>
using namespace std;

class Solution1{
public:
    vector<int> productOfArrayExceptSelf(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> prefix(n, 1);
        vector<int> suffix(n, 1);
        vector<int> ans(n, 1);
        for(int i = 1; i<n; i++)
            prefix[i] = prefix[i-1] * nums[i-1];
        for(int i = n-2; i>=0; i--)
            suffix[i] = suffix[i+1] * nums[i+1];
        for(int i = 0; i<n; i++)
            ans[i] = prefix[i] * suffix[i];
        return ans;
    }
};

class Solution2{
public:
    vector<int> productOfArrayExceptSelf(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> res(n,1);
        for(int i = 1; i<n; i++)
        {
            res[i] = res[i-1] * nums[i-1];
        }

        int postfix = 1;
        for(int i = n-1; i>=0; i--)
        {
            res[i] *= postfix;
            postfix *= nums[i];
        }
        return res;
    }
};

int main()
{
    Solution1 sol1;
    Solution2 sol2;
    vector<int> nums = {1, 2, 3, 4};

    vector<int> ans1 = sol1.productOfArrayExceptSelf(nums);
    vector<int> ans2 = sol2.productOfArrayExceptSelf(nums);

    for(int element: ans1)
    {
        cout<<element<<" ";
    }
    cout<<endl;

    for(int element: ans2)
    {
        cout<<element<<" ";
    }
    cout<<endl;
    return 0;
}