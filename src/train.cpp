// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
        Cage *cage = new Cage;
        cage->light = light;
        cage->next = nullptr;
        cage->prev = nullptr;
        if (first == nullptr) {
            first = cage;
        } else if (first->prev == nullptr) {
            first->prev = cage;
            cage->next = first;
            first->next = cage;
            cage->prev = first;
        } else {
            first->next->prev = cage;
            cage->next = first->next;
            first->next = cage;
            cage->prev = first;
        }
    }

int Train::getLength() {
        int len = 0;
        int i = 0;
        first->light = true;
        Cage *temp = first;
        while (true) {
            countOp++;
            len++;
            temp = temp->prev;
            if (temp->light) {
                temp->light = false;
                i = 0;
                while (i < len) {
                    temp = temp->next;
                    countOp++;
                    i++;
                }
                if (!temp->light) {
                    return len;
                }
                len = 0;
            }
        }
        return i;
    }

int Train::getOpCount() {
        return countOp;
    }
