#include <iostream>
#include <string>
using namespace std;

/* https://leetcode.com/problems/palindrome-number/

PROBLEM: Given an integer x, return true if x is palindrome integer.
An integer is a palindrome when it reads the same backward as forward.
For example, 121 is a palindrome while 123 is not.

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 
Constraints:
-231 <= x <= 231 - 1
*/
class Solution {
public:
	bool isPalindrome(int x) {
		string temp = std::to_string(x);
		int left_index = 0;
		int right_index = temp.size() - 1;

		//check < vs <= later…
		while (left_index < right_index) {
			if(temp[left_index] != temp[right_index]) return false;
			left_index++;
			right_index --;
		}

		return true;
	}
};


int main()
{
	Solution s;
	s.isPalindrome(10101);

    std::cout << "Hello World!\n";
}