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
  int lgth = 0;
  first->light = true;
  Cage* tmp = first;
  while (true) {
    lgth++;
    for (int i = 0; i < lgth; ++i) {
      tmp = tmp->next;
      ++countOp;
  }
    if (tmp->light) {
      tmp->light = false;
      for (int i = 0; i < lgth; ++i) {
        tmp = tmp->prev;
        countOp += 1;
      }
    } else {
      while (!tmp->light) {
        lgth++;
        tmp = tmp->next;
        countOp += 1;
      }
      tmp->light = false;
      for (int i = 0; i < lgth; ++i) {
        tmp = tmp->prev;
        countOp++;
      }
    }
    if (!tmp->light)
      break;
    }
  return lgth;
}

int Train::getOpCount() {
  return countOp;
}
