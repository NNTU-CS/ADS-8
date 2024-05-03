// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;

  if (first == nullptr) {
    first = newCage;
    first->next = first;
    first->prev = first;
  } else {
    newCage->next = first;
    newCage->prev = first->prev;
    first->prev->next = newCage;
    first->prev = newCage;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;
  int length = 0;
  Cage* current = first;

  do {
    length++;
    current = current->next;
  } while (current != first);

  return length;
}

int Train::getOpCount() {
  if (first == nullptr) return 0;
  int countOp = 0;
  int length = 0;
  Cage* current = first;
  first->light = true;
  do {
    length++;
    current = current->next;
    if (current->light == first->light) {
      countOp += length;
      countOp += length;
    }
  } while (current != first);

  return countOp;
}
