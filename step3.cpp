#include <vector>
#include <map>
#include <queue>

using namespace std;

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