// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  if (first == nullptr) {
    first = newCage;
    newCage->prev = newCage;
    newCage->next = newCage;
    return;
  }
  newCage->next = first;
  newCage->prev = first->prev;
  first->prev->next = newCage;
  first->prev = newCage;
}
int Train::getLength() {
  if (first == nullptr)
    return 0;
  Cage* now = first;
  now->light = 1;
  int k = 1;
  while (true) {
    now = now->next;
    while (now->light == 0) {
      now = now->next;
      k += 1;
      countOp++;
    }
    countOp++;
    now->light = 0;
    for (int i = k; i > 0; i--) {
      countOp++;
      now = now->prev;
    }
    if (now->light == 0)
      return k;
    k = 1;
  }
}
int Train::getOpCount() {
  return countOp;
}
