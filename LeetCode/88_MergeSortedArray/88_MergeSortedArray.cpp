/* https://leetcode.com/problems/merge-sorted-array/

PROBLEM: You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
    Merge nums1 and nums2 into a single array sorted in non-decreasing order.

    The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

    Example 1:

    Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]
    Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
    The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

    Example 2:

    Input: nums1 = [1], m = 1, nums2 = [], n = 0
    Output: [1]
    Explanation: The arrays we are merging are [1] and [].
    The result of the merge is [1].

    Example 3:

    Input: nums1 = [0], m = 0, nums2 = [1], n = 1
    Output: [1]
    Explanation: The arrays we are merging are [] and [1].
    The result of the merge is [1].
    Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.

Constraints:
    nums1.length == m + n
    nums2.length == n
    0 <= m, n <= 200
    1 <= m + n <= 200
    -109 <= nums1[i], nums2[j] <= 109
 

Follow up: Can you come up with an algorithm that runs in O(m + n) time?
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        //since nums1 has been given the capacity to hold the valid values of nums1 (up to m) + the valid values of nums2 (up to n) i.e. it has a size of n+m, we can immediately start populating the sorted values starting at the end of nums1 until we are finished.
        if (nums1.size() != m + n) return; //sanity check

        //populate the final array from back to front
        for (int current = nums1.size() - 1; current >= 0; current--) {
            //since arrays are sorted in ascending order but we are populating nums1 from back to front we
            //want to populate the largest values to the back of nums1
            if (n <= 0 && m <= 0) return;
            if (n == 0) //understood that m > 0 here...
            {
                nums1[current] = nums1[m - 1];
                m--; //update m pointer
            }
            else if (m == 0) //understood that n > 0 here...
            {
                nums1[current] = nums2[n - 1];
                n--; //update n pointer
            }
            else if (nums1[m - 1] >= nums2[n - 1]) 
            {
                nums1[current] = nums1[m - 1];
                m--; //update m pointer
            }
            else
            {
                nums1[current] = nums2[n - 1];
                n--; //update n pointer
            }
        }

        return;
    }
};

void print(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

int main()
{
    Solution s;
    vector<int> test1_1 = { 1, 4, 5, 8, 20, 22, 0, 0, 0, 0, 0, 0 };
    vector<int> test1_2 = { 3, 6, 6, 8, 19, 23 };

    s.merge(test1_1, 6, test1_2, 6);

    print(test1_1);
}