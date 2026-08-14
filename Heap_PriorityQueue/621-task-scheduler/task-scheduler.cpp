
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int>freq(26,0);
        for(char ch:tasks) freq[ch-'A']++;
        int maxfreq=0,cm=0;
        for(int f:freq){
            if(f>maxfreq){
                maxfreq=f;
                cm=1;
            }
            else if (f==maxfreq) cm++;
        }
        int ans=max((int)tasks.size(),(maxfreq-1)*(n+1)+cm);
        return ans;
    }
};