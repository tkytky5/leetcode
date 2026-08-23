head = [1,1,2,3,3]
Output = [1,2,3,3]
Expected = [1,2,3]

末尾の重複を除けず10分経つ

leftとrightを見比べて同じ値ならrightのnextをleftのnextにすればいいかなと思ったが末尾で重複を排除するケースに対応できなかった。
あと、重複したときrightをright->nextにするとleftと同じ位置になってしまうのが後から気づいた。
```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* left = head;
        ListNode* right = head->next;

        while (right->next != nullptr) {
            if (left->val == right->val) {
                left->next = right->next;
            }

            left = left->next;
            right = right->next;
        }

        return head;
    }
};
```

解答を見る
わざわざleftとrightを作る必要はなく、変数一つで済んだ

言語化する
現在のノードと次のノードの値をを見比べ、同じであれば現在の次の次のノードを現在のノードの次にする。
このケースでcurrを進めない理由は次の次のノードも値が同じ可能性があり、進んでしまうと重複が残ってしまうため。
ex. [1, 1, 1, 2]
index1の除き、currを勧めるとcurrがindex2に移動し、index0と3の重複が残ったままになる。

逆に重複していない場合はcurrを進める。

Time complexity: O(n)
Space complexity: O(1)
```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;

        while (curr && curr->next) {
            if (curr->val == curr->next->val) {
                curr->next = curr->next->next;
            } else {
                curr = curr->next;
            }
        }

        return head;
    }
};
```

別の方のコードを参考にした。
変数名currは「たくさんあるものの中から切り替える」使い方のイメージが強い
ただ変数名に絶対的なよしあしはないみたいなのであまり深く考えないようにする
```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node = head;

        while (node && node->next) {
            if (node->val == node->next->val) {
                node->next = node->next->next;
            } else {
                node = node->next;
            }
        }
        return head;
    }
}


step 4

重複したノードをdeleteし忘れメモリリークを起こしている指摘を受け、deleteする

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node = head;

        while (node && node->next) {
            if (node->val == node->next->val) {
                ListNode* duplicate = node->next;
                node->next = node->next->next;
                delete duplicate;
            } else {
                node = node->next;
            }
        }
        return head;
    }
};
```