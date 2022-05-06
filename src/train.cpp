// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) { }

void Train::addCage(bool light) {
    if (first) {
        Cage* last = first->prev;
        last->next = new Cage{light, first, last};
        first->prev = last->next;
    } else {
        first = new Cage{light, nullptr};
        first->prev = first;
    }
}

int Train::getLength() {
    while (true) {
        int steps = 0;
        Cage* cage = first;
        cage->light = true;
        do {
            cage = cage->next;
            steps++;
        } while (!cage->light);
        cage->light = false;
        for (int i = steps; i > 0; i--) {
            cage = cage->prev;
            steps++;
        }
        countOp += steps;
        if (!cage->light) return steps / 2;
    }
}

int Train::getOpCount() {
    return countOp;
}
