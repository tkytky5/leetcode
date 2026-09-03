step 1

単純に配列を一つずつループし、各要素との組み合わせの合計が k と等しければカウント。
最初、累積和が k を超えた、もしくは k と等しい時、それ以降の計算ステップを減らす目的でその時点で次のループに移動（break）していたが以降の値がマイナスだったら累積我が k と等しくなり得ることを考慮できていなかった。
制約をきちんと読むように気をつける。
30分程で pass

Space complexity: O(1)
Time complexity: O(n^2)

実行時間見積り： 4 seconds
    n = 2 * 10^4 = 20000
    n^2 = 400000000
    c++ の秒間ステップ数　10^8

    400000000 / 10^8 = 4

    参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324


```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int total_number = 0;

        for (int i = 0; i < nums.size(); ++i) {
            int current_total = 0;

            for (int j = i; j < nums.size(); ++j) {
                current_total += nums[j];
                if (current_total == k) {
                    total_number++;
                }
            }
        }

        return total_number;
    }
};
```