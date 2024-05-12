// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage *newCage = new Cage;
    newCage->light = light;
    if (first == nullptr) {
        first = newCage;
        newCage->next = newCage;
        newCage->prev = newCage;
    } else {
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}

int Train::getLength() {
    int length = 0;
    Cage* current = first;
    current->light = true;
    while (true) {
        current = current->next;
        countOp++;
        length++;
        if (current->light == true) {
            current->light = false;
            int mlength = length;
            length = 0;
            for (int i = 0; i < mlength; i++) {
                current = current->prev;
                countOp++;
            }
            if (current->light == false)
                return mlength;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
