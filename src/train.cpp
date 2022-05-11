// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    Cage* git = new Cage;
    git->light = light;
    git->prev = nullptr;
    git->next = nullptr;
    if (first == nullptr) {
        first = git;
    } else if (first->next == nullptr) {
        first->next = git;
        git->prev = first;
        first->prev = git;
        git->next = first;
    } else {
        first->prev->next = git;
        git->prev = first->prev;
        first->prev = git;
        git->next = first;
    }
}

int Train::getLength() {
    int rose = 0;
    first->light = true;
    Cage* value = first;
    while (true) {
        rose += 1;
        for (int i = 0; i < rose; ++i) {
            value = value->next;
            countOp += 1;
        }
        if (value->light) {
            value->light = false;
            for (int j = 0; j < rose; ++j) {
                value = value->prev;
                countOp += 1;
            }
        } else {
            while (!value->light) {
                rose += 1;
                value = value->next;
                countOp += 1;
            }
            value->light = false;
            for (int k = 0; k < rose; ++k) {
                value = value->prev;
                countOp += 1;
            }
        }
        if (!value->light) {
            break;
        }
    }
    return rose;
}

int Train::getOpCount() {
    return countOp;
}
