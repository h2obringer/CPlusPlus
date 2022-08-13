#include <iostream>
#include <stack>
#include <string>
using namespace std;

/*

PROBLEM: Given an encoded string, return its decoded string.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
The test cases are generated so that the length of the output will never exceed 105.

Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"


CONSTRAINTS:
    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in s are in the range [1, 300]
*/

class Solution {
public:
	string decodeString(string s) {
		stack<char> working;
		for(int i = 0; i < s.size(); i++) {
			if (s[i] != ']') {
				working.push(s[i]);
			}
			else {
				string temp = "";
				while (!working.empty() && working.top() != '[') {
					temp = working.top() + temp;
					working.pop();
				}

				working.pop(); //remove the ‘]’

				string numTemp = "";
				while(!working.empty() && isdigit(working.top())) {
					numTemp = working.top() + numTemp;
					working.pop();
				}

				int mult = stoi(numTemp);
				string temp2 = "";
				for(int j = 0; j < mult; j++) {
					temp2 += temp; //concat with itself mult times
				}

				for(char c : temp2) {
					working.push(c);
				}
			}
		}

		string result = "";
		while(!working.empty()) {
			result = working.top() + result;
			working.pop();
		}

		return result;
	}
};

int main()
{
	Solution s;
	cout << s.decodeString("2[abc]3[bc]de") << endl;
}