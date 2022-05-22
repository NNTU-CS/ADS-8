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
    int length = 0;
    first->light = true;
    Cage* temp = first;
    while (true) {
        length++;
        for (int i = 0; i < length; ++i) {
            temp = temp->next;
            countOp++;
        }
        if (temp->light) {
            temp->light = false;
            for (int i = 0; i < length; ++i) {
                temp = temp->prev;
                countOp++;
            }
        } else {
            while (!temp->light) {
                length++;
                temp = temp->next;
                countOp++;
            }
            temp->light = false;
            for (int i = 0; i < length; ++i) {
                temp = temp->prev;
                countOp++;
            }
        }
        if (!temp->light) {
            break;
        }
    }
    return length;
}

int Train::getOpCount() {
    return countOp;
}
