# 53. Maximum Subarray

与えられた配列から合計値が最も大きい部分配列の合計値を返す。

- Constraints:
    - 1 <= nums.length <= 10^5
    - -10^4 <= nums[i] <= 10^4

## step 1
前から順番に走査していき、部分配列に後続の要素を一つずつ追加して、その合計値が既出の最大値よりも大きければ更新する方針にした。
DP 的な考え方はできなかった。

- [-2,1] のケースで、1 ではなく -1 となる。
    - 部分配列の長さが1つのときに対応できていない。

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        int max = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            vector<int> temp_arr({nums[i]});
            for (int j = i + 1; j < nums.size(); j++) {
                temp_arr.push_back(nums[j]);
                int sum = sumArry(temp_arr);
                if (max < sum) {
                    max = sum;
                }
            }
        }

        return max;
    }

private:
    int sumArry(vector<int>& nums) {
        int sum = 0;
        for (const auto num : nums) {
            sum+=num;
        }
        return sum;
    }
};
```

10分経過したので答えを見る。

- https://github.com/chryschron/codings/pull/30
    > std::numeric_limits::min() を使用することをお勧めいたします。
    - 一つ前までの合計値が正の値であれば現在の要素を加算（部分配列の要素と）する。そうでなければ現在の値を合計値（部分配列の先頭）とする。subarray_sums はその時点までの合計値を表すので、その中から最も大きい要素が最大値の部分配列であり、最大値を表す。
    - Space complexity: O(n)
        - 
    - Time complexity: O(n)
        - 10^5 / 10^8 = 1ms

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> subarray_sums(nums.size());
        subarray_sums[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (subarray_sums[i - 1] < 0) {
                subarray_sums[i] = nums[i];
            } else {
                subarray_sums[i] = subarray_sums[i - 1] + nums[i];
            }
        }

        return *std::max_element(subarray_sums.begin(), subarray_sums.end());
    }
};
```

なぜこのコードが正しいのかちゃんと理解できていない。特に if の部分が説明できない。

コメント集を読む。
- https://discord.com/channels/1084280443945353267/1206101582861697046/1207405733667410051
    - 愚直に部分配列を全て紙に書き出してみた。全部で15通りある。
    - コードに変換する
        ```c++
            class Solution {
            public:
                int maxSubArray(vector<int>& nums) {
                    int max = 0;
                    for (int i = 0; i < nums.size(); i++) {
                        for (int j = i; j < nums.size(); j++) {
                            int current_sum = sumSubArray(nums, i, j);
                            max = std::max(max, current_sum);
                        }
                    }
                    return max;
                }

            private:
                int sumSubArray(vector<int>& nums, int i, int j) {
                    int sum = nums[i];
                    for (int i = i; i < j; i++) {
                        sum += nums[i];
                    }
                    return sum;
                }
            };
        ```


