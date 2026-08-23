step 1

12分くらいで解く。

各単語をアルファベット順にソートしてやれば同じ anagram なので、それをキーにすればグルーピングできる。
最後にグルーピングした各要素を配列に移し替える。

文字列をソートする方法がわからなかったので調べながら解いた。

map の変数名で良いのが思いつかなかったので雑になってしまった。

map のループ変数でキーは使わないので element.second の方がいいと思った。

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> ordered_words;

        for (string str : strs) {
            string coppied_str = str;
            sort(str.begin(), str.end());

            if (ordered_words.contains(str)) {
                ordered_words[str].push_back(coppied_str);
            } else {
                ordered_words[str] = {coppied_str};
            }
        }

        vector<vector<string>> result;
        for (auto [ordered, words] : ordered_words) {
            result.push_back(words);
        }

        return result;
    }
};
```

step2（整形＆他の人のコードを読む）

他の人のコードを参考にする。
https://leetcode.com/problems/group-anagrams/solutions/6113105/video-create-keys-for-group-of-strings-2-tqdx/
    - グループの要素数が0の時、1以上の時で if で条件分岐させずにどちらの場合でも push_back で対応できた。

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> anagram_groups;

        for (const auto& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            anagram_groups[key].push_back(str);
        }

        vector<vector<string>> result;
        for (const auto& entry : anagram_groups) {
            result.push_back(entry.second);
        }

        return result;        
    }
};
```

step3（10分以内にさっとかける * 3回）