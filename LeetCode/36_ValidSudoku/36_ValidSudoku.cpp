#include <iostream>
#include <vector>

/* https://leetcode.com/explore/learn/card/hash-table/185/hash_table_design_the_key/1126/
https://leetcode.com/problems/valid-sudoku/

PROBLEM: Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example1:

Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true

Example 2:

Input: board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

CONSTRAINTS:
    board.length == 9
    board[i].length == 9
    board[i][j] is a digit 1-9 or '.'
*/

class MySudokuHashSet {
public:
    MySudokuHashSet() {
        //initialize the values in the hashtable.
        for (int i = 0; i < 9; i++) {
            hashset[i] = 0;
        }
    }
    ~MySudokuHashSet() { }
    bool exists(char c) {
        if (hashset[hash_function(c)] > 0) {
            return true;
        }

        return false;
    }
    void insert(char c) {
        hashset[hash_function(c)] = (int)(c - '0'); //store the actual value
    }

private:
    int hashset[9];
    int hash_function(char value) {
        return value - '1'; //0 indexed
    }
};

class Sudoku {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        MySudokuHashSet rows[9];
        MySudokuHashSet columns[9];
        MySudokuHashSet sections[9];

        for (int i = 0; i < board.size(); i++) { //rows            
            for (int j = 0; j < board[i].size(); j++) { //columns
                if (board[i][j] == '.') continue;

                if (rows[i].exists(board[i][j]))
                {
                    return false;
                }
                else {
                    rows[i].insert(board[i][j]);
                }

                if (columns[j].exists(board[i][j]))
                {
                    return false;
                }
                else {
                    columns[j].insert(board[i][j]);
                }

                if (sections[get_section(i, j)].exists(board[i][j]))
                {
                    return false;
                }
                else {
                    sections[get_section(i, j)].insert(board[i][j]);
                }
            }
        }

        return true;
    }
private:
    int get_section(int x, int y) {
        //i'm sure there is a clever math function i could use to calculate this...
        if (0 <= x && x <= 2)
        {
            if (0 <= y && y <= 2)
            {
                return 0;
            }
            else if (3 <= y && y <= 5)
            {
                return 3;
            }
            else if (6 <= y && y <= 8)
            {
                return 6;
            }
        }
        else if (3 <= x && x <= 5)
        {
            if (0 <= y && y <= 2)
            {
                return 1;
            }
            else if (3 <= y && y <= 5)
            {
                return 4;
            }
            else if (6 <= y && y <= 8)
            {
                return 7;
            }
        }
        else if (6 <= x && x <= 8)
        {
            if (0 <= y && y <= 2)
            {
                return 2;
            }
            else if (3 <= y && y <= 5)
            {
                return 5;
            }
            else if (6 <= y && y <= 8)
            {
                return 8;
            }
        }
        return -1;
    }
};

int main()
{
    Sudoku s;

    std::vector<std::vector<char>> board1{
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'}
        ,{'6', '.', '.', '1', '9', '5', '.', '.', '.'}
        ,{'.', '9', '8', '.', '.', '.', '.', '6', '.'}
        ,{'8', '.', '.', '.', '6', '.', '.', '.', '3'}
        ,{'4', '.', '.', '8', '.', '3', '.', '.', '1'}
        ,{'7', '.', '.', '.', '2', '.', '.', '.', '6'}
        ,{'.', '6', '.', '.', '.', '.', '2', '8', '.'}
        ,{'.', '.', '.', '4', '1', '9', '.', '.', '5'}
        ,{'.', '.', '.', '.', '8', '.', '.', '7', '9'} };

    bool answer1 = s.isValidSudoku(board1);

    std::cout << answer1 << std::endl;

    std::vector<std::vector<char>> board2{
        { '8', '3', '.', '.', '7', '.', '.', '.', '.' }
        ,{'6', '.', '.', '1', '9', '5', '.', '.', '.'}
        ,{'.', '9', '8', '.', '.', '.', '.', '6', '.'}
        ,{'8', '.', '.', '.', '6', '.', '.', '.', '3'}
        ,{'4', '.', '.', '8', '.', '3', '.', '.', '1'}
        ,{'7', '.', '.', '.', '2', '.', '.', '.', '6'}
        ,{'.', '6', '.', '.', '.', '.', '2', '8', '.'}
        ,{'.', '.', '.', '4', '1', '9', '.', '.', '5'}
        ,{'.', '.', '.', '.', '8', '.', '.', '7', '9'} };

    bool answer2 = s.isValidSudoku(board2);

    std::cout << answer2 << std::endl;
}