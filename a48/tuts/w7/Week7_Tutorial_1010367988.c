#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode *reverseList(ListNode *head) {
    ListNode *prev = NULL;
    ListNode *curr = head;

    while (curr != NULL) {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

int main() {}