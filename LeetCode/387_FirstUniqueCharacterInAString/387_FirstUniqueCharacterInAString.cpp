#include <iostream>
#include <unordered_map>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1120/
https://leetcode.com/problems/first-unique-character-in-a-string/

PROBLEM: Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

Example 1:

Input: s = "leetcode"
Output: 0

Example 2:

Input: s = "loveleetcode"
Output: 2

Example 3:

Input: s = "aabb"
Output: -1

CONSTRAINTS:
    1 <= s.length <= 10^5
    s consists of only lowercase English letters
*/
int firstUniqChar(std::string s) {
    std::unordered_map<char, int> chars; //character, count
    for (int i = 0; i < s.size(); i++) {
        if (chars.count(s[i]) > 0) {
            chars[s[i]] = chars[s[i]] + 1;
        }
        else {
            chars[s[i]] = 1;
        }
    }

    for (int i = 0; i < s.size(); i++) {
        if (chars[s[i]] == 1) {
            return i;
        }
    }

    return -1;
}

int main()
{
    std::cout << firstUniqChar("leetcode") << std::endl;
    std::cout << firstUniqChar("loveleetcode") << std::endl;
    std::cout << firstUniqChar("aabb") << std::endl;
}