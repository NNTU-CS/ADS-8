// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    countOp = 0;
    Cage{ false, nullptr, nullptr };
    first = nullptr;
}

void Train::addCage(bool n) {
    if (first) {
        Cage* x = first;
        while ((*x).next != first) {
            x = (*x).next;
        }
        Cage* temp = new Cage;
        (*temp).light = n;
        (*temp).prev = (*temp).next = nullptr;
        (*temp).prev = x;
        (*x).next = temp;
        (*temp).next = first;
        (*first).prev = temp;
    } else {
        first = new Cage;
        (*first).light = n;
        (*first).prev = first;
        (*first).next = first;
    }
}

int Train::getLength() {
    int steps1 = 0;
    int steps2 = 0;
    Cage* j = first;
    if ((*j).light == true) {
        int result = 0;
        int c = 0;
        bool end = true;
        Cage* y = first;
        do {
            y = (*y).next;
            c++;
            result++;
            if ((*y).light) {
                (*y).light = false;
                for (int i = c; i > 0; i--) {
                    y = (*y).prev;
                    result++;
                }
                if (!(*y).light) {
                    countOp = result;
                    return c;
                } else {
                    c = 0;
                }
            } else {
                continue;
            }
        } while (end);
    } else {
        (*j).light = true;
        j = (*j).next;
        steps1++;
        while (true) {
            while ((*j).light != true) {
                steps1++;
                j = (*j).next;
            }
            j = (*j).prev;
            steps2++;
            while ((*j).light != true) {
                steps2++;
                j = (*j).prev;
            }
            if (steps2 == steps1) {
                countOp = steps1 + steps1;
                return steps1;
            }
        }
    }
    return 0;
}

int Train::getOpCount() {
    return countOp;
}
