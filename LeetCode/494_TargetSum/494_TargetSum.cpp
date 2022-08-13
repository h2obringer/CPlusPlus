#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/232/practical-application-stack/1389/
https://leetcode.com/problems/target-sum

PROBLEM: You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:

Input: nums = [1], target = 1
Output: 1

CONSTRAINTS:
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000

TIME/SPACE ANALYSIS:
    Time: O(2^n) -> 2 decisions at each index...
    Space: O(n) -> the system stack only ever has up to n + 1 functions calls on it max
*/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int result = 0;
        findTargetSumWays(nums, 0, target, 0, result);

        return result;
    }
private:
    void findTargetSumWays(vector<int>& nums, int current_index, int target, int currentSum, int& result) {
        if (current_index == nums.size()) { //we only reach the base case AFTER we have iterated over every element in the nums array
            if (currentSum == target) {
                result++;
            }
            return;
        }

        findTargetSumWays(nums, current_index + 1, target, currentSum + nums[current_index], result);
        findTargetSumWays(nums, current_index + 1, target, currentSum - nums[current_index], result);

        return;
    }
};

int main()
{

    Solution s;
    vector<int> test1 = {1,1,1,1,1};
    int target1 = 3;
    cout << s.findTargetSumWays(test1, target1) << endl;
}