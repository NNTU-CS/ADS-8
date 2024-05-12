// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* CageN = new Cage;
    CageN->light = light;
    if (first == nullptr) {
        first = CageN;
        first->next = first;
        first->prev = first;
    } else {
        CageN->next = first;
        CageN->prev = first->prev;
        first->prev->next = CageN;
        first->prev = CageN;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;
    int length = 0;
    first->light = true;
    Cage* CurrentCage = first;
    while (first->light) {
        length = 1;
        CurrentCage = first->next;
        while (!CurrentCage->light) {
            CurrentCage = CurrentCage->next;
            length += 1;
        }
        CurrentCage->light = false;
        countOp += length * 2;
    }
    return length;
}

int Train::getOpCount() {
    return countOp;
}
