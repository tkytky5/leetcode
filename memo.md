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
