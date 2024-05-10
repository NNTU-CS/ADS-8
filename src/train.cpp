// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* newCage = new Cage;
    newCage->light = light;
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
    int length = 0;
    Cage* currentCage = first;
    do {
        currentCage->light = true;
        length++;
        currentCage = currentCage->next;
        while (!currentCage->light) {
            currentCage = currentCage->next;
            length++;
        }
        currentCage->light = false;
        countOp += length * 2;
    } while (currentCage != first);
    return length;
}
int Train::getOpCount() {
    return countOp;
}
