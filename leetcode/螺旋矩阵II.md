给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:
输入: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

    class Solution {
    public:
    vector<vector<int>> generateMatrix(int n) {
        int left = 0, right = n - 1, top = 0, bottom = n - 1;
        vector<vector<int>> res(n, vector<int>(n, 0));
        int num = 1;
        while(left <= right && top <= bottom)
        {
            //从左往右
            for(int i = left; i <= right; ++i)
                res[top][i] = num++;
            //从上往下
            for(int i = top + 1; i <= bottom; ++i)
                res[i][right] = num++;
            if(left < right && top < bottom)
            {
                //从右往左
                for(int i = right - 1; i > left; --i)
                    res[bottom][i] = num++;
                //从下往上
                for(int i = bottom; i > top; --i)
                    res[i][left] = num++;
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return res;
    }
    };
