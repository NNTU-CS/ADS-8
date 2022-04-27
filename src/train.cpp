// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() :countOp(0), first(nullptr), tail(nullptr) {}

Train::Cage *Train::create(bool light) {
  Cage *temp = new Cage;
  temp->light = light;
  temp->next = nullptr;
  temp->prev = nullptr;
  return temp;
}

int Train::getOpCount() {
  return countOp;
}

void Train::addCage(bool light) {
  if (first && tail) {
    tail->next = create(light);
    tail->next->prev = tail;
    tail = tail->next;
    if (!tail->next) {
      tail->next = first;
    }
    if (!first->prev) {
      first->prev = tail;
    }
  } else {
    first = create(light);
    tail = first;
  }
}

int Train::getLength() {
  first->light = true;
  Cage *temp = first;
  int tempCount = 0, length = 0;
  while (true) {
    ++countOp;
    ++tempCount;
    temp = temp->next;
    if (temp->light) {
      int tmp = tempCount;
      temp->light = false;
      for (int i = tempCount; tempCount; --tempCount, ++countOp) {
        temp = temp->prev;
      }
      if (!temp->light) {
        length = tmp;
        break;
      }
    }
  }
  return length;
}
