#include <iostream>
#include <vector>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1115/
https://leetcode.com/problems/two-sum/

PROBLEM: Given an array of integers "nums" and an integer "target", return indeces of the two numbers such that they add up to "target". You may assume that each input would have exactly one solution, and you may not use the same element twice. You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

CONSTRAINTS:
    2 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9
    only one valid answer exists

TIME COMPLEXITY ANALYSIS:
    Hashmap inserts/search: O(1)
    Therefore our solution is O(n) as we loop through the nums array twice
*/
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::vector<int> result;
    result.reserve(2);
    std::unordered_map<int, int> temp; //value, index
    //add each number to a hashmap
    for (int i = 0; i < nums.size(); i++) {
        temp[nums[i]] = i;
    }

    for (int i = 0; i < nums.size(); i++) {
        int toFind = target - nums[i];
        if (temp.count(toFind) > 0 && temp[toFind] != i) {
            result.push_back(temp[toFind]);
            result.push_back(i);
            return result;
        }
    }

    return result;
}

//helper
void print(std::vector<int> v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main()
{
    std::vector<int> test = { 2,7,11,15 };
    std::vector<int> answer = twoSum(test, 9);
    print(answer);

    std::cout << std::endl;

    std::vector<int> test2 = { 3,2,4 };
    std::vector<int> answer2 = twoSum(test2, 6);
    print(answer2);

    std::cout << std::endl;

    std::vector<int> test3 = { 3,3 };
    std::vector<int> answer3 = twoSum(test3, 6);
    print(answer3);

    std::cout << std::endl;
}