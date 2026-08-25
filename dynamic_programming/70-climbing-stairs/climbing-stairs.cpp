class Solution {
public:
    int climbStairs(int n) {
        int a = 1;
        int b = 2;
        int c = 3;

        if (n <= 3) {
            return n;
        }

        for (int i = 4; i <= n; i++) {
            a = b;
            b = c;
            c = a + b;
        }

        return c;
    }
};