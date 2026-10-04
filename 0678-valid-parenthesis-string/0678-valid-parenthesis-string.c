bool checkValidString(char* s) {
    int low = 0;
    int high = 0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (s[i] == '(') {
            low++;
            high++;
        }
        else if (s[i] == ')') {
            low--;
            high--;
        }
        else {  // '*'
            low--;   // Treat '*' as ')'
            high++;  // Treat '*' as '('
        }

        // Too many closing brackets
        if (high < 0) {
            return false;
        }

        // Minimum cannot be negative
        if (low < 0) {
            low = 0;
        }
    }

    // If zero unmatched '(' is possible
    return low == 0;
}