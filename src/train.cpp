// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

Train::Train() : countOp(0), first(nullptr) {}

int Train::getOpCount() { return countOp; }

void Train::addCage(bool light) {
  Cage* cage = new Cage;
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
  int length = 0;
  int train_length;
  countOp = 0;
  first->light = true;
  Cage* temp = first;
  while (true) {
    countOp++;
    length++;
    temp = temp->next;
    if (temp->light) {
      temp->light = false;
      train_length = length;
      for (train_length; train_length > 0; train_length--) {
        temp = temp->prev;
        countOp++;
      }
      if (!temp->light) {
        return length;
      }
      length = train_length;
    }
  }
  return train_length;
}
