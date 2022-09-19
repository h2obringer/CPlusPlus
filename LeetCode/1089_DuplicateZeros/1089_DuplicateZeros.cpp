/* https://leetcode.com/explore/learn/card/fun-with-arrays/525/inserting-items-into-an-array/3245/

PROBLEM: Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.

Example 1:
    Input: arr = [1,0,2,3,0,4,5,0]
    Output: [1,0,0,2,3,0,0,4]
    Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]

    Example 2:

    Input: arr = [1,2,3]
    Output: [1,2,3]
    Explanation: After calling your function, the input array is modified to: [1,2,3]

Constraints:
    1 <= arr.length <= 104
    0 <= arr[i] <= 9
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) {
                for (int j = arr.size() - 2; j >= i + 1; j--) {
                    arr[j + 1] = arr[j];
                }

                if (i + 1 < arr.size()) {
                    arr[i + 1] = 0;
                    i++;
                }
            }
        }
    }
};

void print(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

int main()
{
    Solution s;
    vector<int> test1 = { 1,0,2,3,0,4,5,0 };
    s.duplicateZeros(test1);
    print(test1);
    cout << endl;

    vector<int> test2 = { 0 };
    s.duplicateZeros(test2);
    print(test2);
    cout << endl;

    vector<int> test3 = { 8,4,5,0,0,0,0,7 };
    s.duplicateZeros(test3);
    print(test3);
}