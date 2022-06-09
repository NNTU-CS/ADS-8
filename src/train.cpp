// Copyright 2021 NNTU-CS
#include "train.h"
Train::Cage* Train::create(bool lamp) {
    Cage* tmp = new Cage;
    tmp->light = lamp;
    tmp->next = nullptr;
    tmp->prev = nullptr;
    return tmp;
}
Train::Train() : countOp(0) {}
void Train::addCage(bool light) {
    if (first) {
        Cage* tmp = create(light);
        tmp->prev = current;
        tmp->next = first;
        current->next = tmp;
        current = tmp;
        first->prev = current;
    } else {
        first = create(light);
        current = first;
    }
}
int Train::getLength() {
    int n = 1;
    Cage* tmp = first;
    if (!first->light) {
        while (n++) {
            for (int i = 0; i < n; i++) {
                if (i != n - 1) {
                    tmp->light = true;
                    tmp = tmp->next;
                } else {
                    tmp->light = false;
                    tmp = first;
                }
            }
            if (tmp->light == false) {
                countOp = (n - 1) * 2;
                return n - 1;
            }
        }
    } else {
        while (n++) {
            for (int i = 0; i < n; i++) {
                if (i != n - 1) {
                    tmp->light = true;
                    tmp = tmp->next;
                    ++countOp;
                } else {
                    tmp->light = false;
                }
            }
            for (int j = n - 1; j > 0; j--) {
                tmp = tmp->prev;
                ++countOp;
            }
            if (tmp->light == false) {
                return n - 1;
            }
        }
    }
    return 0;
}
int Train::getOpCount() {
    return countOp;
}
