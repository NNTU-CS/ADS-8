// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
  first = nullptr;
  countOp = 0;
}

int Train::getOpCount() {
  return countOp;
}

void Train::addCage(bool light) {
  Cage* Cag = new Cage;
  Cag->light = light;
  if (first == nullptr) {
    first = Cag;
    first->next = Cag;
    first->prev = Cag;
    return;
  }
  Cag->prev = first->prev;
  Cag->next = first;
  first->prev->next = Cag;
  first->prev = Cag;
}

int Train::getLength() {
  int k1, k2;
  Cage* nov = first;
  k1 = 0;
  k2 = 0;
  if (!first->light) {
    first->light = true;
  }
  while (!nov->next->light) {
    nov = nov->next;
    k1++;
    countOp++;
  }
  nov = nov->next;
  nov->light = false;
  k1++;
  countOp++;
  k2 = k1;
  while (k1 != 0) {
    nov = nov->prev;
    countOp++;
    k1--;
  }
  if (!nov->light)
    return k2;
  else
    return getLength();
}
