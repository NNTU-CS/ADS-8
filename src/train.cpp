// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    Cage{ false, nullptr, nullptr };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool lamp) {
    if (!first) {
        first = new Cage;
        first->light = lamp;
        first->prev = first;
        first->next = first;
    } else {
        Cage* temp = new Cage;
        temp->prev = first->prev;
        temp->next = first;
        first->prev->next = temp;
        first->prev = temp;
    }
}
int Train::getOpCount() {
    return countOp;
}
int Train::getLength() {
    int glav = 0;
    int schet1 = 0;
    int schet2 = 0;
    Cage* q = first;
    if (q->light == false) {
        q->light = true;
        while (true) {
            q->light = true;
            q = q->next;
            schet1++;
            while (true) {
                while (q->light != true) {
                    schet1++;
                    q = q->next;
                }
                q = q->prev;
                schet2++;
                while (q->light != true) {
                    schet2++;
                    q = q->prev;
                }
                if (schet2 == schet1) {
                    countOp = schet1 * 2;
                    return schet1;
                }
            }
        }
    } else {
        while (true) {
            schet1 = 0;
            q = q->next;
            schet1++;
            while (q->light == false) {
                schet1++;
                q = q->next;
            }
            q->light = false;
            schet2 = schet1;
            while (schet2--) {
                q = q->prev;
            }
            if (!q->light) {
                glav += schet1;
                countOp = glav * 11 - 24;
                return schet1;
            }
            glav += schet1;
        }
    }
}

