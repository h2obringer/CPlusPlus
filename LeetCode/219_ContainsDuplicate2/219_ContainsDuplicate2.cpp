#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1121/
https://leetcode.com/problems/contains-duplicate-ii/

PROBLEM: Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

Example 1:

Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:

Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:

Input: nums = [1,2,3,1,2,3], k = 2
Output: false

CONSTRAINTS:
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    0 <= k <= 10^5
*/
bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
    std::unordered_map<int, std::list<int>> temp; //value, index
    for (int i = 0; i < nums.size(); i++) {
        std::list<int> mylist = temp[nums[i]];
        if (mylist.size() > 0) {
            for (auto it = mylist.begin(); it != mylist.end(); it++) {
                if (std::abs(*it - i) <= k) return true;
            }
        }

        temp[nums[i]].push_back(i);
    }

    return false;
}

int main()
{
    std::vector<int> test = { 1,2,3,1 };
    std::cout << containsNearbyDuplicate(test, 3) << std::endl;


    std::vector<int> test2 = { 1,0,1,1 };
    std::cout << containsNearbyDuplicate(test2, 1) << std::endl;


    std::vector<int> test3 = { 1,2,3,1,2,3 };
    std::cout << containsNearbyDuplicate(test3, 2) << std::endl;
}