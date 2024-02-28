#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include <stddef.h>

// Check current node, move to next node until NULL node is not found.
// Finds the tail node.

node* GetTail(node* current) {
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

node* Partition(node* head, node* end, node** newHead, node** newEnd) {
    node* pivot = end;
    node* prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->value < pivot->value) {
            if ((*newHead) == NULL) {
                (*newHead) = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) {
                prev->next = cur->next;
            }
            node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL) {
        (*newHead) = pivot;
    }

    (*newEnd) = tail;

    return pivot;
}

node* QuickSort(node* head, node* end) {
    if (!head || head == end) {
        return head;
    }

    node* newHead = NULL, *newEnd = NULL;

    node* pivot = Partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        node* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;

        newHead = QuickSort(newHead, tmp);

        tmp = GetTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = QuickSort(pivot->next, newEnd);

    return newHead;
}

void SortList(node** head) {
    (*head) = QuickSort(*head, GetTail(*head));
    node* ptr = *head; int pos = 1;
    while(ptr!=NULL)
    {
      ptr->position = pos;
      pos = pos+1;
      ptr = ptr->next;
   }
}
