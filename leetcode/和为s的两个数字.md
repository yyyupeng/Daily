    class Solution {
    public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //双指针(前后指针遍历)
        int i = 0, j = nums.size() - 1;
        while(i < j)
        {
            if(target - nums[i] == nums[j])
                return vector<int> {nums[i], nums[j]};
            else if(target - nums[i] > nums[j])
                i++;
            else
                j--;
        }
        return {};

        /*
        //hashset
        unordered_set<int> st;
        for(int t : nums)
        {
            if(st.count(target - t))
                return vector<int> {target - t, t};
            st.insert(t);
        }
        return {};
        */
    }
    };
