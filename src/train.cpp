// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage {
        false,
        nullptr,
        nullptr
        };
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light2) {
  Cage *newCage = new Cage;
  newCage->light = light2;

  if (first == nullptr) {
      first = newCage;
      newCage->next = first;
      newCage->prev = first;
  } else {
      Cage *lastCage = first->prev;
      newCage->next = first;
      newCage->prev = lastCage;
      lastCage->next = newCage;
      first->prev = newCage;
  }
}
int Train::getLength() {
  int length = 0;
  Cage *currentCage = first;
  currentCage->light = true;
    while (true) {
        currentCage = currentCage->next;
        countOp++;
        length++;
        if (currentCage->light == true) {
            currentCage->light = false;
            int maxlength = length;
            length = 0;
            for (int i = 0; i < maxlength; i++) {
                currentCage = currentCage->prev;
                countOp++;
            }
            if (currentCage->light == false)
                return maxlength;
        }
    }
}
int Train::getOpCount() {
  return countOp;
}
