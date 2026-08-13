step1

・各リストの値を配列に変換
・forループで要素を合算
・合算値を10で割り、余りで新しいノードを作成

末尾のノードから作成するので、nextに連結できない。
ここでギブアップ。

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* current1 = l1;
        std::vector<int> array1 = {};
        while (current1) {
            array1.push_back(current1->val);
            current1 = current1->next;
        }
        ListNode* current2 = l2;
        std::vector<int> array2 = {};
        while (current2) {
            array2.push_back(current2->val);
            current2 = current2->next;
        }

        int sum1 = 0;
        for (int i = sizeof(array1) -1 ; i >= 0; i--) {
            sum1 += array1[i];
        }
        int sum2 = 0;
        for (int i = sizeof(array2) -1 ; i >= 0; i--) {
            sum2 += array2[i];
        }

        int total = sum1 + sum2;

        while (total > 0) {
            total = total / 10;
            ListNode* node = new ListNode(total % 10, nullptr);
        }
    }
};
```

step2

解答を見る。

dummyHeadで最後のノード、つまり最終的なリストのheadの参照を保持しておく。
tailは逆順のリストの末尾になる。
carryは、各ノードの値を足して繰り上がった値（10の位）を保持して次のループで2つのノードの値と合算する。

l1、l2のどちらも末尾まで達するまで、且つ、繰り上げ値が存在する限りループを回す。

上記3つを足し合わせ、新しいノードを作り、リストに連結する。

Time complexity: O(max(N, M)) (N, Mは、l1とl2のListNodeのそれぞれの長さ)
Space complexity: O(1)

参考にした解答では、
・l.74
carray != 0　だったが、繰り上げ値があれば(1以上)trueにするなら ">" にした方がすんなり伝わると思い変更。


```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode();
        ListNode* tail = dummyHead;
        int carry = 0;

        while (l1 || l2 || carry > 0) {
            int digit1 = l1 ? l1->val : 0;
            int digit2 = l2 ? l2->val : 0;

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};
```

step3

dummyHeadはヒープメモリに確保する必要はないのでスタティックメモリに確保。

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummyHead(-1);
        ListNode* tail = &dummyHead;
        int carry = 0;

        while (l1 || l2 || carry > 0) {
            int digit1 = l1 ? l1->val : 0;
            int digit2 = l2 ? l2->val : 0;

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = new ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;
    }
};
```