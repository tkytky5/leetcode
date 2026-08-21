#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> frequent = {};
        for (int element : nums) {
            if (frequent.key(element)) {
                frequent[element] += 1;
            } else {
                frequent[element] = 0;
            }
        }
    }
};