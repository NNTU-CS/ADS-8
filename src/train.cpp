// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    countOp = 0;
    first = nullptr;
}

void Train::addCage(bool light) {
    Cage* current = new Cage;
    current->light = light;
    if (first == nullptr) {
        first = current;
        first->prev = first;
        first->next = first;
    } else {
        current->next = first;
        current->prev = first->prev;
        first->prev->next = current;
        first->prev = current;
    }
}

int Train::getLength() {
    int  Dyn_count = 1;
    Cage* current = first;
    if (current == nullptr) return 0;
    current->light = true;
    countOp++;
    current = current->next;
    while (current) {
        if (current->light == false) {
            Dyn_count++;
            countOp++;
            current = current->next;
        } else {
            current->light = false;
            for (int i = 0; i < Dyn_count; i++) {
                countOp++;
                current = current->prev;
            }
            if (current->light == false) {
                return Dyn_count;
            } else {
                Dyn_count = 1;
                countOp++;
                current = current->next;
            }
        }
    }
    return 0;
}
int Train::getOpCount() {
    return countOp;
}
