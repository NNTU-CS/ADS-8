// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), frst(nullptr) {}
void Train::addCage(bool light) {
    if (frst != nullptr) {
        Cage* stp;
        stp = new Cage;
        stp->light = light;
        stp->nn = nullptr;
        stp->prev = ll;
        ll->nn = stp;
        ll = stp;
    } else {
        frst = new Cage;
        frst->light = light;
        frst->nn = nullptr;
        frst->prev = nullptr;
        ll = frst;
        return;
    }
}
int Train::getLength() {
        frst->light = true;
        frst->prev = ll;
        ll->nn = frst;
        Cage* temp = frst;
        Cage* van = frst->nn;
        while (van != nullptr) {
            if (!van->light) {
                count++;
                countOp++;
                van = van->nn;
            } else {
                if (van->light) {
                        van->light = 0;
                    countOp++;
                }
                for (int c = count; c > 0; c--) {
                    van = van->prev;
                    countOp++;
                }
                if (!van->light) {
                    break;
                }
                van = van->nn;
                count = 1;
            }
        }
        return count;
    }
int Train::getOpCount() {
  return countOp;
}
