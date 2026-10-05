# 112. Path Sum
二分木の root から leaf までの合計値が targetSum に等しい道のり？（ path ）があれば true 、そうでなければ false を返す。


## step 1
DFS で解いた。13 分で pass 。

BFS より DFS の方が各終端に辿り着くのが速いので早く見つかるケースが多そう。

各ノードの値を合算していき、子ノードがない、かつ、targetSum に等しければ true

tuple の要素が2つの場合 pair も考えたが、どのように使い分けるべきか調べてみたが、オーバーヘッドやメモリ使用量に関しては見つからなかった。同じ構造で複数回使うなら struct の方が良さそう。

Time complexity: O(n)
Space complexity: O(n)
実行時間: 5000 / 10^8 = 0.000005 seconds = 0.05 ms = 50 ns

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }

        stack<tuple<TreeNode*, int>> node_to_sum({{root, 0}});

        while (!node_to_sum.empty()) {
            auto [node, val] = node_to_sum.top();
            node_to_sum.pop();

            if (!node) {
                continue;
            }

            val += node->val;
            if (!node->left && !node->right && val == targetSum) {
                return true;
            }

            node_to_sum.emplace(node->right, val);
            node_to_sum.emplace(node->left, val);
        }

        return false;
    }
};
```

BFS
```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }

        queue<tuple<TreeNode*, int>> node_to_sum({{root, 0}});

        while (!node_to_sum.empty()) {
            auto [node, val] = node_to_sum.front();
            node_to_sum.pop();

            if (!node) {
                continue;
            }

            val += node->val;
            if (!node->left && !node->right && val == targetSum) {
                return true;
            }

            node_to_sum.emplace(node->right, val);
            node_to_sum.emplace(node->left, val);
        }

        return false;
    }
};
```

## step 2

https://github.com/MA-yo-TA/leetcode/pull/25
- 再帰の場合、ノードが一直線だった場合最大 5000 なので注意が必要。Python は再帰呼び出し上限は 1000 回。C++ の場合は固定値ではなく、コールスタックのメモリサイズ（ 1MB 〜 8MB ）によって決まる。

if (!root->left && !root->right && remainder == 0) よりも if (!root->left && !root->right) の方が末端での関数呼び出しを 1 回減らせるので良いと思った。

```c++
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }

        int remainder = targetSum - root->val;
        if (!root->left && !root->right) {
            return remainder == 0;
        }

        return hasPathSum(root->left, remainder) || hasPathSum(root->right, remainder);
    }
};
```

## step 3
3 回連続 pass