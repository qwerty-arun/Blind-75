/*
PROBLEM STATEMENT: Encode and Decode Strings

Design an algorithm to encode a list of strings to a single string.
The encoded string is then decoded back to the original list of strings.

Input: ["I", "am", "doing", "dsa"]
Output: ["I", "am", "doing", "dsa"]

Recommended Time and Space: O(m) for each encode and decode and O(m+n)
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:

    string encode(vector<string>& strs) {
        if(strs.empty()) return "";
        vector<int> sizes;
        string res = "";
        for(string& s: strs)
            sizes.push_back(s.size());
        
        for(int sz: sizes)
            res += to_string(sz) + ',';
        
        res += '#';
        for(string& s: strs)
            res += s;
        cout<<res<<endl;
        return res;
    }

    vector<string> decode(string s) {
        if(s.empty()) return {};
        vector<int> sizes;
        vector<string> res;
        int i = 0;
        while(s[i] != '#')
        {
            string cur = "";
            while(s[i] != ',')
            {
                cur += s[i];
                i++;
            }
            sizes.push_back(stoi(cur));
            i++;
        }
        i++;
        for(int sz: sizes)
        {
            res.push_back(s.substr(i,sz));
            i += sz;
        }
        for(auto value: res)
            cout<<value<<endl;
        return res;
    }
};

int main()
{
    Solution soln;
    vector<string> str = {"neet", "code", "love", "you"};
    string res = soln.encode(str);
    vector<string> decoded = soln.decode(res);
}