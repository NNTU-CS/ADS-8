// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() :countOp(0), first(nullptr), last(nullptr) {}

Train::Cage* Train::create(bool light) {
    Cage *cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
}

void Train::addCage(bool light) {
    if (first && last) {
        last->next = create(light);
        last->next->prev = last;
        last = last->next;
        last->next = first;
        first->prev = last;
    } else {
        first = last = create(light);
    }
}

int Train::getLength() {
    Cage* temp = first;
    int step = 0;
    if (!(temp->light)) {
        temp->light = !(temp->light);
    }
    temp->light = true;
    while (temp) {
        temp = temp->next;
        step++;
        countOp++;
        if (temp->light == true) {
            temp->light = !true;
            break;
        }
    }
    for (int i = 0; i < step; i++) {
        temp = temp->prev;
        countOp++;
    }
    if (temp->light != true) {
        return step;
    }
    return getLength();
}

int Train::getOpCount() {
    return countOp;
}
