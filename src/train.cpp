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
    Cage* currentWagon = first;
    if (!currentWagon->light) {
        currentWagon->light = true;
    }
    int wagonCount = 0;
    int finalLength = 0;
    bool keepCounting = true;
    while (keepCounting) {
        currentWagon = currentWagon->next;
        countOp += 1;
        wagonCount += 1;
        while (!currentWagon->light) {
            currentWagon = currentWagon->next;
            countOp += 1;
            wagonCount += 1;
        }
        currentWagon->light = false;
        finalLength = wagonCount;
        int tempCount = wagonCount;
        for (int i = 0; i < tempCount; i++) {
            countOp += 1;
            currentWagon = currentWagon->prev;
        }
        if (currentWagon->light == false) {
            keepCounting = false;
        }
    }
    return finalLength;
}
