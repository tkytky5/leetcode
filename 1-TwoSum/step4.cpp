#include <map>
#include <vector>

class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> nums, int target) {
      std::map<int, int> num_to_index;

      for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        if (num_to_index.contains(complement)) {
          return {i, num_to_index[complement]};
        }

        num_to_index[nums[i]] = i;
      }

      return {};
    }
};