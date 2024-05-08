// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() :first(nullptr) {}

void Train::addCage(bool light) {
    Cage* newCage = new Cage();
    newCage->light = light;
    if (first == nullptr) {
        newCage->next = newCage;
        newCage->prev = newCage;
        first = newCage;
    } else {
        Cage* lastCage = first->prev;
        newCage->next = first;
        newCage->prev = lastCage;
        first->prev = newCage;
        lastCage->next = newCage;
    }
    if (light) {
        countOp = getLength() + (getLength() * getLength());
    } else {
        countOp = 2 * getLength();
    }
}

int Train::getLength() {
    Cage light;
    int length = 0;
    if (first != nullptr) {
        length = 1;
        Cage* currentCage = first->next;
        while (currentCage != first) {
            length++;
            currentCage = currentCage->next;
        }
    }
    return length;
}

int Train::getOpCount() {
    return countOp;
}
