// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), ft(nullptr) {}
void Train::addCage(bool light) {
    if (ft != nullptr) {
        Cage* sp;
        sp = new Cage;
        sp->light = light;
        sp->nt = nullptr;
        sp->prev = lt;
        lt->nt = sp;
        lt = sp;
    } else {
        ft = new Cage;
        ft->light = light;
        ft->nt = nullptr;
        ft->prev = nullptr;
        lt = ft;
        return;
    }
}
int Train::getLength() {
        ft->light = true;
        ft->prev = lt;
        lt->nt = ft;
        Cage* temp = ft;
        Cage* van = ft->nt;
        while (van != nullptr) {
            if (!van->light) {
                count++;
                countOp++;
                van = van->nt;
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
                van = van->nt;
                count = 1;
            }
        }
        return count;
    }
int Train::getOpCount() {
  return countOp;
}
