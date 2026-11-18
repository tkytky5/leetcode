# 213. House Robber II

通りの家に強盗を企てている。各家には幾らかのお金がある。家の並びは円状になっており、先頭の家は末尾の家の隣を意味する。
各家は両隣の家と防犯システムが繋がっており、一夜に連続する家に強盗が入ると通報されるようになっている。
各家にあるお金を示す与えられた整数値の配列から、通報されずに盗める最大の金額を返す。

- Example 1:
    - Input: nums = [2, 3, 2]
    - Output: 3
    - Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

- Example 2:
    - Input: nums = [1, 2, 3, 1]
    - Output: 4
    - Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3). Total amount you can rob = 1 + 3 = 4.

- Example 3:
    - Input: nums = [1, 2, 3]
    - Output: 3

- Constraints:
    - 1 <= nums.length <= 100
    - 0 <= nums[i] <= 1000


## step 1
198. House Robber の解法を応用すれば解けそう。ただ結果に先頭と末尾の両方が含まれていることを検知する方法が思いつかない。
15分たったので答えを見る。


## step 2
- https://github.com/miyataka/coding-practice/pull/34/changes
    - 入力から先頭を除いた配列と末尾を除いた配列からそれぞれ最大値を算出し、最後に両者を見比べる。
    - 先頭や末尾を除外する発想はなかった。こうすることで結果に先頭と末尾が含まれる可能性を排除できる。

- Time complexity: O(n)
    - 100 μs オーダー
- Space complexity: O(n)

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        vector<int> without_first(nums.begin() + 1, nums.end());
        vector<int> without_end(nums.begin(), nums.end() - 1);

        return std::max(
            robHelper(without_first),
            robHelper(without_end)
        );
    }

private:
    int robHelper(vector<int>& nums) {
        vector<int> memo(nums.size() + 2);

        for (int i = 2; i < memo.size(); i++) {
            memo[i] = std::max(
                memo[i - 2] + nums[i - 2],
                memo[i - 1]
            );
        }

        return memo[memo.size() - 1];
    }
};
```

- https://github.com/MA-yo-TA/leetcode/pull/35 step 4
    - 配列のサイズは変えずに変数で1つ前、2つ前の最大値を記憶している。こっちの方が2つ前までの値しか記憶しないのでメモリサイズは少ないし、読みやすいので良いコードに思う。
- https://github.com/chryschron/codings/pull/34
    - 入力じゃなくて関数を2つ作る方法。
    - prev1, prev2 という命名がとても読みやすくしている気がした。関数を2つ書くのは少し冗長に感じる。
- https://github.com/TakayaShirai/leetcode_practice/pull/35/changes
    - step 2 の解説がすごくわかりやすい。House Robber を基準に考える際、条件がどう変わっていて、それを取り除く方法が丁寧に言語化されている。
    - >「未知のものは何か」、「与えられているものは何か」、「条件は何か」を意識するのは、どんな問題を解く上でもやはり重要
        - 参考にしたいと思う。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        if (nums.size() == 2) {
            return std::max(nums[0], nums[1]);
        }

        vector<int> without_head(nums.begin() + 1, nums.end());
        vector<int> without_tail(nums.begin(), nums.end() - 1);

        return std::max(
            robHelper(without_head),
            robHelper(without_tail)
        );
    }

private:
    int robHelper(vector<int>& houses) {
        int previous_max = houses[0];
        int current_max = std::max(houses[0], houses[1]);

        for (int i = 2 ; i < houses.size(); i++) {
            int next_max = std::max(previous_max + houses[i], current_max);
            previous_max = current_max;
            current_max = next_max;
        }

        return current_max;
    }
};
```

## step 3
3回連続 pass