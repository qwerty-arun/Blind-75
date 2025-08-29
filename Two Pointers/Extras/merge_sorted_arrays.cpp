#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;        // pointer for last valid element in nums1
        int j = n - 1;        // pointer for last element in nums2
        int k = m + n - 1;    // pointer for last position in nums1

        while (i >= 0 && j >= 0) {
            if (nums1[i] >= nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        }

        // Copy remaining elements of nums2 if any
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};

int main() {
    Solution sol;

    // Example test case
    vector<int> nums1 = {1, 3, 5, 0, 0, 0};  // size m+n (here 3+3)
    int m = 3;
    vector<int> nums2 = {2, 4, 6};
    int n = 3;

    sol.merge(nums1, m, nums2, n);

    cout << "Merged array: ";
    for (int num : nums1) {
        cout << num << " ";
    }
    cout << endl;

    // Another test case
    vector<int> nums3 = {1, 2, 3, 0, 0, 0};
    int m2 = 3;
    vector<int> nums4 = {2, 5, 6};
    int n2 = 3;

    sol.merge(nums3, m2, nums4, n2);

    cout << "Merged array: ";
    for (int num : nums3) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}