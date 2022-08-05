#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/231/practical-application-queue/1371/
https://leetcode.com/problems/perfect-squares

PROBLEM: Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

CONSTRAINTS:
    1 <= n <= 104

SOLUTION ANALYSIS:
Usage of Dynamic Programming. 

We iterate through each possible # once performing an log(n) operations computing to O(n*log(n)) time. O(n) space complexity.
*/

class Solution {
public:
    int numSquares(int n) {
        //generate all perfect squares between 1 and n -> dynamic programming to store previous results.
        vector<int> dp(n + 1, n); //dynamic programming //initialize every value to n
        dp[0] = 0; //starting point

        for (int target = 1; target <= n; target++) {
            for (int i = 1; i <= target; i++) { //compute the square of the target
                int s = i * i; //i squared
                if (target - s < 0) break;
                dp[target] = min(dp[target], dp[target - s] + 1);
            }
        }

        return dp[n]; //return the computed result for n
    }
};

int main()
{
    Solution s;
    cout << s.numSquares(13) << endl;
}