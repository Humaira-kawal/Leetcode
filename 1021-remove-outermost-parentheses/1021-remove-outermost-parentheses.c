char* removeOuterParentheses(char* s) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));

    int balance = 0;
    int j = 0;

    for (int i = 0; i < n; i++) {

        if (s[i] == '(') {
            if (balance > 0) {
                result[j++] = s[i];
            }
            balance++;
        }
        else {
            balance--;

            if (balance > 0) {
                result[j++] = s[i];
            }
        }
    }

    result[j] = '\0';

    return result;
}