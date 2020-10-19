    class Solution {
    //快排划分
    int partition(vector<int>& arr, int l, int r)
    {
        int temp = arr[l];
        while(l<r)
        {
            while(l < r && arr[r] >= temp) r--;
            arr[l] = arr[r];
            while(l < r && arr[l] <= temp) l++;
            arr[r] = arr[l]; 
        }
        arr[l] = temp;
        return l;
    }
    public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if(!arr.size() || !k)   return {};
        vector<int> vc(k, -1);
        int left = 0, right = arr.size() - 1;
        int index = partition(arr, left, right);
        while(index != k - 1)
        {
            if(index > k - 1)
                right = index - 1;
            else if(index < k - 1)
                left = index + 1;
            index = partition(arr, left, right);
        }
        for(int i = 0; i < k; ++i)
            vc[i] = arr[i];
        return vc;

        /*
         * 大顶堆（优先队列）
        vector<int> vc(k, -1);
        priority_queue<int> Q;
        for (int i = 0; i < k; ++i)
            Q.push(arr[i]);
        for (int i = k; i < arr.size(); ++i) 
        {
            if (Q.top() > arr[i]) 
            {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) 
        {
            vc[i] = Q.top();
            Q.pop();
        }
        return vc;
        */

        /*
         * sort
        vector<int> vc;
        sort(arr.begin(), arr.end());
        for(int i = 0; i < k; ++i)
            vc.push_back(arr[i]);
        return vc;
        */
    }
    };
