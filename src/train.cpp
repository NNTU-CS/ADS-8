// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = nullptr;
}

void Train::addCage(bool light) {
    Cage* newCage = new Cage();
    newCage->light = light;
    if (first == nullptr) {
        newCage->next = newCage;
        newCage->prev = newCage;
        first = newCage;
    } else {
        Cage* lastCage = first->prev;
        lastCage->next = newCage;
        newCage->prev = lastCage;
        newCage->next = first;
        first->prev = newCage;
    }
}

int Train::getLength() {
    Train::Cage* CurWagon = first;
    if (!CurWagon->light) {
        CurWagon->light = true;
    }
    int wagCount = 0;
    int finlen = 0;
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
        finlen = wagCount;
        for (wagCount; wagCount > 0; wagCount--) {
            countOp += 1;
            CurWagon = CurWagon->prev;
        }
        if (CurWagon->light == false) {
            continueCount = false;
        }
    }
    return finlen;
}

int Train::getOpCount() {
    return countOp;
}
