// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0) {
    first = nullptr;
}

void Train::addCage(bool light) {
    Cage* newCage = new Cage();
    newCage->light = light;
    if (!first) {
        first = newCage;
        first->next = first;
        first->prev = first;
        return;
    }
    Cage* last = first->prev;
    last->next = newCage;
    newCage->prev = last;
    newCage->next = first;
    first->prev = newCage;
}

int Train::getLength() {
    countOp = 0;
    if (!first) {
        return 0;
    }
    first->light = true;
    while (true) {
        Cage* cage = first;
        int length = 0;
        do {
            cage = cage->prev;
            countOp++;
            length++;
        } while (cage->light == false);
        cage->light = false;
        for (int i = 0; i < length; i++) {
            cage = cage->next;
            countOp++;
        }
        if (cage->light == false) {
            return length;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
