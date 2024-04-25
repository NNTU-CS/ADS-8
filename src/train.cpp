// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage *oC = new Cage;
        oC->light = light;
        TailOfTrain->next = oC;
        oC->prev = TailOfTrain;
        oC->next = nullptr;
        TailOfTrain = TailOfTrain->next;
    } else {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
        TailOfTrain = first;
    }
}

int Train::getLength() {
    iPerem = 1;
    first->prev = TailOfTrain;
    TailOfTrain->next = first;
    first->light = true;
    Cage *train = new Cage;
    train = first->next;
    while (true) {
        countOp++;
        if (train->light != true) {
            iPerem++;
            train = train->next;
        } else {
            train->light = false;
            break;
        }
    }
    for (int i = 1; i <= iPerem; i++) {
        countOp++;
        train = train->prev;
    }
    if (train->light == false) {
        return iPerem;
    } else {
        return getLength();
    }
}

int Train::getOpCount() {
    return countOp;
}
