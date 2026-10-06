# 103. Binary Tree Zigzag Level Order Traversal

### Constraints
The number of nodes in the tree in the range [0, 2000]. <br>
-100 <= Node.val <= 100 <br>

## step 1 
階層毎に左から走査するか右から走査するか決めるために現在地の level が偶数か奇数で判断する。

[1,2,3,4,null,null,5] のケースで通らない。
3 -> 2 と入れた後に 3 の子ノードから先に実行される。2 の子ノードを先頭に割り込ませたい。

- Time complexity: O(n)　<br>
- Space complexity: O(n) <br>
- Worst execution time: 2 ns <br>
    - 2000 / 10^8 = 0.000002 seconds = 0.002 ms = 2 ns

```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        if (!root) {
            return answer;
        }
        queue<pair<TreeNode*, int>> node_to_level({{root, 0}});
        bool from_left = true;
        while (!node_to_level.empty()) {
            const auto [node, level] = node_to_level.front();
            node_to_level.pop();
            if (level == answer.size()) {
                vector<int> empty;
                answer.push_back(empty);
            }
            answer[level].push_back(node->val);
            if (level % 2 == 0) {
                if (node->right) {
                    node_to_level.emplace(node->right, level + 1);
                }
                if (node->left) {
                    node_to_level.emplace(node->left, level + 1);
                }
            } else {
                if (node->left) {
                    node_to_level.emplace(node->left, level + 1);
                }
                if (node->right) {
                    node_to_level.emplace(node->right, level + 1);
                }
            }
        }
        return answer;
    }
};
```

## step 2

https://github.com/MA-yo-TA/leetcode/pull/27/changes#diff-63db05f4fe42d2f40c1405f62f20042c53977a1224d26b5c4655ccbb48e63022

フラグで配列を反転させるので、子の順番を気にする必要がない。

```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> values_by_level;
        if (!root) {
            return values_by_level;
        }
        vector<TreeNode*> nodes({root});
        bool is_left_to_right = true;
        while (!nodes.empty()) {
            vector<int> values;
            vector<TreeNode*> next_level;
            for (const auto node : nodes) {
                values.push_back(node->val);
                if (node->left) {
                    next_level.push_back(node->left);
                }
                if (node->right) {
                    next_level.push_back(node->right);
                }
            }
            if (!is_left_to_right) {
                std::reverse(values.begin(), values.end());
            }
            is_left_to_right = !is_left_to_right;
            values_by_level.push_back(values);
            nodes = next_level;
        }
        return values_by_level;
    }
};
```

## step 3
3回連続 pass