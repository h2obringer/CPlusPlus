/* https://leetcode.com/problems/valid-mountain-array/

PROBLEM: Given an array of integers arr, return true if and only if it is a valid mountain array.

Recall that arr is a mountain array if and only if:

arr.length >= 3
There exists some i with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Example 1:
Input: arr = [2,1]
Output: false

Example 2:
Input: arr = [3,5,5]
Output: false
Example 3:

Input: arr = [0,3,2,1]
Output: true

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 104
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        if (arr.size() < 3) return false;

        const int UP = 0;
        const int DOWN = 1;

        int currentState = UP; //we must start moving uphill

        if (arr[0] >= arr[1]) return false; //we cannot start going downhill.

        for (int i = 2; i < arr.size(); i++) {
            if (arr[i - 1] < arr[i]) {
                if (currentState == UP) {
                    continue;
                }
                else
                {
                    return false;
                }
            }
            else if (arr[i - 1] > arr[i]) {
                if (currentState == DOWN) { //going down
                    continue;
                }
                else
                {
                    currentState++;
                    if (currentState > DOWN) return false;
                }
            }
            else return false;
        }

        if (currentState == DOWN) return true; //must end going downhill...
        return false;
    }
};

int main()
{
    Solution s;
    vector<int> test1 = { 1, 2, 1 };
    cout << s.validMountainArray(test1) << endl;

    vector<int> test2 = { 0, 3, 2,1 };
    cout << s.validMountainArray(test2) << endl;

    vector<int> test3 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << s.validMountainArray(test3) << endl;

    vector<int> test3 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout << s.validMountainArray(test3) << endl;
}