141. Linked List Cycleのコードでfastとslowが一致した時のノードを返せばいいと思い実行。
問題文を勘違いしており、循環が始まったノードつまり最初に複数回参照されたノードを見つける必要があった。

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return slow;
            }
        }

        return nullptr;
    }
}
```


一致したら循環が始まったノードfast->nextを返したが、
head = [1,2]
pos = 0
で失敗
Output: index 1
Expected: index 0

このケースはfastを返したいが、条件分岐がわかならいのでギブアップ。
```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return fast->next;
            }
        }

        return nullptr;
    }
}
```

解答を見た。
解説を読んでも理解できなかったのでAIに聞くと

headから循環開始点までの距離を a
循環開始点から衝突地点までの距離を b
循環の残り（衝突地点から循環開始点に戻るまで）を c
このとき a = c + (fastの周回数-1)×循環長 という関係が成り立つため、headから1歩ずつ進むポインタと衝突地点から1歩ずつ進むポインタは、ちょうど循環の開始点で出会います。

と言われたが理解できない。
紙に書いてみた
   pos
1   2   3   4   5
s,f
    s   f
        s   f   
    f       s
            f   s
    s,f
sをheadにリセット
s   f
    s   f
    　　 s   f  
            s   f
    f           s
    s   f
        s   f
            s   f
    f           s

無限ループになってる？

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
}
```