#include <iostream>
#include <vector>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/185/hash_table_design_the_key/1124/
https://leetcode.com/problems/group-anagrams/

PROBLEM: Given an array of strings strs, group the anagrams together. You can return the answer in any order. An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]

CONSTRAINTS:
    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters.
*/

const int MAX_CHAR = 26;
std::string sortString(std::string str) {
    std::string result;
    int charCount[MAX_CHAR] = { 0 };

    //traverse string and increment count of characters
    for (int i = 0; i < str.length(); i++) {
        charCount[str[i] - 'a']++;
    }

    for (int i = 0; i < MAX_CHAR; i++) {
        for (int j = 0; j < charCount[i]; j++) {
            result += (char)('a' + i);
        }
    }

    return result;
}

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> result;
    std::unordered_map<std::string, std::vector<std::string>> temp; //key = sorted string, value = set[original_strings]
    for (int i = 0; i < strs.size(); i++) {
        temp[sortString(strs[i])].push_back(strs[i]);
    }

    for (auto it = temp.begin(); it != temp.end(); it++) { //iterate through the map
        result.push_back(it->second);
    }

    return result;
}

//helper
void print(std::vector<std::vector<std::string>> v) {
    std::cout << "[";
    for (int i = 0; i < v.size(); i++) {
        std::cout << "[";
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j]; 
            if (j < v[i].size() - 1) std::cout << ",";
        }
        std::cout << "]";
        if (i < v.size() - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

int main()
{
    std::vector<std::string> test = { "eat","tea","tan","ate","nat","bat" };
    std::vector<std::vector<std::string>> answer1 = groupAnagrams(test);
    print(answer1);

    std::cout << std::endl;

    std::vector<std::string> test2 = { "" };
    std::vector<std::vector<std::string>> answer2 = groupAnagrams(test2);
    print(answer2);

    std::cout << std::endl;


    std::vector<std::string> test3 = { "a"};
    std::vector<std::vector<std::string>> answer3 = groupAnagrams(test3);
    print(answer3);

    std::cout << std::endl;
}