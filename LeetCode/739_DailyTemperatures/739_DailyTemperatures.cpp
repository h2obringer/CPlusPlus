#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/1363/
https://leetcode.com/problems/daily-temperatures

PROBLEM: Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]

CONSTRAINTS:
    1 <= temperatures.length <= 105
    30 <= temperatures[i] <= 100
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> s;
        for (int i = 0; i < temperatures.size(); i++) {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                result[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }

        return result;
    }
};

//The Brute Force Method... Exceeds out time constraints...
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size());

        for (int i = 0; i < temperatures.size(); i++) {
            int numDays = 0;
            for (int j = i + 1; j < temperatures.size(); j++) {
                if (temperatures[i] < temperatures[j]) {
                    numDays = j - i;
                    break;
                }
            }
            result[i] = numDays;
        }

        return result;
    }
};

//helper
void print(vector<int> v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}
int main()
{
    Solution s;
    vector<int> temps = { 73,74,75,71,69,72,76,73 };
    print(s.dailyTemperatures(temps));
    cout << endl;

    vector<int> temps2 = { 30,40,50,60 };
    print(s.dailyTemperatures(temps2));
    cout << endl;

    vector<int> temps3 = { 30,60,90 };
    print(s.dailyTemperatures(temps3));
    cout << endl;

    vector<int> temps4 = { 90,60,30 };
    print(s.dailyTemperatures(temps4));
    cout << endl;
}