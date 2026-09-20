int reverseDegree(char* s) {
    int sum = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int reversePosition = 26 - (s[i] - 'a');
        int stringPosition = i + 1;

        sum += reversePosition * stringPosition;
    }

    return sum;
}