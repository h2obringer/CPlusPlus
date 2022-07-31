#include <iostream>
#include <unordered_map>
#include <unordered_set>

/* https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1117/
https://leetcode.com/problems/isomorphic-strings/

PROBLEM: Given two strings s and t, determine if they are isomorphic
    Two strings are isomorphic if the characters in s can be replaced to get t.
    All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"
Output: true

Example 2:

Input: s = "foo", t = "bar"
Output: false

Example 3:

Input: s = "paper", t = "title"
Output: true

CONSTRAINTS:
    1 <= s.length <= 5*10^4
    t.length == s.length
    s and t consist of any valid ascii characters.

TIME COMPLEXITY ANALYSIS:
    Hashmaps and hashsets Insert/Search: O(1)
    Therefore O(n)
*/
bool isIsomorphic(std::string s, std::string t) {
    if (s.size() == 1) return true;

    std::unordered_map<char, char> temps;
    std::unordered_set<char> tempt;
    for (int i = 0; i < s.size(); i++) {
        if (temps.count(s[i]) > 0) { //if current s char exists in the map, compare the mapping with current t char
            if (temps[s[i]] != t[i]) return false;
        }
        else //otherwise insert it into the map
        {
            if (tempt.count(t[i]) > 0) return false; //if we have see current t char before then we would be attempting to add 2 mappings to the same character which is invalid...
            temps[s[i]] = t[i];
            tempt.insert(t[i]);
        }
    }

    return true;
}

int main()
{
    std::cout << isIsomorphic("egg", "add") << std::endl;
    std::cout << isIsomorphic("foo", "bar") << std::endl;
    std::cout << isIsomorphic("paper", "title") << std::endl;
}