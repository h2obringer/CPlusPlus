#include <iostream>
#include <vector>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1177/
https://leetcode.com/problems/minimum-index-sum-of-two-lists/

PROBLEM: Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.
You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with
no order requirement. You could assume there always exists an answer.

Example 1:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".

Example 2:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["KFC","Shogun","Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).

CONSTRAINTS:
    1 <= list1.length, list2.length <= 1000
    1 <= list1[i].length, list2[i].length <= 30
    list1[i] and list2[i] consist of spaces ' ' and English letters
    all the strings of list1 are unique
    all the strings of list2 are unique

TIME COMPLEXITY ANALYSIS:
    Hashmaps Insert/Search: O(1) therefore O(n + m)
*/
std::vector<std::string> findRestaurant(std::vector<std::string>& list1, std::vector<std::string>& list2) {
    std::vector<std::string> result;
    std::unordered_map<std::string, int> temp; //restaurant, index
    //populate the dictionary
    for (int i = 0; i < list1.size(); i++) {
        temp[list1[i]] = i;
    }

    int min_index_sum = INT_MAX;
    for (int i = 0; i < list2.size(); i++) {
        if (temp.count(list2[i]) > 0) {
            int list1_index = temp[list2[i]];
            int sum = list1_index + i;
            if (sum <= min_index_sum) {
                if (sum < min_index_sum) {
                    result.clear();
                    min_index_sum = sum;
                }
                result.push_back(list2[i]);
            }
        }

        if (i > min_index_sum) break; //exit the for loop early
    }

    return result;
}

//helper
void print(std::vector<std::string> v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main()
{
    std::vector<std::string> test1list1 = { "Shogun","Tapioca Express","Burger King","KFC" };
    std::vector<std::string> test1list2 = { "Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun" };
    std::vector<std::string> answer1 = findRestaurant(test1list1, test1list2);
    print(answer1);

    std::cout <<  std::endl;

    std::vector<std::string> test2list1 = { "Shogun","Tapioca Express","Burger King","KFC" };
    std::vector<std::string> test2list2 = { "KFC","Shogun","Burger King" };
    std::vector<std::string> answer2 = findRestaurant(test2list1, test2list2);
    print(answer2);

    std::cout << std::endl;
}