/*
PROBLEM STATEMENT:

Given an array of strings strs, group all anagrams together into sublists.
You can return the output in any order.

Example:
strs = ["act", "pots", "tops", "cat", "stop", "hat"]
output: [["hat"], ["act", "cat"], ["stop", "pots", "tops"]]

Recommended Time and Space: O(m * n) and O(m)
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

// Sorting: Time O(m * nlogn) and Space O(m*n)
class Solution1{
public:
vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    unordered_map<string, vector<string>> mp;

    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s);
    }

    vector<vector<string>> ans;
    for (auto& pair : mp) {
        ans.push_back(pair.second);
    }
    return ans;
}

};

// Hash Table: Time O(m*n) and Space O(m) extra space and O(m*n) space for output
class Solution2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> res;
        for (const auto& s : strs) {
            vector<int> count(26, 0);
            for (char c : s) {
                count[c - 'a']++;
            }
            string key = to_string(count[0]);
            for (int i = 1; i < 26; ++i) {
                key += ',' + to_string(count[i]);
            }
            res[key].push_back(s);
        }
        vector<vector<string>> result;
        for (const auto& pair : res) {
            result.push_back(pair.second);
        }
        return result;
    }
};

int main()
{
    Solution1 sol1;
    Solution2 sol2;
    vector<string> strs = {"act","pots","tops","cat","stop","hat"};
    vector<vector<string>> ans1 = sol1.groupAnagrams(strs);
    vector<vector<string>> ans2 = sol2.groupAnagrams(strs);

    cout<<"First Solution: \n";
    for(auto vec : ans1)
    {
        for(auto item : vec)
        {
            cout<<item<<" ";
        }
        cout<<"\n";
    }

    cout<<"Second Solution: \n";
    for(auto vec : ans2)
    {
        for(auto item : vec)
        {
            cout<<item<<" ";
        }
        cout<<"\n";
    }

    return 0;
}