step1

文字列の真ん中を基準にleftとrightが対応する括弧か確認する

"(){}[]"
上記ケースに対応できない。

Time complexity: O(n)
Space complexity: O(1)

```c++
class Solution {
public:
    bool isValid(string s) {
        int length = s.size();
        if (length % 2 != 0) {
            return false;
        }
        
        int middle = length / 2;

        bool result = false;
        int right = middle;
        int left = middle - 1;
        for (int i = middle; i < length; i++) {
            if (s[right] == '}' && s[left] == '{') {
                result = true;
            } else if (s[right] == ']' && s[left] == '[') {
                result = true;
            } else if (s[right] == ')' && s[left] == '(') {
                result = true;
            }

            right += 1;
            left -= 1;
        }

        return result;
    }
};
```


step2
解答を見る

- https://github.com/minsrd/arai60/pull/6/changes
    - mapとstackを使って、ループ内で
        ・開き括弧ならスタックに投入
        ・スタックが空、または、現在の括弧とスタックのtopが対応していないならfalse
        ・それ以外（括弧が対応している）ならスタックからpopする
    - スタックが空ならtrue
    - if文がそれぞれシンプルでわかりやすいと思った

```go
func isValid(s string) bool {
	pairs := map[rune]rune{'(': ')', '{': '}', '[': ']'}
	stack := []rune{}

	for _, r := range s {
		if _, ok := pairs[r]; ok {
			stack = append(stack, r)
			continue
		}
		if len(stack) == 0 || r != pairs[stack[len(stack)-1]] {
			return false
		}
		stack = stack[:len(stack)-1]
	}
	return len(stack) == 0
}
```


step3

c++に変換

```c++
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        map<char, char> pairs;
        pairs['{'] = '}';
        pairs['['] = ']';
        pairs['('] = ')';

        stack<char> stack;

        for (char ch : s) {
            if (pairs.contains(ch)) {
                stack.push(ch);
                continue;
            }
            if (stack.size() == 0 || ch != pairs[stack.top()]) {
                return false;
            }
            stack.pop();
        }

        return stack.empty();
    }
};
```