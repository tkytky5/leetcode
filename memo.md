# 63. Unique Paths II

m x n の grid の左上から右下にロボットが進める道が何通りあるか。ロボットは下か右にのみ進める。
障害物があれば1、何もなければ0。障害物があれば進めない。

テストケースは回答が 2 * 10^9 になるように作られている。

- Constraints:
    - m == obstacleGrid.length
    - n == obstacleGrid[i].length
    - i <= m, n <= 100
    - obstacleGrid[i][j] is 0 or 1.


## step 1
30分くらいで pass

62. Unique Paths とほぼ同じ問題で解法を覚えていたのでそれをベースとして。異なるのは入力が1だった場合。
- 障害物があれば通れないから0に反転させれば、その右または下に行かせないようにできる。

- Example 1, 2 は15分くらいでクリアできたが、以下のケースの対処に時間をかけすぎた。
    - [[1]]
        - スタート地点は1にしないといけないので、その場合は条件で弾く
    - [[0], [1], [0], [0], ...]
        - 以下ケースの2つ目のように道が一方向にしかなく、障害物があった時点で探索を終了させたいが時間がなかったので放置。

if が多すぎて読みにくい。もっとシンプルにしたい。


Time complexity: O(mn)
    10^4 / 10^8 = 0.1 ms

Space complexity: O(mn)
    4 * 10^4 = 40KB

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1) {
            return 0;
        }

        for (int row = 0; row < rows; row++) {
            if (row == 0) {
                obstacleGrid[0][0] = 1;
            }
            for (int col = 0; col < cols; col++) {
                if (!(row == 0 && col == 0) && obstacleGrid[row][col] == 1) {
                    obstacleGrid[row][col] = 0;
                    continue;
                }
                int top = 0, left = 0;

                if (row > 0) {
                    top = obstacleGrid[row-1][col];
                }

                if (col > 0) {
                    left = obstacleGrid[row][col-1];
                }

                if (top + left > 0) {
                    if (obstacleGrid[row][col] == 1) {
                        obstacleGrid[row][col] = 0;
                    } else {
                        obstacleGrid[row][col] = top + left;
                    }
                }
            }
        }

        return obstacleGrid[rows-1][cols-1];
    }
};
```

## step 2

番兵使った方がシンプル。これは62. Unique Paths　でも書いていた。
障害物チェックの時に、 path_count は番兵配置によって全体のインデックスがずれているのでそこは注意が必要。

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int num_rows = obstacleGrid.size();
        int num_cols = obstacleGrid[0].size();
        vector<vector<int>> path_count(num_rows + 1, vector<int>(num_cols + 1, 0));

        path_count[1][0] = 1;
        for (int row = 1; row < num_rows + 1; row++) {
            for (int col = 1; col < num_cols + 1; col++) {
                if (obstacleGrid[row - 1][col - 1] == 1) {
                    path_count[row][col] = 0;
                } else {
                    path_count[row][col] = path_count[row - 1][col] + path_count[row][col - 1];
                }
            }
        }

        return path_count[num_rows][num_cols];
    }
};
```

- https://github.com/miyataka/coding-practice/pull/32
- https://github.com/MA-yo-TA/leetcode/pull/33/changes
    - OBSTACLE という定数を置けば読みやすい。
    - > 各マスへの行き方は、そのマスの上のマスへの行き方と左のマスへの行き方の合計であるが、ある行を計算し終わったとき、次の行の各マスにおいて、上のマスからの寄与は今保持している行そのもの。左からの分だけ計算すればいい。
        - ひとつ上のマスがわかっていれば、2つ上以降の行はいらない。確かに。

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        const int OBSTACLE = 1;
        int num_rows = obstacleGrid.size();
        int num_cols = obstacleGrid[0].size();

        if (obstacleGrid[num_rows - 1][num_cols - 1] == OBSTACLE) {
            return 0;
        }

        vector<int> path_count(num_cols, 0);
        path_count[0] = 1;

        for (int row = 0; row < num_rows; row++) {
            for (int col = 0; col < num_cols; col++) {
                if (obstacleGrid[row][col] == OBSTACLE) {
                    path_count[col] = 0;
                    continue;
                }

                if (col > 0) {
                    path_count[col] += path_count[col - 1];
                }
            }
        }

        return path_count[num_cols - 1];
    }
};
```