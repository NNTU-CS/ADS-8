// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstddef>

Train::Train() {
  countOp = 0;
  first = nullptr;
}
void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  newCage->next = nullptr;
  if (first == nullptr) {
    newCage->prev = nullptr;
    first = newCage;
    first->next = first;
  } else {
    Cage* current = first;
    while (current->next != first) {
      current = current->next;
    }
    current->next = newCage;
    newCage->prev = current;
    newCage->next = first;
    first->prev = newCage;
  }
}

int Train::getLength() {
  Cage* current = first;
  int length = 0;
  current->light = true;
  while (true) {
    current = current->next;
    length++;
    countOp++;
    if (current->light == true) {
      current->light = false;
      int maxLength = length;
      length = 0;
      for (int i = 0; i < maxLength; i++) {
        current = current->prev;
        countOp++;
      }
      if (current->light == false) return maxLength;
    }
  }
}
int Train::getOpCount() { return countOp; }
