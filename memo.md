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

stackを使った方法
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