// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage{ false, nullptr, nullptr };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool ch) {
    if (!first) {
        first = new Cage;
        first->light = ch;
        first->prev = first;
        first->next = first;
    } else {
        Cage* v = first;
        while (v->next != first)
            v = v->next;
        Cage* our = new Cage;
        our->light = ch;
        our->prev = our->next = nullptr;
        our->prev = v;
        v->next = our;
        our->next = first;
        first->prev = our;
    }
}
int Train::getOpCount() {
    return countOp;
}
int Train::getLength() {
    int sh = 0;
    int sh2 = 0;
    Cage* v = first;
    if (v->light == false) {
        v->light = true;
        v = v->next;
        sh++;
        while (true) {
            while (v->light != true) {
                sh++;
                v = v->next;
            }
            v = v->prev;
            sh2++;
            while (v->light != true) {
                sh2++;
                v = v->prev;
            }
            if (sh2 == sh) {
                countOp = sh * 2;
                return sh;
            }
        }
    } else {
        int sch = 0;
        int fin = 0;
        bool kon = true;
        Cage* tek = first;
        do {
            tek = tek->next;
            sch++;
            fin++;
            if (tek->light) {
                tek->light = false;
                for (int i = sch; i > 0; i--) {
                    tek = tek->prev;
                    fin++;
                }
                if (!tek->light) {
                    countOp = fin;
                    return sch;
                } else {
                    sch = 0;
                }
            } else {
                continue;
            }
        } while (kon);
    }
    return 0;
}
