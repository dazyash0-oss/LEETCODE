class Solution {
public:
    int characterReplacement(string s, int k) {
        int freq[26] = {};
        int left = 0, maxFreq = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            // Window invalid: need more than k replacements
            if ((right - left + 1) - maxFreq > k) {
                freq[s[left] - 'A']--;
                left++;
            }
        }

        return (int)s.size() - left;
    }
};