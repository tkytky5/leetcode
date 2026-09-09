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