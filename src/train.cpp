// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
  Cage* nodeCage = new Cage;
  nodeCage->light = light;

  if (first == nullptr) {
    first = nodeCage;
    nodeCage->prev = nodeCage;
    nodeCage->next = nodeCage;
    return;
  }

  nodeCage->next = first;
  nodeCage->prev = first->prev;
  first->prev->next = nodeCage;
  first->prev = nodeCage;
}

int Train::getLength() {
    int temp = 0;
    Cage* curt = first;
    curt->light = true;

    while (true) {
        curt = curt->next;
        countOp++;
        temp++;

        if (curt->light) {
            curt->light = false;
            int length = temp;

            for (int i = 0; i < length; i++) {
                curt = curt->prev;
                countOp++;
                temp--;
            }

            if (!curt->light)
                return length;
        }
    }
}

int Train::getOpCount() {
  return countOp;
}
