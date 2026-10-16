問題: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

## step 1
入力の配列2つ（ preorder 、inorder ）から二分木を返す。
preorder と inorder の意味がわからなかったので調べた。
https://gink03.github.io/preorder%E3%81%A8inorder%E3%81%A8postorder/
https://github.com/Hiroto-Iizuka/coding_practice/pull/29/changes

- preorder:
    - Node -> Left -> Right
- inorder
    - Left -> Node -> Right
- postorder
    - Left -> Right -> Node
    - 戻りがけのスキャン

preorder は DFS で操作する方法。
inorder はまず root から leaf になるまで左に行った場所からスタート。left -> node -> right の順に見ていく。

ここからどうすればいいかわからなかった。preorder から二分木を作るメソッドを作って、inorder でもそうする？
10 分経っても方法が浮かばなかったので答えを見る。


https://github.com/goto-untrapped/Arai60/pull/53#discussion_r1777944717

そもそも二分木を作るためになぜ preorder と inorder の 2 つが必要なのか理解できなかったので、
- preorder だけで作れる二分木を列挙してみた。preorder: [1, 2, 3] inorder: [2, 1, 3]
    - [1, 2, 3, nullptr, nullptr]
    - [1, 2, nullptr, 3, nullptr]
    - [1, 2, nullptr, nullptr, 3, nullptr, nullptr]
    - [1, nullptr, 2, 3, nullptr]
    - [1, nullptr, 2, nullptr, 3]

これらの内どれかが正解になるということは、どれが正解か判断するために 子 node が nullptr か node か、がわからないといけない。inorder はそのために使用する。
inorder は preorder の先頭と同じ値が root になるので、それを境に左部分木、右部分木に分ける。

- preorder を見て、root が 1 になるのは分かったけど、
- root の左に何を置くのか？
    - inorder から root の左に [2] があるな。だから左に置く。
        - root が 2 の左に何を置くのか？
            - inorder の [2] の左はない。だから nullptr を置く。
        - root が 2 の右に何を置くのか？
            - inorder の [2] の右はない。だから nullptr を置く。
- root の右に何を置くのか？
    - inorder から root の右に [3] があるな。だから右に置く。
        - root が 3 の左に何を置くのか？
            - inorder の [3] の左はない。だから nullptr を置く。
        - root が 3 の右に何を置くのか？
            - inorder の [3] の右はない。だから nullptr を置く。
- [1, 2, nullptr, nullptr, 3, nullptr, nullptr] が答えになる。


https://github.com/nicah4o/arai60/pull/28/changes
自分の上の手順に近い形で理解しやすかった。
関数名は Helper を付けるなり違う方が読みやすい気がした。


```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        deque<int> preorder_deque({preorder(), preorder.end()});
        return buildTree(preorder_deque, inorder);
    }

private:
    TreeNode* buildTree(deque<int>& preorder, vector<int>& inorder) {
        if (inorder.empty()) {
            return nullptr;
        }
        int val = preorder.front();
        preorder.pop_front();
        TreeNode* root = new TreeNode(val);
        auto it = find(inorder.begin(), inorder.end(), val);
        int root_index = it - inorder.begin();
        vector<int> left_inorder(inorder.begin(), inorder.begin() + root_index);
        vector<int> right_inorder(inorder.begin() + root_index + 1, inorder.end());

        root->left = buildTree(preorder, left_inorder);
        root->right = buildTree(preorder, right_inorder);

        return root;
    }
};
```

## step 2
関数名に buildTreeHelper に変更
const にできそうな変数を変更。

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        deque<int> preorder_deque(preorder.begin(), preorder.end());
        return buildTreeHelper(preorder_deque, inorder);
    }

private:
    TreeNode* buildTreeHelper(deque<int>& preorder, vector<int>& inorder) {
        if (inorder.empty()) {
            return nullptr;
        }

        const int val = preorder.front();
        preorder.pop_front();
        TreeNode* root = new TreeNode(val);
        const auto it = find(inorder.begin(), inorder.end(), val);
        const int root_index = it - inorder.begin();
        vector<int> left_inorder(inorder.begin(), inorder.begin() + root_index);
        vector<int> right_inorder(inorder.begin() + root_index + 1, inorder.end());

        root->left = buildTreeHelper(preorder, left_inorder);
        root->right = buildTreeHelper(preorder, right_inorder);

        return root;
    }
};
```

結構苦戦してスタミナ切れなので他の回答は見ていない。

## step 3
3 回連続 pass