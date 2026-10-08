# 98. Validate Binary Search Tree


## step 1

[5,1,4,null,null,3,6] では通らない。通るはずと思ったが、問題をちゃんと読めていないのか。
いい加減再帰で自力で解けるようになりたい。

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root->left && !root->right) {
            return true;
        }
        if (root->left) {
            if (root->left->val < root->val) {
                isValidBST(root->left);
            } else {
                return false;
            }
        }
        if (root->right) {
            if (root->val < root->right->val) {
                isValidBST(root->right);
            } else {
                return false;
            }
        }
        return true;
    }
};
```

## step 2
回答見る。

https://github.com/kazukiii/leetcode/pull/29/changes#diff-041340df4abb911ffef1f86bd5e216ee5d252585f8ac00220a4ea7f78a03c7eb

再帰の深さの見積り参考になった。
- 自分の Mac のスタックメモリのサイズは 8MB、64 bit
- 各スタックのフレームサイズ
    -  引数
        - TreeNode* root: 8 bytes
        - long long lower: 8 bytes
        - long long upper: 8 bytes
    - local 変数
        - なし
    - その他
        - 戻りアドレス： 8 bytes
        - ベースポインタ： 8 bytes
    - 合計 40 bytes
- 最大で 8000000 / 40 = 2 * 10^5 くらいは大丈夫そう
- 制約はノード数が 10^4 なので、見積り場再起で書いても大丈夫

helper を呼び出す行が長いので改行。

Time complexity: O(n)
Space complexity: O(n)

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(
            root,
            numeric_limits<long long>::min(),
            numeric_limits<long long>::max()
        );
    }

private:
    bool isValidBSTHelper(TreeNode* root, long long lower, long long upper) {
        if (!root) {
            return true;
        }
        if (!(lower < root->val && root->val < upper)) {
            return false;
        }
        return isValidBSTHelper(root->left, lower, root->val) && isValidBSTHelper(root->right, root->val, upper);
    }
};
```

step 3
3 回連続 pass