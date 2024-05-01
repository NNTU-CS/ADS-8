// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
  Cage { false, nullptr, nullptr };
}

void Train::addCage(bool light) {
  if (first == nullptr) {
    first = new Cage;
    first->next = first;
    first->prev = first;
    first->light = light;
  } else {
    Cage* temp = new Cage;
    temp->light = light;
    Cage* pos = first;
    while (pos->next != first)
      pos = pos->next;
    temp->prev = pos;
    temp->next = first;
    first->prev = temp;
    pos->next = temp;
  }
}

int Train::getLength() {
  int length = 0, count = 0;
  Cage* wag = first;
  wag->light = true;
  while (1) {
    while (1) {
      wag = wag->next;
      countOp++;
      count++;
      if (wag->light) {
        wag->light = false;
        break;
      }
    }
    length = count;
    for (count; count != 0; count--) {
      wag = wag->prev;
      countOp++;
    }
    if (wag->light == false) {
      return length;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
