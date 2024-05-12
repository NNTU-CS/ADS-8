// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
  Cage* cage = new Cage;
  cage->light = light;
  if (first == nullptr) {
    cage->next = cage;
    cage->prev = cage;
    first = cage;
  } else {
    cage->next = first;
    cage->prev = first->prev;
    first->prev->next = cage;
    first->prev = cage;
  }
}
int Train::getLength() {
  first->light = true;
  int cnt = 1;
  Cage* curr = first;
  while (first->light) {
    cnt = 1;
    curr = first->next;
    while (!curr->light) {
      curr = curr->next;
      cnt++;
    }
    curr->light = false;
    countOp += 2 * cnt;
  }
  return cnt;
}
int Train::getOpCount() {
  return countOp;
}
