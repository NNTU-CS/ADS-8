// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    countOp = 0;
    first = nullptr;
}

void Train::addCage(bool cond) {
    if (!first) {
        Cage* newCage = new Cage;
        newCage->light = cond;
        newCage->next = newCage;
        newCage->prev = newCage;
        first = newCage;
    } else {
        Cage* copyFirst = first;
        Cage* newCage = new Cage;
        newCage->light = cond;
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}

int Train::getLength() {
    first->light = true;
    Cage* copyfirst = first;
    int k = 1;
    int cages = 1;
    while (first->light) {
        cages = 1;
        copyfirst = first->next;
        while (!copyfirst->light) {
            copyfirst = copyfirst->next;
            cages += 1;
        }
        copyfirst->light = false;
        countOp += 2 * cages;
    }
    return cages;
}

int Train::getOpCount() { return countOp; }
