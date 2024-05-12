// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* nCage = new Cage;
    nCage->light;
    if (first == nullptr) {
        first = nCage;
        first->next = first;
        first->prev = first;
    }
    else {
        nCage->next = first;
        nCage->prev = first->prev;
        first->prev->next = nCage;
        first->prev = nCage;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;
    int len = 0;
    first->light = true;
    Cage* CurrentCage = first;
    while (first->light) {
        len = 1;
        CurrentCage = first->next;
        while (!CurrentCage->light) {
            CurrentCage = CurrentCage->next;
            len += 1;
        }
        CurrentCage->light = false;
        countOp += len * 2;
    }
    return len;
}

int Train::getOpCount() {
    return countOp;
}
