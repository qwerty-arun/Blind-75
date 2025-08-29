# Duplicates checking

```cpp
return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
```

# Anagrams

```cpp
unordered_map<char, int> countS;
unordered_map<char, int> countT;

for(int i = 0; i<s.length(); i++){
    countS[s[i]]++;
    countT[t[i]]++;
}
return countS == countT;
```

# Two Sum 

```cpp
for (int i = 0; i < nums.size(); i++) {
    int diff = target - nums[i];
    // Checks if diff exists in the map and is not the same index as i (ensuring two distinct numbers).
    if (indices.count(diff) && indices[diff] != i) {
        return {i, indices[diff]};
    }
}
```

# Product of Array Except Self

- Use suffix and prefix array
- Multiply them to find the final answer

# Top 'k' frequent elements

- It first counts the frequency of each unique number in nums using an unordered_map called count.

- Then, it transfers frequency-count pairs into a vector of pairs, where each pair stores (frequency, number) for sorting by frequency.

- The vector of pairs is sorted in descending order of frequency to have the most frequent elements first.

- Finally, the function collects the top k numbers from this sorted vector and returns them.

```cpp
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) { //frequency of each element
            count[num]++;
        }

        vector<pair<int, int>> arr; //transfer map entries to vector of pairs to facilitate sorting by frequency
        for (const auto& p : count) {
            arr.push_back({p.second, p.first});
        }
        //reverse iterators used here for descending order
        sort(arr.rbegin(), arr.rend());

        vector<int> res;
        for (int i = 0; i < k; ++i) {
            res.push_back(arr[i].second);
        }
        return res;
    }
```

# Group Anagrams

```cpp
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
```

# Longest Consecutive Sequence

## Solution-1
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> mp;
        int res = 0;
        for(int num: nums)
        {
            if(!mp[num])
            {
                mp[num] = mp[num-1] + mp[num+1] + 1;
                mp[num - mp[num-1]] = mp[num];
                mp[num + mp[num+1]] = mp[num];
                res = max(res, mp[num]);
            }
        }
        return res;
    }
};
```

## Solution-2

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;

        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int length = 1;
                while (numSet.find(num + length) != numSet.end()) {
                    length++;
                }
                longest = max(longest, length);
            }
        }
        return longest;
    }
};
```
