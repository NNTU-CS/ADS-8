// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* s;
        s = new Cage;
        s->light = light;
        s->n = nullptr;
        s->prev = l;
        l->n = s;
        l = s;
    } else {
        first = new Cage;
        first->light = light;
        first->n = nullptr;
        first->prev = nullptr;
        l = first;
        return;
    }
}
int Train::getLength() {
        first->light = true;
        first->prev = l;
        l->n = first;
        Cage* temp = first;
        Cage* van = first->n;
        while (van != nullptr) {
            if (!van->light) {
                count++;
                countOp++;
                van = van->n;
            } else {
                if (van->light) {
                        van->light = 0;
                    countOp++;
                }
                for (int i = count; i > 0; i--) {
                    van = van->prev;
                    countOp++;
                }
                if (!van->light) {
                    break;
                }
                van = van->n;
                count = 1;
            }
        }
        return count;
    }
int Train::getOpCount() {
  return countOp;
}
