// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    countOp = 0;
    first = nullptr;
}

void Train::addCage(bool light) {
    Cage* temp = new Cage;
    temp->light = light;
    if (!first) {
        first = temp;
        first->next = first;
        first->prev = first;
    } else {
        temp->prev = first->prev;
        temp->next = first;
        first->prev = temp;
        temp->prev->next = temp;
    }
}

int Train::getLength() {
    Cage* temp = first;
    temp->light = true;
    int maxLength = 0;
    while (true) {
        int curLength = 0;
        do {
            temp = temp->next;
            curLength++;
        } while (!temp->light);
        countOp += curLength;
        temp->light = false;
        maxLength = curLength;
        while (curLength--) {
            temp = temp->prev;
            countOp++;
        }
        if (!temp->light) {
            return maxLength;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
