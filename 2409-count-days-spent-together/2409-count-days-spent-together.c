int toDays(char* date) {
    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date[3] - '0') * 10 + (date[4] - '0');

    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 1; i < month; i++) {
        day += days[i];
    }

    return day;
}

int countDaysTogether(char* arriveAlice, char* leaveAlice, char* arriveBob, char* leaveBob) {
    int aStart = toDays(arriveAlice);
    int aEnd = toDays(leaveAlice);
    int bStart = toDays(arriveBob);
    int bEnd = toDays(leaveBob);

    int start = aStart > bStart ? aStart : bStart;
    int end = aEnd < bEnd ? aEnd : bEnd;

    return start <= end ? end - start + 1 : 0;
}