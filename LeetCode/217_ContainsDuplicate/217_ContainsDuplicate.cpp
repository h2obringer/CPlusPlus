#include <iostream>
#include <vector>
#include <unordered_set>

/* https://leetcode.com/explore/learn/card/hash-table/183/combination-with-other-algorithms/1112/
https://leetcode.com/problems/contains-duplicate/

PROBLEM: Given an integer array "nums", return "true" if any value appears at least twice in the array, and return "false" if every element is distinct.

Example 1:

Input: nums = [1,2,3,1]
Output: true

Example 2:

Input: nums = [1,2,3,4]
Output: false

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true

CONSTRAINTS:
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
*/
bool containsDuplicate(std::vector<int>& nums) {
    std::unordered_set<int> set;
    for (int key : nums) {
        if (set.count(key) > 0) return true;
        set.insert(key);
    }
    return false;
}

int main()
{
    std::vector<int> test = { 1,2,3,1 };
    std::cout << containsDuplicate(test) << std::endl;

    std::vector<int> test2 = { 1,2,3,4 };
    std::cout << containsDuplicate(test2) << std::endl;

    std::vector<int> test3 = { 1,1,1,3,3,4,3,2,4,2 };
    std::cout << containsDuplicate(test3) << std::endl;


    std::cout << "Hello World!\n";
}