#include <stdlib.h>
#include <stdio.h>
#include "node.h"

void Swap2Nodes(node** head, int i, int j)
{
    // If the list is empty or the same node is selected, return
    if (*head == NULL || i == j)
    {
        return;
    }

    node *temp_i = *head;
    node *temp_j = *head;
    int i = 0;
    int j = 0;

    while (temp_i != NULL && temp_i->position != i)
    {
        temp_i = temp_i->next;
        i++;
    }

    while (temp_j != NULL && temp_j->position != j)
    {
        temp_j = temp_j->next;
        j++;
    }

    if (temp_i == NULL || temp_j == NULL)
    {
        return;
    }

    int temp = temp_i->value;
    temp_i->value = temp_j->value;
    temp_j->value = temp;
}
