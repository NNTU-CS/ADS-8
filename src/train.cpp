// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
  Cage*  n_cage = new Cage;
  n_cage->light = light;
  if (first == nullptr) {
    first = n_cage;
    first->next = first;
    first->prev = first;
  }
  n_cage->next = first;
  n_cage->prev = first->prev;
  first->prev->next = n_cage;
  first->prev = n_cage;
}

int Train::getLength() {
  Cage* current = first;
  current->light = true;
  int count = 0;
  while (current) {
    current = current->next;
    if (current->light == false) {
      count++;
      countOp++;
    } else {
      current->light = false;
      countOp++;
      count++;
      for (int i = 0; i < count; i++) {
        current = current->prev;
        countOp++;
      }
      if (current->light == false) return count;
      else
        count = 0;
    }
  }
  return 0;
}

int Train::getOpCount() {
  return countOp;
}
