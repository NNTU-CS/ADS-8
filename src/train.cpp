// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage* Train::create(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
}

Train::Train() {
    first = nullptr;
    tail = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* temp = create(light);
    if (!first) {
       current = first = tail = temp;
    } else {
        tail->next = temp;
        tail->next->prev = tail;
        tail = tail->next;
        first->prev = temp;
        tail->next = first;
    }
}

int Train::getLength() {
    int length = 0;
    first->light = true;
    Cage* temp = first;
    while (true) {
        length++;
        for (int i = 0; i < length; i++) {
            temp = temp->next;
            countOp++;
        }
        if (temp->light) {
            temp->light = false;
            for (int i = 0; i < length; i++) {
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
            for (int i = 0; i < length; i++) {
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
