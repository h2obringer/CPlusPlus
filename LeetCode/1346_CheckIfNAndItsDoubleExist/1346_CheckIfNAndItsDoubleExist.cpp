/* https://leetcode.com/explore/learn/card/fun-with-arrays/527/searching-for-items-in-an-array/3250/

PROBLEM: Given an array arr of integers, check if there exist two indices i and j such that :

i != j
0 <= i, j < arr.length
arr[i] == 2 * arr[j]

Example 1:

Input: arr = [10,2,5,3]
Output: true
Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]
Example 2:

Input: arr = [3,1,7,11]
Output: false
Explanation: There is no i and j that satisfy the conditions.


Constraints:

2 <= arr.length <= 500
-103 <= arr[i] <= 103
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        unordered_map<int, int> values; //key = arr[index], value = index of arr
        for (int i = 0; i < arr.size(); i++) {
            if (values.count(2 * arr[i]) > 0) { //if we have seen double the current value before
                return true;
            }
            else if (values.count(arr[i] / 2) > 0 && arr[i] % 2 == 0) { //if we have seen half the current value before
                return true;
            }
            values[arr[i]] = i;
        }

        return false;
    }
};

int main()
{
    Solution s;
    vector<int> test1 = {7,1,14,11};
    cout << s.checkIfExist(test1) << endl;
}