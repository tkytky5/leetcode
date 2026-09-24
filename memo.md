# 617. Merge Two Binary Trees

https://leetcode.com/problems/merge-two-binary-trees/description/


## step 1

入力を上書きする方法として root1 を元に root2 を重ねる方法と、新しいツリーを作る方法を思いつき、再帰で解くイメージをしてみたが分からず回答を参考にした。

https://github.com/MA-yo-TA/leetcode/pull/23

書かなくてもいいが、root1 と root2 どちらも null の時は nullptr を返すことを宣言的に書いた方が挙動をイメージしやすいと思った。

### 新しいツリーを作る方法

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) {
            return nullptr;
        }

        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        TreeNode* node = new TreeNode(root1->val + root2->val);

        node->left = mergeTrees(root1->left, root2->left);
        node->right = mergeTrees(root1->right, root2->right);

        return node;
    }
};
```

### 上書きする方法
入力の書き換えは呼び出し側から扱いづらい気がするので、コメントを明記しておいた方が親切。理由がなければ使いたくないが、入力が使い捨て前提ならメモリ使用量を減らせそうなので一応選択肢として持っておく。

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) {
            return nullptr;
        }

        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;
    }
};
```

## step 2

C++ のスタックサイズは 1MB みたい。(https://discord.com/channels/1084280443945353267/1235829049511903273/1236256946403807323)
1 スタックフレームのサイズは 112 bytes
112 * 2000 = 224000 bytes = 0.224 MB
なのでスタックオーバーフローの心配はない？計算に自信はない。

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        TreeNode* left = mergeTrees(root1->left, root2->left);
        TreeNode* right = mergeTrees(root1->right, root2->right);
        int val = root1->val + root2->val;
        TreeNode* node = new TreeNode(val, left, right);

        return node;
    }
};
```

## step 3
3回連続10分以内に pass

## step 4
- ダブルポインターで解く方法
    https://discord.com/channels/1084280443945353267/1262688866326941718/1297934906189549599
    https://github.com/irohafternoon/LeetCode/pull/26/changes#r2056392034

    
    ダブルポイントという発想自体がなかった。もう少し詳しく調べておきたい。
    irohafternoon さんのコードを使わせてもらった。
    再帰のようにスタックオーバーフローの心配をしなくても良さそう。それ以外にメリット（デメリット）があるのかはわからない。

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        std::queue<std::tuple<const TreeNode*, const TreeNode*, TreeNode**>> nodes_to_merge;
        TreeNode* new_head = new TreeNode();
        nodes_to_merge.emplace(root1, root2, &new_head);

        while (!nodes_to_merge.empty()) {
            auto [node1, node2, ptr_to_merged_node] = nodes_to_merge.front();
            nodes_to_merge.pop();

            if (!node1 && !node2) {
                *ptr_to_merged_node = nullptr;
                continue;
            }
            if (!node1) {
                node1 = kSentinel;
            }
            if (!node2) {
                node2 = kSentinel;
            }

            (*ptr_to_merged_node)->val = node1->val + node2->val;
            (*ptr_to_merged_node)->left = new TreeNode();
            nodes_to_merge.emplace(node1->left, node2->left, &((*ptr_to_merged_node)->left));
            (*ptr_to_merged_node)->right = new TreeNode();
            nodes_to_merge.emplace(node1->right, node2->right, &((*ptr_to_merged_node)->right));
        }

        return new_head;
    }

private:
    static const TreeNode* const kSentinel;
};

const TreeNode* const Solution::kSentinel = new TreeNode(0);
```