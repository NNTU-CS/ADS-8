// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
        if (first != nullptr && tail != nullptr) {
            tail->next = create(light);
            tail->next->prev = tail;
            tail = tail->next;
            tail->next = first;
            first->prev = tail;
        } else {
            first = tail = create(light);
        }
    }
    int Train::getLength() {
        first->light = true;
        Cage* temp = first->next;
        while (temp != nullptr) {
            if (temp->light != true) {
                countOp++;
                n++;
                temp = temp->next;
            } else {
                if (temp->light) {
                    temp->light = false;
                    countOp++;
                }
                for (int i = n; i > 0; i--) {
                    temp = temp->prev;
                    countOp++;
                }
                if (temp->light != true) {
                    break;
                }
                temp = temp->next;
                n = 1;
            }
        }
        return n;
    }
    int Train::getOpCount() {
        return countOp;
    }
