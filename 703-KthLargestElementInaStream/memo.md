step 1
解法が思いつかず時間切れ。


step 2

priority_queueというコンテナアダプターの存在を知る。優先順位付きキューが実現できる。

コンストラクタ、addメソッド共に、キューに値を追加し、サイズを超過していたらpopで最小値を除去。

1探索ごとに対象の配列のサイズが1/2になる（2^n）ので O(log k)
コンストラクタは上記を配列の要素数分繰り返すので O(n log k)
- Time complexity
  - KthLargest(): O(n log k)

  - add(): O(log k)

- Space complexity
  O(k)

```c++
class KthLargest {
    int number;
    priority_queue<int, vector<int>, greater<int>> pq;
public:
    KthLargest(int k, vector<int>& nums) {
        number = k;
        for (auto element : nums) {
            pq.push(element);
            if (pq.size() > k) 
                pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > number) pq.pop();
        return pq.top();
    }
};
```

step 3

変数名を整える。

```c++
class KthLargest {
    int kthLargest;
    priority_queue<int, vector<int>, greater<int>> largestNumbers;

public:
    KthLargest(int k, vector<int> nums) {
        kthLargest = k;
        for (int element : nums) {
            largestNumbers.push(element);
            if (largestNumbers.size() > kthLargest) largestNumbers.pop();
        }
      }

    int add(int val) {
        largestNumbers.push(val);
        if (largestNumbers.size() > kthLargest) largestNumbers.pop();
        return largestNumbers.top();
    }
};
```