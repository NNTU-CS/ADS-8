// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

int Train::getOpCount() { return countOp; }

void Train::addCage(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->prev = nullptr;
    cage->next = nullptr;
    if (first == nullptr) {
        first = cage;
    } else {
        if (first->next == nullptr) {
            first->next = cage;
            cage->prev = first;
            first->prev = cage;
            cage->next = first;
        } else {
            first->prev->next = cage;
            cage->prev = first->prev;
            first->prev = cage;
            cage->next = first;
        }
    }
}

int Train::getLength() {
    int len_buff, len= 0;
    first->light = true;
    Cage* temp = first;
    while (1337) {
        countOp++;
        len++;
        temp = temp->next;
        if (temp->light) {
            temp->light = false;
            len_buff = len;
            for (len_buff; len_buff > 0; len_buff--) {
                temp = temp->prev;
                countOp++;
            }
            if (!temp->light) {
                return len;
            }
            else {
                len = len_buff;
            }
        }
    }
    return len_buff;
}
