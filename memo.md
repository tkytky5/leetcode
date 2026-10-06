# 102. Binary Tree Level Order Traversal

Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

### Constraints:
    - The number of nodes in the tree is in the range [0, 2000].
    - -1000 <= Node.val <= 1000



## step 1
各ノードとその階層を記憶すれば、外側の配列の何番目の配列に入れればいいかわかる。

家があって、それぞれの世代ごとに部屋を作ってあげて、各人を部屋に案内する。
ノードの順番は正確でないといけないので、stack、queue に投入する左右の順番に気をつける。

result.size() - 1 で - 1 を表現しようとするとマイナスオーバーフローになるのを気にしていなかった。
    size() は size_t 型。
    もうちょっと直感的な書き方をしたい。


- Time complexity: O(n)　<br>
- Space complexity: O(n) <br>
- Worst execution time: 2 ns <br>
    - 2000 / 10^8 = 0.000002 seconds = 0.002 ms = 2 ns

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }

        queue<pair<TreeNode*, int>> next_nodes;
        next_nodes.emplace(root, 0);
        while (!next_nodes.empty()) {
            const auto [node, level] = next_nodes.front();
            next_nodes.pop();

            if (level + 1 > result.size()) {
                vector<int> empty({node->val});
                result.push_back(empty);
            } else {
                result[level].push_back(node->val);
            }

            if (node->left) {
                next_nodes.emplace(node->left, level + 1);
            }
            if (node->right) {
                next_nodes.emplace(node->right, level + 1);
            }
        }

        return result;
    }
};
```

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }

        stack<pair<TreeNode*, int>> next_nodes;
        next_nodes.emplace(root, 0);
        while (!next_nodes.empty()) {
            const auto [node, level] = next_nodes.top();
            next_nodes.pop();

            if (level + 1 > result.size()) {
                vector<int> empty({node->val});
                result.push_back(empty);
            } else {
                result[level].push_back(node->val);
            }

            if (node->right) {
                next_nodes.emplace(node->right, level + 1);
            }
            if (node->left) {
                next_nodes.emplace(node->left, level + 1);
            }
        }

        return result;
    }
};
```

## step 2

level のスタートを 1 にすれば難しいことしなくて済む。

- https://discord.com/channels/1084280443945353267/1200089668901937312/1211248049884499988
    - 「level が nodes_ordered_by_level よりも大きい時、一段だけ拡張する」と書くと、「足りないことがあっても1段だけ」とその if だけでわかる。「level が nodes_ordered_by_level よりもいくらか大きい」と書くと、「足りないことがあっても1段だけ」と脳内デバッグするなど、他の箇所を読んで分かる。
    後者は読み手に無駄なパズルを解かせている。前者はとても自然な流れに感じる。
    - 内側の配列にノードの値を追加するのは配列を拡張する場合、しない場合どちらでも行うので。if else で分ける必要はない。拡張するかしないかのために if を使う。

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> nodes_ordered_by_level;
        if (!root) {
            return nodes_ordered_by_level;
        }

        queue<pair<TreeNode*, int>> next_nodes;
        next_nodes.emplace(root, 0);
        while (!next_nodes.empty()) {
            const auto [node, level] = next_nodes.front();
            next_nodes.pop();

            if (level == nodes_ordered_by_level.size()) {
                vector<int> empty;
                nodes_ordered_by_level.push_back(empty);
            }
            nodes_ordered_by_level[level].push_back(node->val);

            if (node->left) {
                next_nodes.emplace(node->left, level + 1);
            }
            if (node->right) {
                next_nodes.emplace(node->right, level + 1);
            }
        }

        return nodes_ordered_by_level;
    }
};
```


https://discord.com/channels/1084280443945353267/1196472827457589338/1196473479256625233
2重ループで BFS をすれば level を記憶しなくてよくなり、各階層をごとに走査するので配列のサイズが足りるか確認しなくて済む。こっちの方が今いる階層を考えなくて良いので思考回路がシンプルに感じる。

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        if (!root) {
            return answer;
        }
        vector<TreeNode*> current_level({root});
        while (!current_level.empty()) {
            vector<TreeNode*> next_level;
            vector<int> values;
            for (auto node : current_level) {
                values.push_back(node->val);
                if (node->left) {
                    next_level.push_back(node->left);
                }
                if (node->right) {
                    next_level.push_back(node->right);
                }
            }
            answer.push_back(values);
            current_level = next_level;
        }
        return answer;
    }
};
```

step 3
3回連続 pass

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        if (!root) {
            return answer;
        }
        vector<TreeNode*> current_level;
        while (!current_level.empty()) {
            vector<TreeNode*> next_level;
            vector<int> values;
            for (const auto node : current_level) {
                values.push_back(node->val);
                if (node->left) {
                    next_level.push_back(node->left);
                }
                if (node->right) {
                    next_level.push_back(node->right);
                }
            }
            answer.push_back(values);
            current_level = next_level;
        }
        return answer;
    }
};
```