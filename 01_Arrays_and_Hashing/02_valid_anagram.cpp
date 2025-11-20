/*
PROBLEM STATEMENT:
Given two strings 's' and 't', return 'true' 
if the two strings are anagrams of each other, otherwise return false.

An anagram is a string that contains the exace same characters as another string,
but the order of characters can be different

Example:
1) s = "racecar" and t = "carrace" will result in 'true'
2) s = "jar" and t = "jam" will result in 'false'

Recommended Time and Space: O(m+n) and O(1)
*/
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

// Brute Force: Time: O(nlogn + mlogm) and Space: O(n+m) or O(1)
class Solution1{
public:
    bool isAnagram(string s, string t) {
        // If lengths aren't equal, the strings can never be anagrams
        if(s.size() != t.size())
            return false;

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        return s == t; 
    }   
};

// Hash Map: Time: O(n+m) and Space: O(1)
class Solution2 {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        unordered_map<char, int> countS;
        unordered_map<char, int> countT;
        for (int i = 0; i < s.length(); i++) {
            countS[s[i]]++;
            countT[t[i]]++;
        }
        return countS == countT;
    }
};

// Hash Table: Time: O(n+m) and Space: O(1)
class Solution3 {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        vector<int> count(26, 0);
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (int val : count) {
            if (val != 0) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution1 soln1;
    Solution2 soln2;
    Solution3 soln3;
    cout<<soln1.isAnagram("racecar", "carrace")<<"\n";
    cout<<soln2.isAnagram("racecar", "carrace")<<"\n";
    cout<<soln3.isAnagram("racecar", "carrace")<<"\n";
    return 0;
}