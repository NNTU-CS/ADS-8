// Copyright 2021 NNTU-CS
#include "train.h"

Train :: Cage *Train::create(bool light) {
  Cage* value = new Cage;
  value -> light = light;
  value -> next = value -> prev = nullptr;
  return value;
}

Train :: Train() {
  first = current = nullptr;
  countOp = length = count = 0;
}

void Train :: addCage(bool light) {
  if (!first) {
    first = create(light);
    current = first;
  } else {
    current -> next = create(light);
    current -> next -> prev = current;
    current = current -> next;
    if (!current -> next) {
      current -> next = first;
    } else {
      first -> prev = current;
    }
  }
}

int Train::getLength() {
  first -> light = true;
  current = first;
  int shagi;
  while (true) {
    ++countOp, ++count;
    current = current -> next;
    if (current -> light) {
      shagi = count;
      current -> light = false;
      while ((current -> prev != nullptr) && (current -> light == false)) {
        current = current -> prev;
        --count, ++countOp;
      }
      if (!current -> light) {
        length = shagi;
        break;
      }
    }
  }
  countOp += length;
  return length;
}

int Train :: getOpCount() {
  return countOp;
}
