// Copyright 2021 NNTU-CS
#include "train.h"
Train::Cage* Train::create(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
}

void Train::addCage(bool light) {
    if (last && first) {
        last->next = create(light);
        last->next->prev = last;
        last = last->next;
        first->prev = last;
        last->next = first;
    } else {
        first = create(light);
        last = first;
    }
}

int Train::getLength() {
    int len = 0;
    first->light = true;
    Cage* temp = first;
    while (true) {
        len = len + 1;
        for (int j = 0; j < len; j++) {
            temp = temp->next;
            countOp = countOp + 1;
        }
        if (temp->light) {
            temp->light = false;
            for (int j = 0; j < len; j++) {
                temp = temp->prev;
                countOp = countOp + 1;
            }
        } else {
            while (!temp->light) {
                len = len+1;
                temp = temp->next;
                countOp = countOp + 1;
            }
            temp->light = false;
            for (int j = 0; j < len; j++) {
                temp = temp->prev;
                countOp = countOp+1;
            }
        }
        if (!temp->light) {
            break;
        }
    }
    return len;
}
int Train::getOpCount() {
    return countOp;
}
