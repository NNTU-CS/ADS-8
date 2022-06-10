// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
  Cage* cell = new Cage;
  cell->light = light;
  cell->next = cell->prev = nullptr;
  if (first == nullptr) {
    first = cell;
  } else if (first->next == nullptr) {
    first->next = first->prev = cell;
    cell->next = cell->prev = first;
  } else {
    first->prev->next = cell;
    cell->prev = first->prev;
    first->prev = cell;
    cell->next = first;
  }
}

int Train::getLength() {
  int Count = 0;
  Cage* tmp = first;
  first->light = true;
  while (true) {
    tmp = tmp->next;
    Count++;
    countOp++;
    if (tmp->light == true) {
      tmp->light = false;
      for (int i = 0; i < Count; i++) {
        tmp = tmp->prev;
        countOp++;
      }
    if (tmp->light == false) {
      return Count;
    }
      Count = 0;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
