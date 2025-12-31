# Sliding Window

## When to use?
- Substrings
- Continuous segments
- Subarrays
- Never revisit

### Fixed-Size Window (You know the window length in advance.)

1. **Maximum Sum Subarray of Size K** – Find the maximum sum of any contiguous subarray of size `k`.
2. **First Negative Number in Every Window of Size K**.
3. **Maximum of All Subarrays of Size K** (can also be solved using deque).
4. **Count of Anagrams / Permutations of a String in Another String**.
5. **Average of All Subarrays of Size K**.
6. **Minimum/Maximum Average Subarray of Size K**.

### Variable-Size Window (Window expands and shrinks based on conditions.)
7. **Longest Substring Without Repeating Characters**.
8. **Longest Substring with At Most K Distinct Characters**.
9. **Smallest Substring/Window Containing All Characters of Another String** (classic "Minimum Window Substring").
10. **Longest Substring with At Most Two Distinct Characters**.
11. **Subarray Sum Equals K** (can also be solved with prefix sum, but sliding window works if only positives).
12. **Longest Subarray with Sum ≤ K**.
13. **Smallest Subarray with Sum ≥ K**.
14. **Longest Repeating Character Replacement**.
15. **Fruit Into Baskets** (same as longest subarray with at most 2 distinct elements).

### Advanced / Variations

16. **Binary Subarray with Sum**.
17. **Number of Subarrays with Product Less Than K**.
18. **Count Subarrays with Exactly K Distinct Integers**.
19. **Longest Turbulent Subarray**.
20. **Max Consecutive Ones III** (allow at most K zero flips).
21. **Sliding Window Median** (uses heap + window).
22. **Longest Substring with Same Letters After K Replacements**.