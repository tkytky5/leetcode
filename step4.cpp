#include <vector>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int> nums, int k) {
        map<int, int> num_to_frequency;
        for (int num : nums) {
            num_to_frequency[num]++;
        }

        priority_queue<pair<int, int>> frequency_to_num;
        for (auto [num, frequency] : num_to_frequency) {
            frequency_to_num.push({frequency, num});
        }

        vector<int> result;
        while (result.size() < k) {
            result.push_back(frequency_to_num.top().second);
            frequency_to_num.pop();
        }

        return result;
    }
};