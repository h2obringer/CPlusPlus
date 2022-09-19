/* https://leetcode.com/problems/squares-of-a-sorted-array/

PROBLEM: Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

    Example 1:
    Input: nums = [-4,-1,0,3,10]
    Output: [0,1,9,16,100]
    Explanation: After squaring, the array becomes [16,1,0,9,100].
    After sorting, it becomes [0,1,9,16,100].

    Example 2:
    Input: nums = [-7,-3,2,3,11]
    Output: [4,9,9,49,121]
 
Constraints:
    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums is sorted in non-decreasing order. 

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> negatives;
        negatives.reserve(nums.size());

        int currNeg = -1; //index of current negative value
        int currPos = 0; //index of current positive value
        int curr = 0; //index of current result we are on

        vector<int> result;
        result.reserve(nums.size());

        //populate our negative array...
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0) {
                negatives.push_back(nums[i]);
                currNeg = i;
            }
            else
            {
                break;
            }
        }
        currPos = currNeg + 1;

        while (currPos < nums.size() && currNeg >= 0) {
            if (nums[currPos] < abs(negatives[currNeg])) {
                result.push_back(nums[currPos] * nums[currPos]);
                currPos++;
            }
            else
            {
                result.push_back(nums[currNeg] * nums[currNeg]);
                currNeg--;
            }
            curr++;
        }

        //loop through remaining positives...
        while (currPos < nums.size()) {
            result.push_back(nums[currPos] * nums[currPos]);
            currPos++;
            curr++;
        }

        //loop through remaining negatives...
        while (currNeg >= 0) {
            result.push_back(nums[currNeg] * nums[currNeg]);
            currNeg--;
            curr++;
        }

        return result;
    }
};

void print(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

int main()
{
    vector<int> temp = { -1 };
    Solution s;
    vector<int> answer = s.sortedSquares(temp);
    print(answer);
}