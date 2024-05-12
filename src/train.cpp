// Copyright 2021 NNTU-CS
#include <iostream>
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage *newCage = new Cage;
    newCage->light = light;

    if (!first) {
        first = newCage;
        first->next = first;
        first->prev = first;
    } else {
        Cage *lastCage = first->prev;
        lastCage->next = newCage;
        newCage->prev = lastCage;
        newCage->next = first;
        first->prev = newCage;
    }

    countOp += 2;
}

int Train::getLength() {
    if (!first)
        return 0;

    int length = 0;
    Cage *current = first;
    do {
        length++;
        current = current->next;
    } while (current != first);

    return length;
}

int Train::getOpCount() {
    return countOp;
}
