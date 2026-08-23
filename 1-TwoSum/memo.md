step 1

map を使い、key に target から num[i] を引いた値を、value に index を保存して、nums の後続の要素とキーが一致すればその時点の index と value の配列を返せばいいと考えた。
if の条件のエラー解決できずタイムアップ。

result は定義せず return で配列を作ってそのまま返すべきだった。
一回の for ループで、出現した値とインデックスの記録と、補数が map に存在するかの確認を同時にやろうとして頭の中で整理できずに書いてしまった。


```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> result;
        for (int i = 0; i < nums.size(); i++) {
            if (result.find(nums[i]) && result.find(nums[i])->first == nums[i]) {
                return vector<int>{result[i], i};
            }
            result[i] = target - nums[i];
        }
    }
};
```

step 2

他の人の回答を見る。
map の key に値、value に index を格納する。
nums から補数と同じキーの要素がないか、且つ、現在の index が map の自分自身を指していないかチェック。

```c++
class Solution {
public:
	vector<int> twoSum(vector<int> nums, int target) {
		unordered_map<int, int> hash;
		for (int i = 0; i < nums.size(); i++) {
			hash[nums[i]] = i;
		}

		for (int i = 0; i < nums.size(); i++) {
			int complement = target - nums[i];
			if (hash.find(complement) != hash.end() && hash[complement] != i) {
				return {i, num_to_index[complement]};
			}
		}

		return {};
	}
};
```

step 3

map型の変数名を (キー)_to_(値) に修正し中身がイメージできるようにする。

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> num_to_index;
		for (int i = 0; i < nums.size(); i++) {
			num_to_index[nums[i]] = i;
		}

		for (int i = 0; i < nums.size(); i++) {
			int complement = target - nums[i];
			if (num_to_index.find(complement) != num_to_index.end() && num_to_index[complement] != i) {
				return {i, num_to_index[complement]};
			}
		}

		return {};
	}
};
```

step 4

step 1 で一回の for ループで完結させる方法が見つかったので参考にする。
https://github.com/Apo-Matchbox/LeetCode_Practice/pull/23/changes

unordered_map は要素数が少ない時 map よりもメモリ使用量が大きく、insert() も map よりも遅いらしい。
https://github.com/Apo-Matchbox/LeetCode_Practice/pull/23#discussion_r2525525275

nums のループ内で要素とインデックスを記録する。もしくは target - nums[i] が既出であればそれが補数なので現在の値のインデックスとその補数となる値のインデックスを返す。

```c++
class Solution {
public:
	vector<int> twoSum(vector<int> nums, int target) {
		std::map<int, int> num_to_index;
		
		for (int i = 0; i < nums.size(); ++i) {
			int complement = target - nums[i];

			if (num_to_index.contains(complement)) {
				return {i, num_to_index[complement]};
			}
			
			num_to_index[nums[i]] = i;
		}

		return {};
	}
};
```
