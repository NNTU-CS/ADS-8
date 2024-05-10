// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

Train::~Train() {
    Cage* cur = new Cage;
    while (cur->next != nullptr) {
        Cage* temp = cur;
        cur = cur->next;
        delete[] temp;
    }
}

void Train::addCage(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    if (first == nullptr) {
        cage->prev = nullptr;
        first = cage;
        first->next = first;
    } else {
        Cage* cur = first;
        while (cur->next != first) {
        cur = cur->next;
        }
        cur->next = cage;
        cage->prev = cur;
        cage->next = first;
        first->prev = cage;
  }
}

int Train::getLength() {
    int length = 0;
    Cage* cur = first;
    cur->light = true;
    while (true) {
        cur = cur->next;
        countOp++;
        length++;
        if (cur->light == true) {
            cur->light = false;
            int maxlen = length;
            length = 0;
            for (int i = 0; i < maxlen; i++) {
                cur = cur->prev;
                countOp++;
            }
            if (cur->light == false)
                return maxlen;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
