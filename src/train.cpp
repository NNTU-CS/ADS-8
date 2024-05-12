// Copyright 2021 CheginArtyom
#include "train.h"

Train::Train() : first(nullptr), end(nullptr) {}

void Train::addCage(bool light) {
    if (!first) {
        first = new Cage;
        first->light = light;
        end = first;
        first->next = first;
        first->prev = first;
    } else {
        Cage *uk = new Cage;
        uk->light = light;
        uk->next = first;
        uk->prev = end;
        end->next = uk;
        end = uk;
        first->prev = uk;
    }
}

int Train::getLength() {
    first->light = true;
    int kvp = 0;
    Cage *temp = first;
    int tempn = 0;
    while (true) {
        countOp++;
        tempn++;
        temp = temp->next;
        if (temp->light) {
            int tmp = tempn;
            temp->light = false;
            for (int i = tempn; tempn > 0; tempn--, countOp++) {
                temp = temp->prev;
            }
            if (!temp->light) {
                kvp = tmp;
                break;
            }
        }
    }
    return kvp;
}

int Train::getOpCount() {
    return countOp;
}
