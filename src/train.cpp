// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool l) {
    Cage* newCage = new Cage(l, nullptr, nullptr);
    newCage->light = l;
    if (first == nullptr) {
        first = newCage;
        first->next = first;
        first->prev = first;
    } else {
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;
    int l = 0;
    Cage* currentCage = first;
    do {
        currentCage->light = true;
        l++;
        currentCage = currentCage->next;
        while (!currentCage->light) {
            currentCage = currentCage->next;
            l++;
        }
        currentCage->light = false;
        countOp += l * 2;
    } while (currentCage != first);
    return l;
}

int Train::getOpCount() {
    return countOp;
}
