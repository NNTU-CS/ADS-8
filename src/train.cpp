// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), first(nullptr) {}

void Train::addCage(bool a) {
  Cage *cage = new Cage;
  cage->light = a;
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
  int size = 0;
  int size_temp;
  countOp = 0;
  first->light = true;
  Cage* temp = first;
  while (true) {
    size++;
    countOp++;
    temp = temp->next;
    if (temp->light) {
      size_temp = size;
      temp->light = false;
      for (size_temp = size; size_temp > 0; size_temp--) {
        temp = temp->prev;
        countOp++;
      }
      if (!temp->light) {
        return size;
      }
      if (temp->light) {
        size = size_temp;
      }
    }
  }
  return 0;
}

int Train::getOpCount() {
  return countOp;
}
