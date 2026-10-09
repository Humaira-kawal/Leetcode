
int minInsertions(char* s) {
    int insertions = 0;
    int open = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            open++;
        } else {
            // If the next character is also ')',
            // we have a complete closing pair.
            if (s[i + 1] == ')') {
                i++;
            } else {
                // Insert one ')' to complete the pair.
                insertions++;
            }

            // Match this closing pair with an opening '('.
            if (open > 0) {
                open--;
            } else {
                // Insert one '(' because no opening exists.
                insertions++;
            }
        }
    }

    // Each remaining '(' needs two ')'.
    insertions += open * 2;

    return insertions;
}
