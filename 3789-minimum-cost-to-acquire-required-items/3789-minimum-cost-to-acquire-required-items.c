long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
    long long ans1 = (long long)need1 * cost1 + (long long)need2 * cost2;

    long long common = (need1 < need2) ? need1 : need2;

    long long ans2 = common * costBoth
                   + (long long)(need1 - common) * cost1
                   + (long long)(need2 - common) * cost2;

    long long maxNeed = (need1 > need2) ? need1 : need2;

    long long ans3 = maxNeed * costBoth;

    long long ans = (ans1 < ans2) ? ans1 : ans2;
    return (ans < ans3) ? ans : ans3;
}
