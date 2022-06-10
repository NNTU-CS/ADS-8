// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
  Cage *cage = new Cage;
  cage->light = light;
  cage->prev = nullptr;
  cage->next = nullptr;
  if (first == nullptr) {
    first = cage;
  } else if (first->next == nullptr) {
    first->next = cage;
    cage->prev = first;
    first->prev = cage;
    cage->next = first;
  } else {
    first->prev->next = cage;
    cage->prev = first->prev;
    first->prev = cage;
    cage->next = first;
  }
}
int Train::getLength() {
  Cage* current = first;
  first->light = true;
  int l = 0;
  countOp = 0;
  while (true) {
    countOp += 1;
    l += 1;
    int tr_l;
    current = current->next;
    if (current->light) {
      current->light = false;
      tr_l = l;
      for (tr_l; tr_l > 0; tr_l--) {
        current = current->prev;
        countOp++;
      }
      if (!current->light) {
        return l;
      }
      l = tr_l;
    }
  }
}
int Train::getOpCount() {
  return countOp;
}
