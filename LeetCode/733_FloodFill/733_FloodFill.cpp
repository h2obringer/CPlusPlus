#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/239/conclusion/1393/
https://leetcode.com/problems/flood-fill

PROBLEM: An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.
You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image[sr][sc].
To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with color.
Return the modified image after performing the flood fill.

Example 1:
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.

Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation: The starting pixel is already colored 0, so no changes are made to the image.

CONSTRAINTS:
    m == image.length
    n == image[i].length
    1 <= m, n <= 50
    0 <= image[i][j], color < 216
    0 <= sr < m
    0 <= sc < n
*/

//Causes a timeout...
class Solution {
private:
	int rowCount = 0;
	int colCount = 0;
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
		rowCount = image.size();
		if(rowCount == 0) return image;
		colCount = image[0].size();
		
		queue<pair<int, int>> q;
		q.push(pair<int, int> (sr, sc));

		int oldColor = image[sr][sc];

		while (!q.empty()) {
			int row = q.front().first;
			int col = q.front().second;
			q.pop();

			if (row >= 0 && row < rowCount && col >= 0 && col < colCount && image[row][col] == oldColor) {
				image[row][col] = color;

				q.push(pair<int, int>(row, col - 1));
				q.push(pair<int, int>(row, col + 1));
				q.push(pair<int, int>(row - 1, col));
				q.push(pair<int, int>(row + 1, col));
			}
		}

		return image;
	}
};

//DFS Solution - causes stack overflow...
class Solution2 {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
		int oldColor = image[sr][sc];
		if (oldColor == color) return image; //no work to be done...
		vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size(), false));

		floodFill(image, sr, sc, oldColor, color, visited);

		return image;
	}

	void floodFill(vector<vector<int>>& image, int sr, int sc, int oldcolor, int newcolor, vector<vector<bool>>& visited) {
		if (image[sr][sc] == oldcolor && !visited[sr][sc]) {
			visited[sr][sc] = true;
			image[sr][sc] = newcolor;
			if (sc > 0) floodFill(image, sr, sc - 1, oldcolor, newcolor, visited);
			if (sc + 1 < image.size()) floodFill(image, sr, sc + 1, oldcolor, newcolor, visited);
			if (sr > 0) floodFill(image, sr - 1, sc, oldcolor, newcolor, visited);
			if (sr + 1 < image[0].size()) floodFill(image, sr + 1, sc, oldcolor, newcolor, visited);
		}
	}
};

//helper
void print(vector<vector<int>> image) {
	for (int row = 0; row < image.size(); row++) {
		for (int col = 0; col < image[0].size(); col++) {
			cout << image[row][col] << " ";
		}
		cout << endl;
	}
}

int main()
{
	Solution s;
	vector<vector<int>> image1 = { {0, 0, 0},{0, 0, 0} };
	
	print(s.floodFill(image1, 1, 0, 2));
}