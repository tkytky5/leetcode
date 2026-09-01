step 1

map で各文字とカウントを記録し、文字列を先頭から走査してカウントが1のインデックスを返す。

Time complexity: O(n)
Space complexity: O(n)

処理時間: 10^5 / 10^8 = 0.001 sec
参考：https://github.com/Yuto729/leetcode/pull/16#discussion_r2602118324

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> char_to_frequency;

        for (char letter : s) {
            char_to_frequency[letter]++;
        }

        for (int i = 0; i < s.size(); ++i) {
            if (char_to_frequency[s[i]] == 1) {
                return i;
            }
        }

        return -1;
    }
};

```

step 2

map の変数名とインテレー他の名前を統一。

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> letter_to_frequency;

        for (const char& letter : s) {
            letter_to_frequency[letter]++;
        }

        for (int i = 0; i < s.size(); ++i) {
            if (letter_to_frequency[s[i]] == 1) {
                return i
            }
        }

        return -1;
    }
};
```

step 3

3回連続10分以内に解く。


step 4

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> letter_to_frequency;

        for (const char letter : s) {
            letter_to_frequency[letter]++;
        }

        for (int i = 0; i < s.size(); ++i) {
            if (letter_to_frequency[s[i]] == 1) {
                return i
            }
        }

        return -1;
    }
};
```