#include <iostream>
#include <unordered_set>

/* https://leetcode.com/explore/learn/card/hash-table/183/combination-with-other-algorithms/1131/
https://leetcode.com/problems/happy-number/

PROBLEM: Write an algorithm to determine if a number "n" is happy. A happy number is a number defined by the following process:
- start with any positive integer, replace the number by the sum of the squares of its digits
- repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
- those numbers for which this process ends in 1 are happy
return true if n is a happy number, false if not.

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

Example 2:

Input: n = 2
Output: false

CONSTRAINTS:
    1 <= n <= 2^31-1
*/
bool isHappy(int n) {
    if (n == 1) return true;
    std::unordered_set<int> visited;
    visited.insert(n); //add the first # to the set

    while (n > 1) {
        int next_number = 0;
        int temp = n;
        //get the individual digits in n
        while (temp > 0) {
            int digit = temp % 10;
            temp = temp / 10;
            next_number += (digit * digit);
        }
        if (next_number == 1) return true;
        if (visited.count(next_number) > 0) return false;
        visited.insert(next_number);
        n = next_number;
    }

    return false;
}

int main()
{
    std::cout << isHappy(19) << std::endl;
    std::cout << isHappy(2) << std::endl;
}