#include <iostream>
#include <unordered_map>
using namespace std;

/* https://leetcode.com/explore/learn/card/recursion-i/255/recursion-memoization/1661/
https://leetcode.com/problems/fibonacci-number

PROBLEM: The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).

Example 1:

Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:

Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:

Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

CONSTRAINTS:
    0 <= n <= 30
*/

class Solution {
public:
    int fib(int n) {
        if (n < 2) return n;

        unordered_map<int, int> memo; //n, result
        memo.insert(pair<int, int>(0, 0)); //F(0)
        memo.insert(pair<int, int>(1, 1)); //F(1)

        fib(n, 2, memo);

        return memo[n];
    }
private:
    void fib(int target, int current, unordered_map<int, int>& memo) {
        memo.insert(pair<int, int>(current, memo[current - 1] + memo[current - 2]));
        if (target == current) return;

        fib(target, current + 1, memo);
    }
};

int main()
{
    Solution s;
    cout << s.fib(8) << endl;
}