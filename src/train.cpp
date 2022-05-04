// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage *Train::create(bool light) {
  Cage* item = new Cage;
  item->light = light;
  item->next = item->prev = nullptr;
  return item;
}

Train::Train() {
  first = current = nullptr;
  countOp = length = Count = 0;
}

void Train::addCage(bool light) {
  if (!(first)) {
    first = create(light);
    current = first;
  } else {
    current->next = create(light);
    current->next->prev = current;
    current = current->next;
    if (!current->next) {
      current->next = first;
    } else {
      first->prev = current;
    }
  }
}

int Train::getLength() {
  first->light = true;
  current = first;
  int temp;
  while (true) {
    ++countOp, ++Count;
    current = current->next;
    if (current->light) {
      temp = Count;
      current->light = false;
      if ((current->prev) != nullptr) {
        while (current->light == false) {
          current = current->prev;
          --Count, ++countOp;
        }
      }
      if (!current->light) {
        length = temp;
        break;
      }
    }
  }
  countOp += length;
  return length;
}

int Train::getOpCount() {
  return countOp;
}
