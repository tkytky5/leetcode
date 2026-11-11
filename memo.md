# 198. House Robber
強盗として金をむす無計画をしている。通りの複数の家は一定の金を隠し持っており、隣接する家には防犯システムがあり、連続する2つの家が侵入されると自動で通報されるのが制約である。
配列から通報されずに盗める最大の金額を返す。

- Constraints:
    - 1 <= nums.length <= 100
    - 0 <= nums[i] <= 400

# step 1
- 奇数番目、偶数番目でそれぞれ合算していき最後に比較して大きい方を返せばいいか。
    - WA
        - [2, 1, 1, 2] は [2, 2] が最大値なのでこれではダメ。
    - 考えられるテストケースを可能な限り列挙する癖を持つようにする。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int left = 0;
        int right = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) {
                right += nums[i];
            } else {
                left += nums[i];
            }
        }

        return std::max(left, right);
    }
};
```

## step 2
わからないので他の方のコードを見る。

- https://github.com/skypenguins/coding-practice/pull/45/changes
- https://github.com/Shunii85/arai60/pull/35/changes
    - ひとつ前時点での最大値を覚えておいて、現在の値と2つ前の値の合算値の大きい方を最大値とする。
    - 今回は空配列が来ても対処できるので、空チェックは必要なさそう。

- Time complexity: O(n)
- Space complexity: O(1)

DP
```c++
class Solution {
public:
    int rob(vectuor<int>& nums) {
        int max_without_prev_house = 0;
        int max = 0;

        for (const auto money : nums) {
            int robbed = max_without_prev_house + money;
            max_without_prev_house = max;

            max = std::max(max, robbed);
        }
        
        return max;
    }
};
```

- https://github.com/Mike0121/LeetCode/pull/47/
    - メモ化再帰
    - フィボナッチ数列
    - 後ろから最大値を探索する

- Time complexity: O(n)
- Space complexity: O(n)

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        unordered_map<int, int> memo;

        return robHelper(0, nums, memo);
    }

private:
    int robHelper(
        int i,
        vector<int>& nums,
        unordered_map<int, int>& memo
    ) {
        if (i >= nums.size()) {
            return 0;
        }

        if (memo.find(i) != memo.end()) {
            return memo[i];
        }

        int max_value = std::max(
            nums[i] + robHelper(i + 2, nums, memo),
            robHelper(i + 1, nums, memo)
        );

        memo[i] = max_value;
        return max_value;
    }
};
```

## step 3
DP メモ化再帰でそれぞれ3回連続 pass