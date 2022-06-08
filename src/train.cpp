// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
void Train::addCage(bool light) {
    Cage* temp = create(light);
    if (isEmpty()) {
       current = first = tail = temp;
    } else {
        tail->next = temp;
        tail->next->prev = tail;
        tail = tail->next;
        first->prev = temp;
        tail->next = first;
    }
}
int Train::getLength() {
    if (current == first && !first->light)
            first->light = true;
    while (true) {
        int len = 0, temp = 0;
        do {
            len++;
            countOp++;
            current = current->next;
        } while (!current->light);
        current->light = false;
        temp = len;
        while (len--) {
            countOp++;
            current = current->prev;
        }
        if (!current->light) {
            return temp;
        }
    }
}
int Train::getOpCount() {
    return countOp;
}
