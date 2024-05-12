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
    int lengthTrain = 0;
    first->light = true;
    Cage* CurrentCage = first;
    while (first->light) {
        lengthTrain = 1;
        CurrentCage = first->next;
        while (!CurrentCage->light) {
            CurrentCage = CurrentCage->next;
            lengthTrain += 1;
        }
        CurrentCage->light = false;
        countOp += lengthTrain * 2;
    }
    return lengthTrain;
}

int Train::getOpCount() {
    return countOp;
}
