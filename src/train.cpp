// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCage(bool light) {
  Cage* nCage = new Cage;
  nCage->light = light;
  if (first == nullptr) {
    first = newCage;
    first->next = first;
    first->prev = first;
  } else {
    nCage->next = first;
    nCage->prev = first->prev;
    first->prev->next = nCage;
    first->prev = nCage;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;
  int len = 0;
  first->light = true;
  Cage* cCage = first;
  while (first->light) {
    len = 1;
    cCage = first->next;
    while (!cCage->light) {
      cCage = cCage->next;
      len += 1;
    }
    cCage->light = false;
    countOp += len * 2;
  }
  return len;
}

int Train::getOpCount() {
  return countOp;
}
