/*
Longest Substring Without Repeating Characters
Solved 
Given a string s, find the length of the longest substring without duplicate characters.

A substring is a contiguous sequence of characters within a string.

Example 1:

Input: s = "zxyzxyz"
Output: 3
Explanation: The string "xyz" is the longest without duplicate characters.

Example 2:

Input: s = "xxxx"
Output: 1
*/

#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
                unordered_map<char, int> map;
        int l = 0, res = 0;

        for (int r = 0; r < s.size(); r++) {
            if (map.find(s[r]) != map.end()) {
                l = max(map[s[r]] + 1, l);
            }
            map[s[r]] = r;
            res = max(res, r - l + 1);
        }
        return res;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }
            charSet.insert(s[r]);
            res = max(res, r - l + 1);
        }
        return res;
    }
};

int main(){
    Solution1 soln1;
    Solution2 soln2;
    cout<<soln1.lengthOfLongestSubstring("zxyzxyz")<<endl;
    cout<<soln2.lengthOfLongestSubstring("zxyzxyz")<<endl;
}