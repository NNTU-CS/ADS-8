// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {}

void Train::addCage(bool light) {
  arr[last] = light;
  last += 1;
  if (!checked) {
    checked = true;
    started = light;
  }
}

int Train::getLength() { return last; }

int Train::getOpCount() {
  if (started) {
    return last * last + last;
  } else {
    return last * 2;
  }
}
