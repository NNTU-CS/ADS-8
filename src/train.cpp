// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage* Train::create(bool light) {
  Cage* cage = new Cage;
  cage->light = light;
  cage->next = nullptr;
  cage->prev = nullptr;
  return cage;
}

void Train::addCage(bool light) {
  if (last && first) {
    last->next = create(light);
    last->next->prev = last;
    last = last->next;
    first->prev = last;
    last->next = first;
  } else {
      first = create(light);
      last = first;
    }
}

int Train::getLength() {
  int length = 0;
  first->light = true;
  Cage* tempor = first;
  while (true) {
    length += 1;
    for (int j = 0; j < length; ++j) {
      tempor = tempor->next;
      countOp += 1;
    }
    if (tempor->light) {
      tempor->light = false;
      for (int j = 0; j < length; ++j) {
        tempor = tempor->prev;
        countOp += 1;
      }
    } else {
        while (!tempor->light) {
          length += 1;
          tempor = tempor->next;
          countOp += 1;
        }
        tempor->light = false;
          for (int j = 0; j < length; ++j) {
            tempor = tempor->prev;
            countOp += 1;
          }
      }
      if (!tempor->light) {
        break;
      }
    }
  return length;
}

int Train::getOpCount() {
  return countOp;
}
