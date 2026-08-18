step 1

mapで各要素の頻度を記録する。その後頻度が高い順に取り出す方法が思いつかずギブアップ。
mapの書き方が分からずとりあえず適当に書いた。


```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        hashmap<int, int> frequent = {};
        for (int element : nums) {
            if (frequent.key(element)) {
                frequent[element] += 1;
            } else {
                frequent[element] = 0;
            }
        }
    }
};
```


step 2

他の人の解答を見る。
mapで頻度カウントし、優先度付きキューに頻度でソートされるように格納。
キューの要素の値から上位k個分を配列に格納。


```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        vector<int>ans;
        map<int,int>mpp;
        for(int i=0;i<nums.size();i++)
        {
            mpp[nums[i]]++;
        }
        priority_queue<pair<int,int>>pq;
        for(auto it:mpp)
        {
            pq.push({it.second,it.first});
        }
        while(k>0)
        {
            ans.push_back(pq.top().second);
            pq.pop();
            k--;
        }
        return ans;
    }
};
```


step 3

auto型にするメリットが分からなかったので明示的にpair型にする。
mapとキューの適切な変数名が思い浮かばなかったので型で区別した。
変数は使う直前に宣言した方がいつ使われるかわかりやすいと思う。

```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> frequent_map;
        for (int element : nums) {
            frequent_map[element]++;
        }

        priority_queue<pair<int, int>> frequent_queue;
        for (pair<int, int> element : frequent_map) {
            frequent_queue.push({element.second, element.first});
        }

        vector<int> result;
        while (k-- > 0) {
            result.push_back(frequent_queue.top().second);
            frequent_queue.pop();
        }

        return result;
    }
};
```