// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = new Cage;
    first->prev = nullptr;
    countOp = 0;
    length = 0;
    trule = 0;
}

void Train::addCage(bool light) {
    if (first->prev == nullptr) {
        first->light = light;
        first->prev = first;
        first->next = first;
    } else {
        Cage* Temp = first->next;
        first->next = new Cage;
        first->next->prev = first;

        first = first->next;
        Temp->prev = first;
        first->next = Temp;
        first->light = light;
    }
}

int Train::getLength() {
    if (!first->light) {
        first->light = true;
    }
    while (true) {
        while (!first->next->light) {
            first = first->next;
            countOp++;
            length++;
        }
        first->next->light = false;
        countOp += 2;
        trule = length + 1;
        for (; length > 0; length--) {
            first = first->prev;
            countOp++;
        }
        if (first->light == false) {
            break;
        }
    }
    return trule;
}

int Train::getOpCount() {
    return countOp;
}
