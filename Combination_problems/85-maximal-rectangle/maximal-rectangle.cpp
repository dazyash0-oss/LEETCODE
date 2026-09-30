class Solution {
public:

    int hist(vector<int>& h) {
        stack<int> st;
        int ans = 0;
        int n = h.size();

        for (int i = 0; i <= n; i++) {

            int curr = (i == n ? 0 : h[i]);

            while (!st.empty() && h[st.top()] > curr) {

                int height = h[st.top()];
                st.pop();

                int width;

                if (st.empty())
                    width = i;
                else
                    width = i - st.top() - 1;

                ans = max(ans, height * width);
            }

            st.push(i);
        }

        return ans;
    }


    int maximalRectangle(vector<vector<char>>& matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> height(m, 0);
        int ans = 0;

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < m; j++) {

                if (matrix[i][j] == '1')
                    height[j]++;
                else
                    height[j] = 0;
            }

            ans = max(ans, hist(height));
        }

        return ans;
    }
};