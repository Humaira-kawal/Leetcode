#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* numberToWords(int num) {
    char *result = malloc(1000);
    result[0] = '\0';

    if (num == 0) {
        strcpy(result, "Zero");
        return result;
    }

    char *ones[] = {
        "", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine",
        "Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen",
        "Seventeen", "Eighteen", "Nineteen"
    };

    char *tens[] = {
        "", "", "Twenty", "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };

    char *scale[] = {
        "", "Thousand", "Million", "Billion"
    };

    // Converts a number from 1 to 999
    void convert(int n, char *temp) {
        temp[0] = '\0';

        if (n >= 100) {
            strcat(temp, ones[n / 100]);
            strcat(temp, " Hundred");
            n %= 100;

            if (n > 0)
                strcat(temp, " ");
        }

        if (n >= 20) {
            strcat(temp, tens[n / 10]);
            n %= 10;

            if (n > 0) {
                strcat(temp, " ");
                strcat(temp, ones[n]);
            }
        }
        else if (n > 0) {
            strcat(temp, ones[n]);
        }
    }

    int group = 0;

    while (num > 0) {
        int part = num % 1000;

        if (part != 0) {
            char temp[200];
            char current[200];

            convert(part, current);

            temp[0] = '\0';

            if (scale[group][0] != '\0') {
                strcat(temp, current);
                strcat(temp, " ");
                strcat(temp, scale[group]);
            } else {
                strcpy(temp, current);
            }

            if (result[0] != '\0') {
                strcat(temp, " ");
                strcat(temp, result);
            }

            strcpy(result, temp);
        }

        num /= 1000;
        group++;
    }

    return result;
}