step 1

単純に配列を一つずつループし、各要素との組み合わせの合計が k と等しければカウント。
最初、累積和が k を超えた、もしくは k と等しい時、それ以降の計算ステップを減らす目的でその時点で次のループに移動（break）していたが、　以降の値がマイナスだったら累積和が k と等しくなり得ることを考慮できていなかった。
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


step 2

他の人の回答を見る。

https://discord.com/channels/1084280443945353267/1206101582861697046/1208414507735453747

理解できたような気がするしできてないような気もするがとりあえず言語化してみる。

値の数だけ駅があり、値を標高とする。一駅ごとに標高差を記録していく。
最初に標高 0 をカウントするのは地表が基準となるため。
現在地の駅から標高差がちょうど k の場所に駅がある組み合わせを調べる。


```cpp
class Solution {
public:
    int subarraySum(vector<int> nums, int k) {
        unordered_map<int, int> elevation_to_frequence;
        int difference = 0;
        int count = 0;
        elevation_to_frequence.insert({0:1});
        
        for (const auto elevation : nums) {
            difference += elevation;
            if (elevation_to_frequence.contains(elevation - k)) {
                count += elevation_to_frequence[elevation - k];
            }

            elevation_to_frequence[elevation] += 1;
        }

        return count;
    }
};
```


step 3
3回連続10分以内に pass

step 4
バグ修正

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> elevation_to_frequency = {{0, 1}};
        int sum = 0;
        int difference = 0;

        for (const auto elevation : nums) {
            difference += elevation;
            sum += elevation_to_frequency[difference - k];
            elevation_to_frequency[difference]++;
        }

        return sum;
    }
};
```