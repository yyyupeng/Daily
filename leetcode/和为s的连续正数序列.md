    class Solution {
    public:
    vector<vector<int>> findContinuousSequence(int target) {
        //双指针(滑动窗口-->只向一侧滑动)
        vector<vector<int>> res;
        vector<int> temp;
        int i = 1, j = 2;
        int sum;
        while(i < j)
        {
            sum = (i + j) * (j - i + 1) / 2;    //求和公式
            if(sum == target)
            {
                temp.clear();
                for(int k = i; k <= j; ++k)
                    temp.emplace_back(k);
                res.emplace_back(temp);
                i++;
            }
            else if(sum > target)
                i++;
            else
                j++;
        }
        return res;
    }
    };
