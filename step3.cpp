#include <vector>
#include <map>

class Solution {
    public:
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
            std::map<std::string, std::vector<std::string>> anagram_groups;

            for (const auto& str : strs) {
                std::string key = str;
                sort(key.begin(), key.end());
                anagram_groups[key].push_back(str);
            }

            std::vector<std::vector<std::string>> result;
            for (const auto& entry : anagram_groups) {
                result.push_back(entry.second);
            }

            return result;
        }

};