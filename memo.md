問題：二分木の root から最も近いノードまでの長さを返す。

制約：
    ・ノードの数　0 ~ 10^5
    ・ノードの値　-1000 <= val <= 1000


step 1

Maximum Depth of Binary Tree を再帰で解いた方法を応用すればいけるかなと思ったが、
[3,9,20,null,null,15,7]
の対処法がわからず。

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        if (!root->left && !root->right) {
            return 1;
        }

        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};
```

再帰

自分のイメージしていた再帰と全く違った。
https://github.com/komdoroid/arai60/pull/18/changes#diff-65990e4dff3b722e23b9632d46b3b9bb15cdff3a4b474300b6a4f1eebb79bbf2
https://github.com/subaru-hello/leetcode-arai60/pull/23/changes

参考にしたリンク先で何故 maxDepth の方法で解けないのかとても親切に説明されたので理解できた。
上記コードで、min(minDepth(root->left), minDepth(root->right)) + 1 と書いたが、これだと left か right のどちらかのみを持つノードを葉ノードとしてしまう。片側が存在する場合片側だけを探索する工夫が必要。

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left_depth = minDepth(root->left);
        int right_depth = minDepth(root->right);

        if (left_depth == 0) {
            return right_depth + 1;
        }
        if (right_depth == 0) {
            return left_depth + 1;
        }

        return min(left_depth, right_depth) + 1;
    }
};
```

step 2

BFS

left と right が無い、leaf node を見つけたらその depth を返す。

https://github.com/komdoroid/arai60/pull/18/changes#diff-5e20e5b3b69314f48f7cc11ea69673219948fddd8991d015f35d45843d051bb7

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        queue<pair<TreeNode*, int>> next_nodes;
        next_nodes.emplace(root, 1);

        while (!next_nodes.empty()) {
            const auto [node, depth] = next_nodes.front();
            next_nodes.pop();

            if (!node->left && !node->right) {
                return depth;
            }

            if (node->left) {
                next_nodes.emplace(node->left, depth + 1);
            }
            if (node->right) {
                next_nodes.emplace(node->right, depth + 1);
            }
        }

        return 0;
    }
};
```

DFS

ノードの最大数が 10^5 なのでそれを max depth として、葉ノードの深度がそれよりも浅ければ更新
https://github.com/subaru-hello/leetcode-arai60/pull/23/changes

DFS の場合、必ず全てのノードを探索するため、葉ノードを見つけても他の葉ノードの方が浅い可能性があるのでBFSのようにその場で終了とはできない。BFSの方が効率が良いと思った。

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        stack<pair<TreeNode*, int>> next_nodes;
        next_nodes.emplace(root, 1);
        int min_depth = 10000;

        while (!next_nodes.empty()) {
            const auto [node, depth] = next_nodes.top();
            next_nodes.pop();

            if (!node->left && !node->right) {
                min_depth = min(min_depth, depth);
            }

            if (node->left) {
                next_nodes.emplace(node->left, depth + 1);
            }
            if (node->right) {
                next_nodes.emplace(node->right, depth + 1);
            }
        }

        return min_depth;
    }
};
```

step 3
再帰、DFS、BFSで3回連続 pass