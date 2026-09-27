char* reverseParentheses(char* s) {
    int n = strlen(s);

    char* stack = (char*)malloc((n + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {

        if (s[i] == '(') {
            // Store opening bracket
            stack[++top] = '(';
        }
        else if (s[i] == ')') {

            // Find the matching '('
            int left = top;

            while (stack[left] != '(') {
                left--;
            }

            // Reverse characters between '(' and ')'
            int l = left + 1;
            int r = top;

            while (l < r) {
                char temp = stack[l];
                stack[l] = stack[r];
                stack[r] = temp;

                l++;
                r--;
            }

            // Remove the '('
            // Shift reversed substring left by one position
            for (int j = left; j < top; j++) {
                stack[j] = stack[j + 1];
            }

            top--;
        }
        else {
            // Normal character
            stack[++top] = s[i];
        }
    }

    // Create result
    stack[top + 1] = '\0';

    return stack;
}