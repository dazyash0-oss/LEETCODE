class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(int i = 0; i < s.length(); i++) {
            char c = s[i];

            // 1. If opening bracket, push it
            if(c == '{' || c == '(' || c == '[') {
                st.push(c);
            }
            // 2. If closing bracket
            else {
                // stack empty means no matching open bracket
                if(st.empty()) return false;

                char top = st.top();
                // check if it matches
                if( (c == ')' && top == '(') ||
                    (c == '}' && top == '{') ||
                    (c == ']' && top == '[') ) {
                    st.pop();
                } else {
                    return false; // mismatch
                }
            }
        }
        // 3. Valid only if stack is empty
        return st.empty();
    }
};
