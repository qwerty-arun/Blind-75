/*
Counting Bits

Given an integer n, count the number of 1's in the binary representation of every number in the range [0, n].

Return an array output where output[i] is the number of 1's in the binary representation of i.

Example 1:

Input: n = 4

Output: [0,1,1,2,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100

Constraints:

0 <= n <= 1000

*/

#include <cstdint>
#include <vector>

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n){
            count += (n & 1);
            n >>= 1;
        }
        return count;
    }

    std::vector<int> countBits(int n) {
        std::vector<int> ans;
        for(int i = 0; i <= n; i++){
            ans.push_back(hammingWeight(i));
        }
        return ans;
    }
};
