# 62. Unique Paths
https://leetcode.com/problems/unique-paths/description/

縦 m x 横 n のグリッド上の左上にいるロボットが右下に行くための道筋が何通りあるかを返す。ロボットは右か下にだけ動く。
テストケースは答えが 2 * 10^9 以下に作られている。

Constraints:
    - 1 <= m, n <= 100

## step 1

TLE
```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m < 0 || n < 0) {
            return 0;
        }

        int unique_paths = 0;

        queue<pair<int, int>> next_coordinates;
        next_coordinates.push({0, 0});
        while (!next_coordinates.empty()) {
            auto [down, right] = next_coordinates.front();
            next_coordinates.pop();

            if (down == m - 1 && right == n - 1) {
                unique_paths+=1;
            }

            if (down < m) {
                next_coordinates.push({down + 1, right});
            }
            if (right < n) {
                next_coordinates.push({down, right + 1});
            }
        }

        return unique_paths;
    }
};
```

32分くらい。
手作業でやることをコンピューターにお願いする意識で考えた。
(0, 0) から右または下に1マスずつ移動した先が右隅にいるかを確認する。


- Time complexity: O(2^m+n)

- Space complexity: O(2^m+n)

他の方の step 1 をいくつか読んでいて、自分だけ思考回路がずれている気がした。DP 的な考え方ができていないと思う。

- https://github.com/miyataka/coding-practice/pull/31
    step 1 参考
    
```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> path_nums(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    path_nums[i][j] = 1;
                    continue;
                }

                int top = 0;
                int left = 0;
                if (i > 0) {
                    top = path_nums[i - 1][j];
                }

                if (j > 0) {
                    left = path_nums[i][j - 1];
                }

                path_nums[i][j] = top + left;
            }
        }

        return path_nums[m - 1][n - 1];
    }
};
```
一つ前（上）の場所までの道のりの数 + 一つ前（左）の場所までの道のりの数  = 現在地までの道のりの数
こっちの方が素直な考え方に感じる。

Time complexity: O(mn)
    10^4 / 10^8 = 0.4 ms
Space complexity: O(mn)
    10^4 * 4 = 40KB