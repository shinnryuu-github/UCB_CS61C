#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (!head)
        return 0;
    node *tortoise = head, *hare = head;
    while (1){
        if (!hare->next)
            return 0;
        else
            hare = hare->next;
        if (!hare->next)
            return 0;
        else
            hare = hare->next;
        tortoise = tortoise->next;
        if (tortoise == hare)
            return 1;
    }
    return 0;
}