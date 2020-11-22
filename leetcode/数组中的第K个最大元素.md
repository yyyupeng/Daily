在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5

示例 2:
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

    class Solution {
    public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        k = len - k;
        int left = 0, right = len - 1;
        int index = partition(nums, left, right);
        while(index != k)
        {
            if(index < k)
                left = index + 1;
            else if(index > k)
                right = index - 1;
            index = partition(nums, left, right);
        }
        return nums[index];
    }
    //快排划分
    int partition(vector<int>& nums, int l, int r)
    {
        int tmep = nums[l];
        while(l < r)
        {
            while(l < r && nums[r] >= tmep) r--;
            nums[l] = nums[r];
            while(l < r && nums[l] <= tmep) l++;
            nums[r] = nums[l];
        }
        nums[l] = tmep;
        return l;
    }
    };

