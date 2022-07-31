#include <iostream>
#include <vector>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/183/combination-with-other-algorithms/1176/
https://leetcode.com/problems/single-number/

PROBLEM: Given a non-empty array of integers "nums", every element appears twice except for one. Find that single one. You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:

Input: nums = [2,2,1]
Output: 1

Example 2:

Input: nums = [4,1,2,1,2]
Output: 4

Example 3:

Input: nums = [1]
Output: 1

CONSTRAINTS:
    1 <= NUMS.LENGTH <= 3 * 10^4
    -3*10^4 <= NUMS[I] <= 3 * 10^4
    Each element in the array appears twice except for one element which appears only once.
*/
int singleNumber(std::vector<int>& nums) {
    std::unordered_map<int, int> map; //number, count
    for (int num : nums) {
        if (map.count(num) > 0) {
            map.insert_or_assign(num, 2); //no need to take an accurate count... all we care about is that the value is greater than 1
        }
        else {
            map.insert_or_assign(num, 1);
        }
    }

    for (int num : nums) {
        if (map[num] == 1) return num;
    }

    return -1;
}

int main()
{
    std::vector<int> test = { 2,2,1 };
    std::cout << singleNumber(test) << std::endl; //1

    std::vector<int> test2 = { 4,1,2,1,2 };
    std::cout << singleNumber(test2) << std::endl; //4

    std::vector<int> test3 = { 1 };
    std::cout << singleNumber(test3) << std::endl; //1
}