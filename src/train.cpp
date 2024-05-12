// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* next = first->next;
        first->next = new Cage;
        first->next->prev = first;
        first = first->next;
        next->prev = first;
        first->next = next;
        first->light = light;
    } else {
        first = new Cage;
        first->light = light;
        first->prev = first;
        first->next = first;
    }
}

int Train::getLength() {
    int trainlength = 0;
    int lenAll = 0;
    Cage* current = first;

    if (!current->light) {
        current->light = true;
    }

    while (true) {
        if (!current->next->light) {
            current = current->next;
            countOp++;
            lenAll++;
            continue;
        }

        current->next->light = false;
        countOp += 2;
        trainlength = lenAll + 1;

        while (lenAll > 0) {
            current = current->prev;
            countOp++;
            lenAll--;
        }

        if (!current->light) {
            break;
        }
    }

    return trainlength;
}

int Train::getOpCount() {
    return countOp;
}
