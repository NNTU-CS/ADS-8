// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    Cage* temp = new Cage;
    temp->light = light;
    if (first != nullptr) {
        if (first->prev != nullptr) {
            first->prev->next = temp;
            temp->prev = first->prev;
            first->prev = temp;
            temp->next = first;
        } else {
            first->prev = temp;
            first->next = temp;
            temp->prev = first;
            temp->next = first;
        }
    } else {
        first = temp;
        first->prev = nullptr;
        first->next = nullptr;
    }
}

int Train::getLength() {
    first->light = true;
    Cage* current = first;
    int steps = 0;
    while (current) {
        current = current->next;
        countOp++;
        steps++;
        if (current->light == true) {
            current->light = false;
            for (int i = 0; i < steps; i++) {
                current = current->prev;
                countOp++;
            }
            if (current->light == false)
                return steps;
            steps = 0;
        }
    }
    return 0;
}

int Train::getOpCount() {
    if (!countOp)
        int temp = getLength();
    return countOp;
}
