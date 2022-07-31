#include <iostream>
#include <vector>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1178/
https://leetcode.com/problems/intersection-of-two-arrays-ii/

PROBLEM: Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in
both arrays and you may return the result in any order.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Explanation: [9,4] is also accepted.

CONSTRAINTS:
    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000
*/
std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> result;
    std::unordered_map<int, int> temp; //num, count
    std::unordered_map<int, int> temp2; //num, count

    //populate the 1st dictionary
    for (int i = 0; i < nums1.size(); i++) {
        if (temp.count(nums1[i]) > 0) {
            temp[nums1[i]] = temp[nums1[i]] + 1;
        }
        else
        {
            temp[nums1[i]] = 1;
        }
    }
    //populate the 2nd dictionary
    for (int i = 0; i < nums2.size(); i++) {
        if (temp2.count(nums2[i]) > 0) {
            temp2[nums2[i]] = temp2[nums2[i]] + 1;
        }
        else
        {
            temp2[nums2[i]] = 1;
        }
    }

    if (nums1.size() < nums2.size()) { //small optimization
        for (auto it = temp.begin(); it != temp.end(); it++) {
            if (temp2.count(it->first) > 0) { //if the # exists in both dictionaries it will be in the result list
                int count = temp2[it->first];
                for (int i = 0; i < std::min(count, it->second); i++) { //we need to add the amount of occurrences that exist in BOTH arrays to the result
                    result.push_back(it->first);
                }
            }
        }
    }
    else
    {
        for (auto it = temp2.begin(); it != temp2.end(); it++) {
            if (temp.count(it->first) > 0) { //if the # exists in both dictionaries it will be in the result list
                int count = temp[it->first];
                for (int i = 0; i < std::min(count, it->second); i++) { //we need to add the amount of occurrences that exist in BOTH arrays to the result
                    result.push_back(it->first);
                }
            }
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
    std::vector<int> test1nums1 = { 1,2,2,1 };
    std::vector<int> test1nums2 = { 2,2 };
    std::vector<int> answer1 = intersect(test1nums1, test1nums2);
    print(answer1);

    std::cout << std::endl;

    std::vector<int> test2nums1 = { 4,9,5 };
    std::vector<int> test2nums2 = { 9,4,9,8,4 };
    std::vector<int> answer2 = intersect(test2nums1, test2nums2);
    print(answer2);

    std::cout << std::endl;
}