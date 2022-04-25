// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage* Train::create(bool _light) {
  Cage *cage = new Cage;
  cage->light = _light;
  cage->next = nullptr;
  cage->prev = nullptr;
  return cage;
}

void Train::addCage(bool _light) {
  if (last && first) {
    last->next = nullptr;
    last->next = create(_light);
    last->next->prev = last;
    last = last->next;
    last->next = first;
    first->prev = last;
  } else {
      first = create(_light);
      last = first;
  }
}

int Train::getLength() {
  Cage *temp = first;
  bool current;
  int steps_count = 0;

  current = temp->light;
  
  while (temp) {
    temp = temp -> next;
    ++steps_count;
    if (temp->light == current) {
      temp->light = !current;
      break;
    }
  }

  countOp += ((steps_count - 1) * 2);

  for (int i = 0; i < steps_count; ++i) {
    temp = temp->prev;
  }

  if (temp->light != current) {
    return steps_count;
  }

  return getLength();
}

int Train::getOpCount() {
  return countOp;
}
