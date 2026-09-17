root という binary tree が与えられ、最大の深さを返す。
binary tree の最大の深さとは、root　から leaf node までが最も長い道にあるノードの数である。

step 1

再帰的に関数を実行し、＋1カウントし続ける方法を考えたが、具体的な再帰の条件がわからずコードが浮かばなかった。

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        return maxDepthHelper(root, 1);
    }

private:
    int maxDepthHelper(TreeNode* node, int count) {
        if (node == nullpt) {

        }

        if (root->left == nullptr) {
            return 1;
        }
    }
};
```

わからないので解答を見る。

https://github.com/subaru-hello/leetcode-arai60/pull/22/changes

DFSを使った方法
親ノードに子ノードが存在すれば　stack に投入しノードがある限り続ける。

max 関数は複数の枝で深さが異なる時に、浅い方の深さが最大深度を上書きしないために必要。
例：root = [3,9,20,null,null,15,7]
    root から3の枝、20の枝と左->右の枝の順に探索すると、20の枝の葉（末端）まで調べた後、葉9を調べる時、葉9の深度は1のため最大深度3よりも小さいので更新したくない。

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        stack<pair<TreeNode*, int>> nodes_to_visit;
        int max_depth = 1;
        nodes_to_visit.emplace(root, max_depth);

        while (!nodes_to_visit.empty()) {
            const auto [node, depth] = nodes_to_visit.top();
            nodes_to_visit.pop();
            max_depth = max(max_depth, depth);

            if (node->left != nullptr) {
                nodes_to_visit.emplace(node->left, depth + 1);
            }

            if (node->right != nullptr) {
                nodes_to_visit.emplace(node->right, depth + 1);
            }
        }

        return max_depth;
    }
};
```

BFS

deque を使って上から順に一層ずつ探索していく。

https://github.com/attractal/leetcode/pull/30/changes

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        deque<TreeNode*> level_node;
        level_node.push_back(root);
        int depth = 0;

        while (!level_node.empty()) {
            int level_size = level_node.size();
            ++depth;

            for (int i = 0; i < level_size; ++i) {
                TreeNode* node = level_node.front();
                level_node.pop_front();

                if (node->left != nullptr) {
                    level_node.push_back(node->left);
                }
                if (node->right != nullptr) {
                    level_node.push_back(node->right);
                }
            }
        }

        return depth;
    }
};
```

step 2

queue でも対応できそう。deque だと以下の用途でも使用できるが、今回は範囲外のため必要最低限の queue に変更。
https://github.com/dxxsxsxkx/leetcode/pull/21/changes

deque シーケンスは以下の特徴を持つ。
    - 個々の要素はその位置インデックスによってアクセスできる
    - 要素のイテレーションは任意の順序で実行することができる
    - 要素はいずれの橋（シーケンスの先端または最後）からも効率よく追加・削除される
https://cpprefjp.github.io/reference/deque/deque.html


```cpp
class Solution {
public:
    /**
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     * };
     */

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<TreeNode*> next_nodes;
        next_nodes.emplace(root);

        int depth = 0;

        while (!next_nodes.empty()) {
            int n_next_nodes = next_nodes.size();
            ++depth;

            for (int i = 0; i < n_next_nodes; ++i) {
                TreeNode* current_node = next_nodes.front();
                next_nodes.pop();

                if (current_node->left) {
                    next_nodes.emplace(current_node->left);
                }
                if (current_node->right) {
                    next_nodes.emplace(current_node->right);
                }
            }
        }

        return depth;
    }
};
```

再帰でも解いておく。
記述量が少ないので書きやすい。

```cpp
class Solution {
public:
    /**
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;   
     *     TreeNode *right;
     *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     *     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
     * };
     */

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

step 3
DFS、BFS、再帰でそれぞれ3回連続10分以内に pass