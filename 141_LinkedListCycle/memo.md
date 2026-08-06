全くコードが浮かばなかったのでこちらの回答を参考にした。

時間計算量がO(n)になるのは、ifに合致せずslowがtailまで進むから。
空間計算量がO(1)の理由は。fastとslowの2つの変数が固定で使用され、変動しないから？（あんまり分かってないのでアドバイスお願いします）

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return true;
            }
        }
        return false;
    }
};
```