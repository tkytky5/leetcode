# 300. Longest Increasing Subsequence
https://leetcode.com/problems/longest-increasing-subsequence/

入力の配列から最も長い昇順にソートされた部分配列の長さを返す。配列の要素は削除してもいいが並び替えることはできない。

## step 1
10分経ってもわからないので答えを見る。

- 入力の配列から厳密（もう少し良い表現があるはず）に昇順に並んだ最も長い配列を返す。
厳密とは、次の値が現在の値よりも大きいかつ、最も近い値を指す。
    - 正: [1, 3, 2, 4] -> [1, 2, 4]
    - 誤: [1, 3, 2, 4] -> [1, 3, 4]

- current が next よりも（ループ）
    - 小さい
        - result に current 追加
        - current を next へ
    - 大きい
        - result の最後尾 < ? < next の値をループで探す
            - 見つかったら、そこを current とする
- result のサイズを返す

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        vector<int> result;
        for (int i = 0; i < nums.size() - 1; i++) {
            auto current_val = nums[i];
            auto next_val = nums[i + 1];
            if (current_val < next_val) {
                result.push_back(current_val);
            } else {
                for (int j = i + 1; j < nums.size() - 1; j++) {
                    if (current_val <)
                }
            }
        }
    }
};
```

- https://github.com/miyataka/coding-practice/pull/29
    - > 整数配列 nums を受け取り、**狭義単調増加**（strictly increasing）な部分列のうち最長のものの**長さ**を int で返す。部分列（subsequence）は、元の配列から要素を削除して（残った要素の順序は変えずに）作れる列のこと。連続している必要はない。

        - strictly increasing のことを **狭義単調増加** というらしい
        

