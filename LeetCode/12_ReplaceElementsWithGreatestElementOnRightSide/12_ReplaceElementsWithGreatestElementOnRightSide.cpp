/* https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/

PROBLEM: Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.

After doing so, return the array.

Example 1:
Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]
Explanation: 
- index 0 --> the greatest element to the right of index 0 is index 1 (18).
- index 1 --> the greatest element to the right of index 1 is index 4 (6).
- index 2 --> the greatest element to the right of index 2 is index 4 (6).
- index 3 --> the greatest element to the right of index 3 is index 4 (6).
- index 4 --> the greatest element to the right of index 4 is index 5 (1).
- index 5 --> there are no elements to the right of index 5, so we put -1.

Example 2:
Input: arr = [400]
Output: [-1]
Explanation: There are no elements to the right of index 0.

Constraints:
1 <= arr.length <= 104
1 <= arr[i] <= 105
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        if (arr.size() == 0) return arr;

        int largest = -1;
        for (int i = arr.size() - 1; i >= 0; i--) {
            if (arr[i] > largest) {
                swap(largest, arr[i]);
            }
            else
            {
                arr[i] = largest;
            }
        }

        return arr;
    }
private:
    void swap(int& i, int& j) {
        int temp = i;
        i = j;
        j = temp;
    }
};

void print(vector<int>& arr) {
    for (auto it = arr.begin(); it != arr.end(); it++) {
        cout << *it << endl;
    }
}

int main()
{
    Solution s;
    vector<int> test1 = { 17, 18, 5, 4, 6, 1  };
    s.replaceElements(test1);
    print(test1);
}