step 1

各配列の値の出現を記録し、お互いを照らし合わせて合致する値であれば結果用配列に追加する。
9分ほどで pass

map のキーが出現したかどうかを表し、値に出現回数を記録する必要はないが何を置くのがいいか分からずとりあえずインクリメントした。

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		map<int, int> num_to_1;
		map<int, int> num_to_2;

		for (const int& num : nums1) {
			num_to_1[num]++;
		}

		for (const int& num : nums2) {
			num_to_2[num]++;
		}

		vector<int> result;
		for (auto& [num, _] : num_to_1) {
			if (num_to_2.contains(num)) {
				result.push_back(num);
			}
		}

		return result;
    }
};
```

もう一つ思いついた。

map の構築の計算量（時間ではなく空間の計算量と認識しているが自信はない）は定数時間なので上記コードとあまり優劣はなさそうなので、可読性で言えば上記の方が「各入力値を見比べている」という意図が伝わりやすいと思った。
https://cpprefjp.github.io/reference/map/map/op_constructor.html


nums1、nums2 どちらにも存在する、尚且つ、nums2 で1回目の出現である場合結果リストに記録し、回数をインクリメントして条件に合致しないよう重複を防止。

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> num_to_frequent;

        for (const auto& num : nums1) {
            num_to_frequent[num] = 0;
        }

        vector<int> result;
        for (const auto& num : nums2) {
            if (num_to_frequent.contains(num) && num_to_frequent[num] == 0) {
                result.push_back(num);
                num_to_frequent[num]++;
            }
        }

        return result;
    }
};
```

step 2

他の人のコードを読む。

「最悪でも1000要素、ワーストでも1000 * 1000 = 10^6オーダーステップなのでC++なら問題ない」
C++ で 10^6 なら問題はないとなる根拠がわからなかったので教えてもらえると助かります。。。
https://github.com/chryschron/codings/pull/13

erase で intersection な値を消す発想がなかった。

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> nums1_set(nums1.begin(), nums1.end());

        vector<int> intersection;
        for (const auto& num : nums2) {
            if (nums1_set.erase(num)) {
                intersection.push_back(num);
            }
        }

        return intersection;
    }
};
```


step 3 
3回連続10分以内に解く。