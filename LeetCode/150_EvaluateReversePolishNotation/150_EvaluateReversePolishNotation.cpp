#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/1394/
https://leetcode.com/problems/evaluate-reverse-polish-notation

PROBLEM: Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, and /. Each operand may be an integer or another expression.

Note that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate to a result, and there will not be any division by zero operation.


Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

CONSTRAINTS:
    1 <= tokens.length <= 104
    tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200]


*/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> ops;
        stack<int> nums;

        for (int i = tokens.size() - 1; i >= 0; i--) { //add to the stack in reversed order
            ops.push(tokens[i]);
        }

        while (!ops.empty()) {
            if (ops.top() == "*" || ops.top() == "/" || ops.top() == "+" || ops.top() == "-") {
                //PERFORM CALCULATIONS
                int temp1 = nums.top();
                nums.pop();
                int temp2 = nums.top();
                nums.pop();
                int result;

                if (ops.top() == "+") {
                    ops.pop();
                    result = temp2 + temp1;
                    nums.push(result);
                }
                else if (ops.top() == "-") {
                    ops.pop();
                    result = temp2 - temp1;
                    nums.push(result);
                }
                else if (ops.top() == "*") {
                    ops.pop();
                    result = temp2 * temp1;
                    nums.push(result);
                }
                else if (ops.top() == "/") {
                    ops.pop();
                    result = temp2 / temp1;
                    nums.push(result);
                }
            }
            else
            {
                //ADD NUMBERS TO THE NUMBERS STACK
                int num = atoi(ops.top().c_str());   //convert string to integer
                ops.pop();
                nums.push(num);
            }
        }

        return nums.top();
    }
};

int main()
{
    Solution s;
    vector<string> test = { "2","1","+","3","*" };
    cout << s.evalRPN(test) << endl;
    
    vector<string> test2 = { "4","13","5","/","+" };
    cout << s.evalRPN(test2) << endl;

    vector<string> test3 = { "10","6","9","3","+","-11","*","/","*","17","+","5","+" };
    cout << s.evalRPN(test3) << endl;
}