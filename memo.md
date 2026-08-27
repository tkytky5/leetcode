step 1

わからなかったので他の人の回答を見る。

local と domainで切り分ける。
＋ があればその手前までを local とする。

C++では文字列から特定の文字を削除したい場合、Erase-remove イディオムという手法があるらしい。
removeで特定の文字を文字列の後ろに移動させ、削除対象の最初のインデックスを返す。ただし配列サイズは変わらない。erase で先ほどのインデックスから末尾までを指定することで特定の文字を取り除くことができる。

local と domain の pair 型として set に格納し重複を排除。

```c++
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        set<pair<string, string>> uniqueEmails;

        for (const auto& email : emails) {
            size_t atPosition = email.find('@');
            string local = email.substr(0, atPosition);
            string domain = email.substr(atPosition + 1);

            size_t plusPosition = local.find('+');
            if (plusPosition != string::npos) {
                local = local.substr(0, plusPosition);
            }

            local.erase(remove(local.begin(), local.end(), '.'), local.end());
            uniqueEmails.insert({local, domain});
        }

        return uniqueEmails.size();
    }
}
```

step 2

https://github.com/chryschron/codings/pull/14/files#r3487474245

こんな書き方もあった。
@ か + のいずれかがあれば手前までが local と言える。

move の概念が理解できず以下参照。
https://qiita.com/tyanmahou/items/3227515bf424f0f2b43d


```c++
class Solution {
public:
    int numUniqueEmails(vector<string> emails) {
        unordered_set<string> unique;
        for (const auto& email : emails) {
            string normalized = email.substr(0, email.find_first_of("@+"));
            erase(normalized, '.');
            normalized += email.substr(email.find('@'));
            unique.insert(move(normalized));
        }
        return unique.size();
    }
};
```