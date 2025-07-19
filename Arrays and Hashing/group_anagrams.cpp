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