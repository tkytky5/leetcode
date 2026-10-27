# 300. Longest Increasing Subsequence
https://leetcode.com/problems/longest-increasing-subsequence/

入力の配列から最も長い昇順にソートされた部分配列の長さを返す。配列の要素は削除してもいいが並び替えることはできない。

## step 1
10分経ってもわからないので答えを見る。

- 入力の配列から厳密（もう少し良い表現があるはず）に昇順に並んだ最も長い配列を返す。
厳密とは、次の値が現在の値よりも大きいかつ、最も近い値を指す。
    - 正: [1, 3, 2, 4] -> [1, 2, 4]
    - 誤: [1, 3, 2, 4] -> [1, 3, 4]

- current が next よりも
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

解けそうにないので答えを見る。

- https://github.com/miyataka/coding-practice/pull/29
    > 整数配列 nums を受け取り、**狭義単調増加**（strictly increasing）な部分列のうち最長のものの**長さ**を int で返す。部分列（subsequence）は、元の配列から要素を削除して（残った要素の順序は変えずに）作れる列のこと。連続している必要はない。

    - strictly increasing のことを **狭義単調増加** というらしい
        
- https://github.com/skypenguins/coding-practice/pull/50
    - その時点での結果を情報として持っておく
    - 最小の部分配列の長さは 1 なので、調査用配列を要素全てを 1 で初期化
    - 時間計算量: O(n^2)
        - n = 2500 の場合、ステップ数: n(n-1) / 2 から 3,123,750 ステップ。C++ の実行時間: 10^8 ステップ/秒とすると、およそ 31 ms
    - 空間計算量: O(n)
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        vector<int> LIS_length(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    LIS_length[i] = std::max(LIS_length[j] + 1, LIS_length[i]);
                }
            }
        }

        return *std::max_element(std::begin(LIS_length), std::end(LIS_length));
    }
};
```

## step 2

- 典型コメント集: https://discord.com/channels/1084280443945353267/1200089668901937312/1209563502407065602
    - 自分の左側にあって、末尾が自分より小さい LIS の中で最大長のものを探し出す。
        ```
        [2, 6, 8, 4, 5, 1] という配列があったとして、
        i = 2 のとき、
        パターン1 [2]
        パターン2 [2, 6] <- LIS

        パターン2が上の条件に当てはまり、その長さと自分を足せば自分の LTS がわかる。
        lis_length = [1, 2, 3, 1, 1, 1]
        ```
    - 内側のループを関数にすることで、関数名から lis_lengths が何を表すかが推測しやすい。
    - 確かに関数に切り出すと処理が想像しやすいと思った。
    
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        vector<int> lis_lengths(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            lis_lengths[i] = getMaxLISLengthBeforeIndex(i, nums, lis_lengths) + 1;
        }
        
        return *std::max_element(std::begin(lis_lengths), std::end(lis_lengths));
    }

private:
    int getMaxLISLengthBeforeIndex(
        int right,
        vector<int>& nums,
        vector<int>& lis_lengths
    ) {
        int max_length = 0;

        for (int i = 0; i < right; i++) {
            if (nums[i] < nums[right]) {
                max_length = std::max(max_length, lis_lengths[i]);
            }
        }

        return max_length;
    }
};
```

## step 3
3回連続で pass