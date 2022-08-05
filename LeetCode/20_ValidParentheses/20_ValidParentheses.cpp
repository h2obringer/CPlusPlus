#include <iostream>
#include <stack>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/1361/
https://leetcode.com/problems/valid-parentheses

PROBLEM: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "()[]{}"
Output: true

Example 3:

Input: s = "(]"
Output: false

CONSTRAINTS:
    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> parens;

        if (s.length() % 2 == 1) return false; //short-cut speedup, every open needs a close and therefore should come in pairs

        for (int i = 0; i < s.length(); i++) {
            switch (s[i]) {
            case '(':
            case '[':
            case '{':
                parens.push(s[i]);
                break;
            case ')':
                if (parens.empty()) return false;
                if (parens.top() != '(') return false;
                parens.pop();
                break;
            case ']':
                if (parens.empty()) return false;
                if (parens.top() != '[') return false;
                parens.pop();
                break;
            case '}':
                if (parens.empty()) return false;
                if (parens.top() != '{') return false;
                parens.pop();
                break;
            default:
                //shouldn't happen
                return false;
            }
        }

        if (!parens.empty()) return false;

        return true;
    }
};

int main()
{
    Solution s;
    cout << s.isValid("((") << endl;
    cout << s.isValid("((()))") << endl;
    cout << s.isValid(")))(((") << endl;
    cout << s.isValid("(){}[]") << endl;
    cout << s.isValid("({[]}))") << endl;
}