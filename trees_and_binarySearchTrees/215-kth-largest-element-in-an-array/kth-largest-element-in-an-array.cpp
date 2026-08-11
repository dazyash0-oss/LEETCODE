class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        priority_queue<int> pq;
        for(int i=0;i<nums.size();i++)
        {
            pq.push(nums[i]);
        }
        while(1)
        {
            k--; 
            if(k==0) return pq.top();
            pq.pop();
        }
        return -1;
    }
//please upvote...
};