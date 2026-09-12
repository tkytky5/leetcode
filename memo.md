step 1

具体的な方法が思いつかずギブアップ。

参考
https://github.com/colorbox/leetcode/pull/31/changes/BASE..68e00411964489033b4e936e38ca08c80a3a1abd

各要素をチェックしたか記憶するために同じサイズ表を複製。
「端から順番に各座標が島か海か確認し、島であればその隣接の座標が地続きになっているか更に確認」、を陸と海の境界点まで、つまり海か座標外が見つかるまで再帰的に繰り返す。

Time complexity: O(mn)
Space complexity: O(mn)

実行時間：90000 / 10^8 = 0.0009 seconds
参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        height = grid.size();
        width = grid.front().size();
        visited = vector<vector<bool>>(height, vector<bool>(width, false));
        int island_count = 0;

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (grid.at(row).at(col) == see || visited.at(row).at(col)) {
                    continue;
                }

                walkThroughIsland(row, col, grid);
                ++island_count;
            }
        }

        return island_count;
    }

private:
    const char see = '0';
    int width, height;
    vector<vector<bool>> visited;

    struct Coordinate {
        int row;
        int col;
    };

    void walkThroughIsland(int row, int col, const vector<vector<char>>& grid) {
        stack<Coordinate> next_coordinates;
        next_coordinates.emplace(row, col);

        while (!next_coordinates.empty()) {
            const auto coordinate = next_coordinates.top();
            next_coordinates.pop();

            if (coordinate.row < 0 || coordinate.row >= height || coordinate.col < 0 || coordinate.col >= width) {
                continue;
            }

            if (grid.at(coordinate.row).at(coordinate.col) == see || visited.at(coordinate.row).at(coordinate.col)) {
                continue;
            }

            visited.at(coordinate.row).at(coordinate.col) = true;
            next_coordinates.emplace(coordinate.row + 1, coordinate.col);
            next_coordinates.emplace(coordinate.row - 1, coordinate.col);
            next_coordinates.emplace(coordinate.row, coordinate.col + 1);
            next_coordinates.emplace(coordinate.row, coordinate.col - 1);
        }
    }
};
```

step 2

コードを整える

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        height = grid.size();
        width = grid.front().size();
        visited = vector<vector<bool>>(height, vector<bool>(width, false));
        int island_count = 0;

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (grid.at(row).at(col) == see || visited.at(row).at(col)) {
                    continue;
                }

                walkThroughIsland(row, col, grid);
                ++island_count;
            }
        }

        return island_count;
    }

private:
    const char see = '0';
    int width, height;
    vector<vector<bool>> visited;

    struct Coordinate {
        int row;
        int col;
    };

    void walkThroughIsland(int row, int col, const vector<vector<char>>& grid) {
        stack<Coordinate> next_coordinates;
        next_coordinates.emplace(row, col);

        while (!next_coordinates.empty()) {
            const auto coordinate = next_coordinates.top();
            next_coordinates.pop();
            int row = coordinate.row;
            int col = coordinate.col;

            if (row < 0 || row >= height || col < 0 || col >= width) {
                continue;
            }

            if (grid.at(row).at(col) == see || visited.at(row).at(col)) {
                continue;
            }

            visited.at(row).at(col) = true;
            next_coordinates.emplace(row + 1, col);
            next_coordinates.emplace(row - 1, col);
            next_coordinates.emplace(row, col + 1);
            next_coordinates.emplace(row, col - 1);
        }
    }
};
```

step 3

- メンバー変数を関数のローカル変数に変更し予期せぬ問題発生の可能性を回避。
    「メンバー変数を書き換える関数は、複数スレッドから呼び出された際に競合を生み、意図しない結果の返却やクラッシュ、クラッシュによるプロセス終了のリスクがあります。今回の実装では、状態をクラス内に持たせるよりも、関数引数として引き回す設計のほうが安全性とスレッド独立性の点で優れていると思います。」
    https://github.com/5ky7/arai60/pull/22#discussion_r2567812904


- 変数名の修正

- vector<bool> -> vector<uint8_t> に変更
    vector<bool>は通常の vector<T> と挙動が異なり、動作が複雑になったり、オーバーヘッドが発生する可能性がある。
    https://github.com/nicah4o/arai60/pull/18#discussion_r3297492842

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int num_rows = grid.size();
        int num_cols = grid.front().size();
        visited = vector<vector<uint8_t>>(num_rows, vector<uint8_t>(num_cols));
        int island_count = 0;

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col <　num_cols; ++col) {
                if (grid[row][col] == see || visited[row][col]) {
                    continue;
                }

                walkthroughIsland(
                    row,
                    col,
                    grid,
                    num_rows,
                    num_cols
                );
                ++island_count;
            }
        }

        return island_count;
    }

private:
    const char see = '0';
    vector<vector<uint8_t>> visited;

    struct Coordinate {
        int row;
        int col;
    };

    void walkthroughIsland(
        int row,
        int col,
        vector<vector<char>>& grid,
        int num_rows,
        int num_cols
    ) {
        stack<Coordinate> coordinates_to_visit;
        coordinates_to_visit.emplace(row, col);

        while (!coordinates_to_visit.empty()) {
            const auto [row, col] = coordinates_to_visit.top();
            coordinates_to_visit.pop();

            if (!(0 <= row && row < num_rows && 0 <= col && col < num_cols)) {
                continue;
            }

            if (grid[row][col] == see || visited[row][col]) {
                continue;
            }

            visited[row][col] = 1;
            coordinates_to_visit.emplace(row + 1, col);
            coordinates_to_visit.emplace(row - 1, col);
            coordinates_to_visit.emplace(row, col + 1);
            coordinates_to_visit.emplace(row, col - 1);
        }
    }
};
```