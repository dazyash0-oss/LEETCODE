class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(), n = board[0].size();
        word_sz = word.size();

        int count[128] = {0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                count[board[i][j]]++;
            }
        }
        for (char c: word) {
            if (--count[c] < 0) {
                return false;
            }
        }
        if (count[word[0]] > count[word.back()]) {
            reverse(word.begin(), word.end());
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    char tmp = board[i][j];
                    board[i][j] = '*';
                    if (backtracking(i, j, 1, board, word)) return true;
                    board[i][j] = tmp;
                }
            }
        }
        return false;
    }
private:
    bool backtracking(int i, int j, int index, vector<vector<char>>& board, const string& word) {
        if (index == word_sz) return true;
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            if (board[x][y] != word[index]) continue;
            char tmp = board[x][y];
            board[x][y] = '*';
            if (backtracking(x, y, index + 1, board, word)) return true;
            board[x][y] = tmp;
        }
        return false;
    }
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int m, n, word_sz;
};