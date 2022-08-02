#include <iostream>
#include <vector>
#include <queue>

/* https://leetcode.com/explore/learn/card/queue-stack/231/practical-application-queue/1374/
https://leetcode.com/problems/number-of-islands

PROBLEM: Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

CONSTRAINTS:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'
*/
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.size() <= 0) return 0;
        N = grid.size();
        M = grid[0].size();

        int result = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    dfs(grid, i, j);
                }   
            }
        }
        
        return result;
    }
private:
    void dfs(std::vector<std::vector<char>>& grid, int x, int y) {
        if (x < 0 || y < 0 || x >= N || y >= M || grid[x][y] != '1') {
            return;
        }

        grid[x][y] = '#'; //visited;
        dfs(grid, x, y + 1);
        dfs(grid, x, y - 1);
        dfs(grid, x + 1, y);
        dfs(grid, x - 1, y);
    }

    int N;
    int M;
};

//TODO - APPARENTLY THE BFS SOLUTION IS TOO SLOW....

class Solution2 {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.size() <= 0) return 0;
        int N = grid.size();
        int M = grid[0].size();

        int result = 0;
        std::queue<std::pair<int, int>> q; //store the coordinates of the next land tile

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    q.push(std::pair<int, int>(i, j));
                    while (!q.empty()) {
                        std::pair<int, int> current = q.front();
                        int x = current.first;
                        int y = current.second;
                        q.pop();
                        grid[x][y] = '#';

                        //up
                        int up = y - 1;
                        if (up >= 0 && grid[x][up] == '1') {
                            q.push(std::pair<int, int>(x, up));
                        }
                        //down
                        int down = y + 1;
                        if (down < M && grid[x][down] == '1') {
                            q.push(std::pair<int, int>(x, down));
                        }
                        //left
                        int left = x - 1;
                        if (left >= 0 && grid[left][y] == '1') {
                            q.push(std::pair<int, int>(left, y));
                        }
                        //right
                        int right = x + 1;
                        if (right < N && grid[right][y] == '1') {
                            q.push(std::pair<int, int>(right, y));
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main()
{
    Solution s;
    std::vector<std::vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    std::cout << s.numIslands(grid1) << std::endl;

    std::vector<std::vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    std::cout << s.numIslands(grid2) << std::endl;
}