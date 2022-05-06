// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {}
int Train::getLength() {
  int w = 0, i = 0;
  first->light = true;
  Cage *t = first;
  while (true) {
    ++i;
    t = t->next;
    ++countOp;
    if (t->light) {
      w = i;
      t->light = false;
      int j = i;
      for (j; j > 0; j--) {
        t = t->prev;
        ++countOp;
        --i;
      }
      if (t->light == false) {
        return w;
      }
    }
  }
}
int Train::getOpCount() {
  return countOp;
}
void Train::addCage(bool light) {
  if (first && last) {
    last->next = add(light);
    last->next->prev = last;
    last = last->next;
    if (!last->next) {
      last->next = first;
    }
    if (!first->prev) {
      first->prev = last;
    }
  } else {
    first = add(light);
    last = first;
  }
}
