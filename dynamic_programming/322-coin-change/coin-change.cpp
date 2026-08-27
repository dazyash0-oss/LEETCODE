class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        const int n = coins.size();

        if (n == 1) return amount % coins[0] ? -1 : amount/ coins[0];

        sort(begin(coins),end(coins));

        if (amount == coins[0]) return 1;
        int minVal = coins[0];
        int gcdVal = minVal;
        int idx = 1;

        for (; idx < n && coins[idx] <= amount; idx++)
        {
            if (coins[idx] == amount) return 1;
            gcdVal = gcd(gcdVal, coins[idx]);
            coins[idx] -= minVal;
        }

        if (amount % gcdVal) return -1;

        int minn = (amount-1) / (coins[idx-1] + minVal) + 1;
        int maxx = amount / minVal;

        for (int i = minn; i <= maxx; i++)
        {
            if (findcomb(coins, 1, idx-1, amount-minVal*i, i)) return i;
        }

        return -1;
    }

    bool findcomb(vector<int>& coins, int l, int r, int amount, int rq)
    {
        if (amount == 0) return true;
        else if (amount < coins[l] || amount / coins[r] > rq) return false;
        else if (amount % coins[r] == 0) return true;
        else if (l == r) return false;

        for (int p = amount / coins[r] + 1; p--;)
        {
            if (findcomb(coins, l, r-1, amount-p*coins[r], rq-p)) return true;
        }
        return false;
    }
};