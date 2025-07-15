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
using namespace std;

// Brute Force
class Solution {
public:
    bool isAnagram(string s, string t) {
        // If lengths aren't equal, the strings can never be anagrams
        if(s.size() != t.size())
            return false;

        for(int i = 0; i<s.size(); i++)
        {
            for(int j = 0; j<t.size(); j++)
            {
                
            }
        }    
    }
};
