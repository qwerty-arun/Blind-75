/*
Given two integers a and b, return the sum of the two integers without using the + and - operators.

Example 1:

Input: a = 1, b = 1

Output: 2
Example 2:

Input: a = 4, b = 7

Output: 11
Constraints:

-1000 <= a, b <= 1000
*/

// Solution-1
/*
Intuition

The problem asks us to compute the sum of two integers without using the + or - operators.

At the bit level, addition works using two simple ideas:
- XOR (^) gives the sum of two bits without considering carry
- AND (&) + left shift determines where a carry is generated

For example (single bit):
- 0 + 0 → sum = 0, carry = 0
- 1 + 0 → sum = 1, carry = 0
- 1 + 1 → sum = 0, carry = 1

By repeating this logic for all bit positions, we can simulate normal addition exactly as it happens in hardware.

Because integers are stored in fixed-width (32-bit) two’s complement form, we also need to:
- limit results to 32 bits
- correctly convert the result back if it represents a negative number

Algorithm

1. Initialize:
    - result to store the final sum
    - carry = 0
    - a mask to keep numbers within 32 bits

2. For each bit position from 0 to 31:
    - Extract the i-th bit from both numbers
    - Compute the current sum bit using XOR:
        sum_bit = a_bit XOR b_bit XOR carry
    - Update the carry:
        carry = (a_bit + b_bit + carry) ≥ 2
    - Set the i-th bit in the result if sum_bit is 1

3. After processing all bits:
    - If the result represents a negative number in 32-bit two’s complement:
    - Convert it back to a signed integer

4. Return the result
*/

class Solution {
public:
    int getSum(int a, int b) {
        int carry = 0, res = 0, mask = 0xFFFFFFFF;

        for (int i = 0; i < 32; i++) {
            int a_bit = (a >> i) & 1;
            int b_bit = (b >> i) & 1;
            int cur_bit = a_bit ^ b_bit ^ carry;
            carry = (a_bit + b_bit + carry) >= 2 ? 1 : 0;
            if (cur_bit) {
                res |= (1 << i);
            }
        }

        if (res > 0x7FFFFFFF) {
            res = ~(res ^ mask);
        }

        return res;
    }
};

// Solution-2
/*
Intuition

We need to add two integers without using + or -.
Binary addition can be built from two operations:

1. Sum without carry
    - a XOR b gives the bit-by-bit sum ignoring carry
    (because 1 XOR 1 = 0, which matches sum without carry)

2. Carry information
    - a AND b tells us where both bits are 1, which creates a carry
    - shifting left by 1 (<< 1) moves that carry to the next higher bit

So we can repeatedly:
- compute the carry
- update the partial sum using XOR
- add the carry again (by setting b = carry)

We keep doing this until there is no carry left (b == 0).

Because many languages use fixed-width integers (like 32-bit signed integers), we use a mask to keep only the lower 32 bits at each step. Finally, if the result represents a negative number in 32-bit two’s complement form, we convert it back to a signed integer.

Algorithm

1. Define constants for 32-bit handling:
    - mask to keep only 32 bits
    - max_int as the largest 32-bit signed integer

2. While b is not zero:
    - Compute carry:
        - carry = (a AND b) << 1
    - Compute sum without carry:
        - a = (a XOR b), then apply the 32-bit mask
    - Move carry into b (also masked to 32 bits)

3. After the loop, a holds the 32-bit result.

4. If a is within signed range, return it directly.

5. Otherwise, convert from unsigned 32-bit to a negative signed value and return it.
*/

class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a ^= b;
            b = carry;
        }
        return a;
    }
};