// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
void Train::addCage(bool light) {
    Cage* temp = createv(light);
    if (isEmpty()) {
       uni = first = tail = temp;
    } else {
        tail->next = temp;
        tail->next->prev = tail;
        tail = tail->next;
        first->prev = temp;
        tail->next = first;
    }
}
int Train::getLength() {
    if (uni == first && !first->light)
            first->light = true;
    while (true) {
        int len = 0, temp = 0;
        do {
            len++;
            countOp++;
            uni = uni->next;
        } while (!uni->light);
        uni->light = false;
        temp = len;
        while (len--) {
            countOp++;
            uni = uni->prev;
        }
        if (!uni->light) {
            return temp;
        }
    }
}
int Train::getOpCount() {
    return countOp;
}
