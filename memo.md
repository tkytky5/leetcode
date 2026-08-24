step 1

入力のリストをスタックに積んで、頭から取り出して連結させれば逆順にできると思った。
10分でpassする。
arai60を始めて、初めて解答を見ずにpassできた。

後半のwhileで新規ノードを作成せずに、既存のノードのnextだけを変えることができればメモリ消費を抑えることができそうだなと思ったが、時間がなかったので雑ではあるがこのコードになった。

stackにListNodeを入れるだけでよかった。
ListNodeをstackに入れた場合、reverseしたリストの末尾のnextをnullptrにしていないため最後にエラーになる

Time complexity: O(n)
Space complexity: O(n)

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<int> values;

        while (head) {
            values.push(head->val);
            head = head->next;
        }

        if (values.empty()) {
            return head;
        }

        ListNode dummyHead(-1);
        ListNode* tail = &dummyHead;
        while (!values.empty()) {
            ListNode* newNode = new ListNode(values.top());
            tail->next = newNode;
            tail = tail->next;

            values.pop();
        }
        return dummyHead.next;
    }
};
```


step 2

解答を見る

two pointerのアプローチ

temporaryに次のノードのアドレスを確保しておき、currentの矢印の向きを逆にする。
previousを進める処理とcurrentを進める処理の順番に間違えると、previousがcurrentの位置に来てしまうので注意。

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current) {
            ListNode* temporary = current->next;
            current->next = previous;

            previous = current;
            current = temporary;
        }

        return previous;
    }
};
```

step 3

再帰のパターンも学んでおく

逆順リストの先頭を返すためにnewHeadを返し続ける。
現在のheadの一つ先のノードのnextを現在のheadに向ける。
head->nextをnullptrにしておくことで循環を防ぐ。


```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) 
            return head;

        ListNode* newHead = reverseList(head->next);

        ListNode* tail = head->next;
        tail->next = head;
        head->next = nullptr;

        return newHead;
    }
};
```