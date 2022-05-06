// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
        if (first != nullptr && last != nullptr) {
            last->next = create(light);
            last->next->prev = last;
            last = last->next;
            last->next = first;
            first->prev = last;
        } else {
            first = last = create(light);
        }
    }
    int Train::getLength() {
        first->light = true;
        Cage* temp = first->next;
        while (temp != nullptr) {
            if (temp->light != true) {
                countOp++;
                k++;
                temp = temp->next;
            } else {
                if (temp->light) {
                    temp->light = false;
                    countOp++;
                }
                for (int i = k; i > 0; i--) {
                    temp = temp->prev;
                    countOp++;
                }
                if (temp->light != true) {
                    break;
                }
                temp = temp->next;
                k = 1;
            }
        }
        return k;
    }
    int Train::getOpCount() {
        return countOp;
    }
