# 53. Maximum Subarray

与えられた配列から合計値が最も大きい部分配列を返す。

- Constraints:
    - 1 <= nums.length <= 10^5
    - -10^4 <= nums[i] <= -10^4

## step 1
前から順番に走査していき、部分配列に後続の要素を一つずつ追加して、その合計値が既出の最大値よりも大きければ更新する方針にした。
DP 的な考え方はできなかった。

- [-2,1] のケースで、1 ではなく -1 となる。
    - 部分配列の長さが1つのときに対応できていない。
    
10分経過したので答えを見る。

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