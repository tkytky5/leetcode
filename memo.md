step 1

大まかな流れ
1. 未探索の島（1）を見つける
2. 島のサイズを調べる
3. 探索済みの島のサイズより大きいか比べる

27分でpass

Space complexity: O(mn)
Time complexity: O(mn)
Estimated execution Time: 0.000025 seconds
参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324


```cpp
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int num_rows = grid.size();
        int num_cols = grid.front().size();
        visited = vector<vector<int>>(num_rows, vector<int>(num_cols));
        int max_area = 0;

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                if (grid[row][col] == see || visited[row][col]) {
                    continue;
                }

                int island_size = getIslandArea(row, col, grid, num_rows, num_cols);
                if (max_area < island_size) {
                    max_area = island_size;
                }
            }
        }

        return max_area;
    }

private:
    const int see = 0;
    vector<vector<int>> visited;

    struct Coordinate {
        int row;
        int col;
    };

    int getIslandArea(
        int row,
        int col,
        vector<vector<int>>& grid,
        int num_rows,
        int num_cols
    ) {
        stack<Coordinate> coordinates_to_visit;
        coordinates_to_visit.emplace(row, col);

        int island_size = 0;

        while (!coordinates_to_visit.empty()) {
            const auto [row, col] = coordinates_to_visit.top();
            coordinates_to_visit.pop();

            if (!(0 <= row && row < num_rows && 0 <= col && col < num_cols)) {
                continue;
            }

            if (grid[row][col] == see || visited[row][col]) {
                continue;
            }

            ++island_size;
            visited[row][col] = 1;
            coordinates_to_visit.emplace(row + 1, col);
            coordinates_to_visit.emplace(row - 1, col);
            coordinates_to_visit.emplace(row, col + 1);
            coordinates_to_visit.emplace(row, col - 1);
        }

        return island_size;
    }
};
```


step 2

- const int -> static constexpr
    const にするとクラスのインスタンスごとに別々のインスタンスが生成され無駄にメモリを消費するため、 static でプロセス中は共有しメモリ節約。また、コンパイル時に計算することで実行速度を改善。
    https://github.com/chryschron/codings/pull/18#discussion_r3511855566

- visited は int -> uint8_t にサイズダウンしても問題なさそう。

```cpp
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int num_rows = grid.size();
        const int num_cols = grid.front().size();
        visited = vector<vector<uint8_t>>(num_rows, vector<uint8_t>(num_cols));
        int max_area = 0;

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                if (grid[row][col] == see || visited[row][col]) {
                    continue;
                }

                const auto island_area = getIslandArea(
                    row,
                    col,
                    grid,
                    num_rows,
                    num_cols
                );

                if (max_area < island_area) {
                    max_area = island_area;
                }
            }
        }

        return max_area;
    }

private:
    static constexpr int see = 0;
    vector<vector<uint8_t>> visited;

    struct Coordinate {
        int row;
        int col;
    };

    int getIslandArea(
        int row,
        int col,
        vector<vector<int>>& grid,
        int num_rows,
        int num_cols
    ) {
        stack<Coordinate> coordinates_to_visit;
        coordinates_to_visit.emplace(row, col);
        int island_area = 0;

        while (!coordinates_to_visit.empty()) {
            const auto [row, col] = coordinates_to_visit.top();
            coordinates_to_visit.pop();

            if (!(0 <= row && row < num_rows && 0 <= col && col < num_cols)) {
                continue;
            }

            if (grid[row][col] == see || visited[row][col]) {
                continue;
            }

            ++island_area;
            visited[row][col] = 1;
            coordinates_to_visit.emplace(row + 1, col);
            coordinates_to_visit.emplace(row - 1, col);
            coordinates_to_visit.emplace(row, col + 1);
            coordinates_to_visit.emplace(row, col - 1);
        }

        return island_area;
    }
};
```

step 3
3回連続 pass