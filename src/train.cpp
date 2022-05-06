// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* ncage;
        ncage = new Cage;
        ncage->light = light;
        ncage->next = nullptr;
        ncage->prev = last;
        last->next = ncage;
        last = ncage;
    } else {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        return;
    }
}
int Train::getLength() {
        first->light = true;
        first->prev = last;
        last->next = first;
        Cage* temp = first;
        Cage* n = first->next;
        while (n != nullptr) {
            if (!n->light) {
                count++;
                countOp++;
                n = n->next;
            } else {
                if (n->light) {
                        n->light = 0;
                    countOp++;
                }
                for (int i = count; i > 0; i--) {
                    n = n->prev;
                    countOp++;
                }
                if (!n->light) {
                    break;
                }
                n = n->next;
                count = 1;
            }
        }
        return count;
    }
int Train::getOpCount() {
  return countOp;
}
