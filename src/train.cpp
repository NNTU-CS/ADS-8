// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
  Cage* nCage = new Cage;
  nCage->light = light;
  if (first == nullptr) {
    first = nCage;
    nCage->prev = nCage;
    nCage->next = nCage;
    return;
  }
  nCage->next = first;
  nCage->prev = first->prev;
  first->prev->next = nCage;
  first->prev = nCage;
}
int Train::getLength() {
  if (first == nullptr)
    return 0;
  Cage* per = first;
  per->light = 1;
  int c = 1;
  while (true) {
    per = per->next;
    while (per->light == 0) {
      per = per->next;
      c += 1;
      countOp++;
    }
    countOp++;
    per->light = 0;
    for (int i = c; i > 0; i--) {
      countOp++;
      per = per->prev;
    }
    if (per->light == 0)
      return c;
    c = 1;
  }
}
int Train::getOpCount() {
  return countOp;
}
