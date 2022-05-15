// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (first == nullptr) {
        first = new Cage();
        first->next = nullptr;
        first->prev = nullptr;
        first->light = light;
        last = first;
        return;
    }
    Cage *newCage;
    newCage = new Cage();
    newCage->light = light;
    newCage->prev = last;
    newCage->next = nullptr;
    last->next = newCage;
    last = newCage;
}

void Train::calculate() {
    if (calculated) {
        return;
    }
    calculated = true;
    first->prev = last;
    last->next = first;
    first->light = true;
    Cage *current = first->next;
    while (true) {
        if (current->light == false) {
            countOp++;
            length++;
            current = current->next;
        } else {
            current->light = false;
            countOp++;
            for (int i = 0; i < length; i++) {
                current = current->prev;
                countOp++;
            }
            if (current->light == false) {
                break;
            }
            length = 1;
            current = current->next;
        }
    }
}

int Train::getLength() {
    calculate();
    return length;
}

int Train::getOpCount() {
    calculate();
    return countOp;
}
