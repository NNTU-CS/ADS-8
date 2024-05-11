// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* newCage = new Cage();
    newCage->light = light;
    newCage->next = nullptr;
    newCage->prev = nullptr;

    if (!first) {
        first = newCage;
        newCage->next = newCage;
        newCage->prev = newCage;
    } else {
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
        first = newCage;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    Train::Cage* CurWagon = first;
    if (!CurWagon->light) {
        CurWagon->light = true;
    }
    int wagCount = 0;
    int finallen = 0;
    bool continueCount = true;
    while (continueCount) {
        CurWagon = CurWagon->next;
        countOp += 1;
        wagCount += 1;
        while (!CurWagon->light) {
            CurWagon = CurWagon->next;
            countOp += 1;
            wagCount += 1;
        }
        CurWagon->light = false;
        finallen = wagCount;
        for (wagCount; wagCount > 0; wagCount--) {
            countOp += 1;
            CurWagon = CurWagon->prev;
        }
        if (CurWagon->light == false) {
            continueCount = false;
        }
    }
    return finallen;
}
