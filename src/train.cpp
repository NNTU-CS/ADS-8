// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = new Cage;
    first->prev = nullptr;
    countOp = 0;
    step = 0;
    length = 0;
}

void Train::addCage(bool light) {
    if (first->prev == nullptr) {
        first->next = first;
        first->prev = first;
        first->light = light;
    } else {
        Cage* mystruct = first->next;
        first->next = new Cage;
        first->next->prev = first;

        first = first->next;
        mystruct->prev = first;
        first->next = mystruct;
        first->light = light;
    }
}

int Train::getLength() {
    if (!first->light) {
        first->light = true;
    }
    while (true) {
        countOp++;
        while (!first->next->light) {
            first = first->next;
            countOp++;
            step++;
        }
        first->next->light = false;
        countOp++;
        length = step;
        while (step > 0) {
            first = first->prev;
            countOp++;
            step--;
        }
        if (first->light == false) {
            return (length + 1);
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
