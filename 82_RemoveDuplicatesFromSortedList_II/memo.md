step 1

83. Remove Duplicates from Sorted Listの問題を応用して、値が重複したら同じようにnextに次のノードを入れ、異なれば追加でheadの位置も変えるようにすれば成功できると思った。

head = [1,2,3,3,4,4,5]
output = [5]
expected = [1,2,5]

これだと末尾以外のノードは全て削除されてしまう
10分経過

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
                ListNode* duplicate = node;
                node = node->next;
                head = node;
                delete duplicate;
            }
        }
        return head;
    }
}
```

step2

Time complexity: O(n)
Space complexity: O(1)

解答を見る。
2ポインタを使って値が一致しなくなるまで何もせずcurrentを進め、異なる値の時previous->nextをcurrentにすることで重複ノードが除外される。


さらに下記を拝見し、
https://github.com/denyaho/Leetcode_repository/pull/3
https://github.com/minsrd/arai60/pull/5

ifとelseの処理を入れ替えることでネストを一段浅くする。
dummyのインスタンス作成時valを-1としていたが、意味のある数字と勘違いしてしまう可能性を考慮して初期値としておく。

3回連続クリア

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* current = head;
        ListNode* previous = dummy;

        while (current && current->next) {
            if (current->val != current->next->val) {
                previous = previous->next;
                current = current->next;
                continue;
            }
            while (current->next && current->val == current->next->val) {
                ListNode* duplicate = current;
                current = current->next;
                delete duplicate;
            }
            ListNode* duplicate = current;
            previous->next = current->next;
            current = current->next;
            delete duplicate;
        }

        return dummy->next;
    }
};
```