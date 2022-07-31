#include <iostream>
#include <vector>
#include <unordered_set>

/* https://leetcode.com/explore/learn/card/hash-table/183/combination-with-other-algorithms/1105/
https://leetcode.com/problems/intersection-of-two-arrays/

PROBLEM: Given two integer arrays "nums1" and "nums2", return an array of their interesection. Each element in the result must be unique and you may return the result in any order.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted.

CONSTRAINTS:
    1 <= nums1.length, num2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

Time Complexity:
    - HashSet Search/Insert: O(1)
    - nums1.size() = n; nums2.size() = m; -> O(n + m)
*/
std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> result;
    result.reserve(1000); //initialize the result "array" to size 1000 to avoid resizing (since we know the max array length ahead of time).

    std::unordered_set<int> set1;
    for (int num : nums1) {
        set1.insert(num);
    }

    std::unordered_set<int> set2;
    for (int i = 0; i < nums2.size(); i++) {
        if (set1.count(nums2[i]) > 0) {
            set2.insert(nums2[i]);
        }
    }

    for (std::unordered_set<int>::iterator it = set2.begin(); it != set2.end(); it++) {
        result.push_back(*it);
    }

    return result;
}

//helper
void print(std::vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main()
{
    std::vector<int> test1nums1 = { 1,2,2,1 };
    std::vector<int> test1nums2 = { 2,2 };
    std::vector<int> answer1 = intersection(test1nums1, test1nums2);
    print(answer1);

    std::cout << std::endl;

    std::vector<int> test2nums1 = { 4,9,5 };
    std::vector<int> test2nums2 = { 9,4,9,8,4 };
    std::vector<int> answer2 = intersection(test2nums1, test2nums2);
    print(answer2);

    std::cout << std::endl;
}