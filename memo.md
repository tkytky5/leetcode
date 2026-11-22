# 121. Best Time to Buy and Sell Stock

要素 i が i 日目の株価を示す配列から、利益が最大になるように、購入日とそれ以降の売却日を選んで最大値を返す。もし利益がなければ0を返す。

- Example 1:
    - Input: prices = [7 ,1, 5, 3, 6, 4]
    - Output: 5
    - Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

- Example 2:
    - Input: prices = [7, 6, 4, 3, 1]
    - Output: 0
    - Explanation: In this case, no transactions are done and the max profit = 0.

- Constrains:
    - 1 <= prices.length <= 10^5
    - 0 <= prices[i] <= 10^4


## step 1
素朴に前から順番に n^2 ループで見ていくのは TLE になる。10^2 秒かかる。
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;

        for (int i = 0; i < prices.size(); i++) {
            for (int j = i + 1; j < prices.size(); j++) {
                max = std::max(max, prices[j] - prices[i]);
            }
        }

        return max;
    }
};
```

DP で考えてみる。紙に書いてみる。最小単位に分解して、最小値と最大値を記録しておく。一番小さな値を記憶しておけば以降の各日の最大利益がわかる。

- [7, 1]
    - min = 7 or 1 = 1
    - max = 0 or (1 - min) = 0

- [7, 1, 5]
    - min = min or 5 = 1
    - max = max or 4 = 4

- [7, 1, 5, 3]
    - min = min or 3 = 1
    - max = max or (3 - min) = 4

- [7, 1, 5, 3, 6]
    - min = min or 6 = 1
    - max = max or (6 - min) = 5

- [7, 1, 5, 3, 6, 4]
    - min = min or 4
    - max = max or (4 - min) = 5

30分くらいで pass

- Time complexity: O(n)
    - 10^5 / 10^8 = 1 ms
- Space complexity: O(1)
    - 4 * 3 bytes

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 1) {
            return 0;
        }

        int min = prices[0];
        int max = 0;
        for (int i = 1; i < prices.size(); i++) {
            min = std::min(min, prices[i]);

            max = std::max(max, prices[i] - min);
        }

        return max;
    }
};
```

## step 2
step 1 のコードで pass


- 他の人のコードを見る
    - https://github.com/miyataka/coding-practice/pull/35
        - ループのスタート地点が0でも解けるが、2日以上ないとこの問題は成り立たないので、自分は配列サイズが2未満なら早々に0を返したいし、読み手に無駄なパズルを解かせずに済むと思う。
    - https://github.com/tsadamor/Leetcode/pull/8/changes#diff-0c860cd754249868513e4f9054206317fa33d0f548fc3896ac2b3e11822fd852R53
        - 自分もシステムの最大値よりも、初日を最小値とした方が文脈が伝わりやすいかなと思った。
    - https://github.com/chryschron/codings/pull/35/changes
        - 　std::min() を使わないパターン。個人的には使った方がシンプルに描けるし読める気がする。


## step 3
3回連続 pass