# 108. Convert Sorted Array to Binary Search Tree
https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

昇順ソートの配列から、子ノードの高さが同じの二分木を返す。

## step 1

配列の真ん中のノードを root として、両端に向かって進みノードを繋げる。
子ノード値が親ノードの値よりも小さければ left 、大きければ right に繋げる。left と right の両方に子ノードができることはない。

Input: [-10,-3,0,5,9]
Output: [0,-3,5,-10,9]
Expect: [0,-3,9,-10,null,5]

なぜか Output に null が入ってくれない。

Time compelxity: O(n) \
Space compelxity: O(n) \
実行時間：10^4 / 10^8 = 100 μs \
参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324

```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        const auto middle_index = nums.size() / 2;
        TreeNode* head = new TreeNode(nums[middle_index]);
        queue<TreeNode*> next_nodes;
        next_nodes.emplace(head);

        int left = middle_index - 1;
        int right = middle_index + 1;
        while(!next_nodes.empty()) {
            TreeNode* node = next_nodes.front();
            next_nodes.pop();
            if (left >= 0) {
                if (node->val < nums[left]) {
                    node->right = new TreeNode(nums[left]);
                    next_nodes.emplace(node->right);
                } else {
                    node->left = new TreeNode(nums[left]);
                    next_nodes.emplace(node->left);
                }
                left--;
            }
            if (right < nums.size()) {
                if (node->val < nums[right]) {
                    node->right = new TreeNode(nums[right]);
                    next_nodes.emplace(node->right);
                } else {
                    node->left = new TreeNode(nums[right]);
                    next_nodes.emplace(node->left);
                }
                right++;
            }
        }

        return head;
    }
};
```

# step 2

再帰

https://github.com/chryschron/codings/pull/23/changes#diff-f7c6af35bcdd057ca61181420371bb8207c1a370906d070e19f7026b11a451f2R5-R14

Time compelxity: O(n) \
Space compelxity: O(n) \
実行時間：10^4 / 10^8 = 100 μs \
参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324

```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedSubArrayToBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* sortedSubArrayToBST(vector<int>& nums, int begin, int end) {
        if (begin > end) {
            return nullptr;
        }

        int middle = (begin + end) / 2;
        TreeNode* node = new TreeNode(
            nums[middle],
            sortedSubArrayToBST(nums, begin, middle - 1),
            sortedSubArrayToBST(nums, middle + 1, end)
        );
        
        return node;
    }
};

```

スタック

https://github.com/chryschron/codings/pull/23/changes#diff-f7c6af35bcdd057ca61181420371bb8207c1a370906d070e19f7026b11a451f2R5-R14

計算量、実行時間は再帰と同じ

ダブルポインタ、この前まで難しく感じていたが、わからなくても良いから 写経 -> 3回見ずに書く をしたら頭の中がスッキリして理解できた気がする。

```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = nullptr;
        stack<tuple<TreeNode**, int, int>> node_subarray({{&root, 0, nums.size() - 1}});

        while (!node_subarray.empty()) {
            auto [node_ptr, begin, end] = node_subarray.top();
            node_subarray.pop();

            if (begin > end) {
                *node_ptr = nullptr;
                continue;
            }

            int middle = (begin + end) / 2;
            *node_ptr = new TreeNode(nums[middle]);
            node_subarray.push({&((*node_ptr)->right), middle + 1, end});
            node_subarray.push({&((*node_ptr)->left), begin, middle - 1});
        }

        return root;
    }
};
```

## step 3
3回連続 pass

## step 4
ダブルポインタを避けて、tuple を struct に変えた書き方。
struct 名もう少しいい名前があるはずだが思いつかない。

```c++
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = new TreeNode();
        Node* node = new Node(root, 0, nums.size() - 1);
        stack<Node*> nodes({node});

        while (!nodes.empty()) {
            auto node = nodes.top();
            nodes.pop();
            TreeNode* current_node = node->node;
            int begin = node->begin;
            int end = node->end;

            int mid_index = (begin + end) / 2;
            current_node->val = nums[mid_index];
            if (begin <= mid_index - 1) {
                current_node->left = new TreeNode();
                Node* node_left = new Node(current_node->left, begin, mid_index - 1);
                nodes.emplace(node_left);
            }
            if (mid_index + 1 <= end) {
                current_node->right = new TreeNode();
                Node* node_right = new Node(current_node->right, mid_index + 1, end);
                nodes.emplace(node_right);
            }
        }

        return root;
    }

private:
    struct Node {
        TreeNode* node;
        int begin;
        int end;
    };
};
```