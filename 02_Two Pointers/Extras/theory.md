# Two Pointers

- Used on Arrays, Strings, Linked Lists

## When to use?

- Same Direction, slow and fast: to find middle element, to detect cycle
- Opposite Direction: sorted arrays and O(n)

## Advantages

- Reduces iterations
- Track relationship between two places
- Avoids extra space

## Where to use?

- Palindromes
- Reversals
- Merge Sort Data
- 'k' sized comparisions
- To find middle element of LL
- To detect cycle

## List of problems

### Array / Sorting

1. **Pair Sum Problems**

   - Two Sum II – Input array is sorted
   - Count pairs with a given sum
   - Find if there exists a pair with a given difference

2. **Merging Problems**

   - Merge two sorted arrays (your last example)
   - Merge k sorted arrays (extension with heaps)

3. **Window / Subarray Problems**

   - Minimum size subarray with given sum
   - Longest subarray with sum ≤ K
   - Maximum number of consecutive ones with at most K zero flips

4. **Classic Problems**

   - Move Zeroes to the end
   - Sort array of 0s, 1s, and 2s (Dutch National Flag Problem)
   - Trapping Rain Water
   - Container With Most Water

### String Problems

1. Valid Palindrome (check if string reads same forward/backward)
2. Valid Palindrome II (at most one removal allowed)
3. Reverse Words in a String (or reverse a string in-place)
4. Longest Substring Without Repeating Characters (sliding window + two pointers)
5. Minimum Window Substring (advanced sliding window)

### Linked List

1. Find the middle of a linked list (slow & fast pointers)
2. Detect cycle in a linked list (Floyd’s cycle detection)
3. Find the starting node of cycle in linked list
4. Check if linked list is a palindrome
5. Remove N-th node from the end

### Searching

1. Find first and last position of element in a sorted array (binary + two pointers variant)
2. Three Sum / Four Sum problems (sorting + two pointers)
3. Find closest pair from two sorted arrays
4. Minimum difference pair between two arrays

### Advanced / Mixed

1. Sliding Window Maximum (two pointers + deque)
2. Longest Mountain in Array
3. Minimum operations to reduce X to zero
4. Partition Labels (string partitioning with two pointers)
5. Longest Repeating Character Replacement

### ✅ If you’re starting out, I’d recommend this **progression path**:

1. Array basics → Pair Sum, Move Zeroes, Container With Most Water
2. Strings → Palindrome, Longest Substring Without Repeating Characters
3. Linked List → Middle element, Detect Cycle, Palindrome check
4. Advanced → Trapping Rain Water, Three Sum, Sliding Window problems