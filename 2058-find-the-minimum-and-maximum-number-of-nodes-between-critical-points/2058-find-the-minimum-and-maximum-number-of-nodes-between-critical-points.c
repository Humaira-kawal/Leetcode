int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* ans = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    ans[0] = -1;
    ans[1] = -1;

    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return ans;

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;
    struct ListNode* next = curr->next;

    int pos = 2;          // position of curr
    int first = -1;       // first critical point
    int last = -1;        // previous critical point
    int minDist = 1000000000;

    while (next != NULL) {

        // Check if curr is a critical point
        if ((curr->val > prev->val && curr->val > next->val) ||
            (curr->val < prev->val && curr->val < next->val)) {

            if (first == -1) {
                // First critical point
                first = pos;
            } else {
                // Distance from previous critical point
                int dist = pos - last;

                if (dist < minDist)
                    minDist = dist;
            }

            last = pos;
        }

        prev = curr;
        curr = next;
        next = next->next;
        pos++;
    }

    // Need at least two critical points
    if (first != last) {
        ans[0] = minDist;
        ans[1] = last - first;
    }

    return ans;
}