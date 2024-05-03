// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstddef>

Train::Train() {
    first = NULL;
    countOp = 0;
}
void Train::addCage(bool light) {
    Cage* node = new Cage;
    node->light = light;
    if (first == NULL) {
        first = node;
        first->prev = node;
        first->next = node;
    } else {
        node->prev = first->prev;
        node->next = first;
        first->prev->next = node;
        first->prev = node;
    }
}
int Train::getLength() {
    Cage* current = first;
    if (first->light == false) {
        first->light = true;
    }
    int len = 0;
    int numberV = 1;
    while (true) {
        countOp++;
        current = current->next;
        len++;
        numberV++;
        int index;
        if (current->light == true) {
            current->light = false;
            index = numberV;
            while (index > 1) {
                current = current->prev;
                countOp++;
                index--;
            }
            if (current->light == false) {
                break;
            } else {
                index = 1;
                while (index < numberV) {
                    current = current->next;
                    countOp++;
                    index++;
                }
                current->light = true;
            }
        } else {
            current->light = true;
        }
    }
    return len;
}
int Train::getOpCount() {
    return countOp;
}
