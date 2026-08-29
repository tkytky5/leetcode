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