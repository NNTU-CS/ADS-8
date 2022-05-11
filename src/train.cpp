// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), ft(nullptr) {}
void Train::addCage(bool light) {
    if (ft != nullptr) {
        Cage* ssp;
        ssp = new Cage;
        ssp->light = light;
        ssp->nxt = nullptr;
        ssp->prev = lst;
        lst->nxt = ssp;
        lst = ssp;
    } else {
        ft = new Cage;
        ft->light = light;
        ft->nxt = nullptr;
        ft->prev = nullptr;
        lst = ft;
        return;
    }
}
int Train::getLength() {
        ft->light = true;
        ft->prev = lst;
        lst->nxt = ft;
        Cage* temp = ft;
        Cage* van = ft->nxt;
        while (van != nullptr) {
            if (!van->light) {
                count++;
                countOp++;
                van = van->nxt;
            } else {
                if (van->light) {
                        van->light = 0;
                    countOp++;
                }
                for (int q = count; q > 0; q--) {
                    van = van->prev;
                    countOp++;
                }
                if (!van->light) {
                    break;
                }
                van = van->nxt;
                count = 1;
            }
        }
        return count;
    }
int Train::getOpCount() {
  return countOp;
}
