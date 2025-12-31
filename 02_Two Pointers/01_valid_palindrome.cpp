/*
VALID PALINDROME

Given a string s, return true if it is a palindrome, otherwise return false.

A palindrome is a string that reads the same forward and backward. 
It is also case-insensitive and ignores all non-alphanumeric characters.

Note: Alphanumeric characters consist of letters (A-Z, a-z) and numbers (0-9).

Example 1:
Input: s = "Was it a car or a cat I saw?"

Output: true
Explanation: After considering only alphanumerical characters we have "wasitacaroracatisaw", which is a palindrome.
*/

#include<iostream>
#include<cctype>
#include<string>

//My solution Time: O(n) and Space: O(1)
class Solution1 {
public:
    bool isPalindrome(std::string s) {
        int i = 0, j = s.length()-1;
        while(i<j)
        {
            if(!isalnum(s[i]))
            {
                ++i;
                continue;
            }
            if(!isalnum(s[j]))
            {
                --j;
                continue;
            }

            if(tolower(s[i]) != tolower(s[j]))
            {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
};

class Solution2 {
public:
    bool isPalindrome(std::string s) {
        std::string newStr = "";
        for (char c : s) {
            if (isalnum(c)) {
                newStr += tolower(c);
            }
        }
        return newStr == std::string(newStr.rbegin(), newStr.rend());
    }
};

int main()
{
    Solution1 sol1; 
    Solution2 sol2; 
    std::cout<<sol1.isPalindrome("malayalam?")<<std::endl;
    std::cout<<sol2.isPalindrome("malayalam?")<<std::endl;
    return 0;
}