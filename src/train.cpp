// Copyright 2021 NNTU-CS
#include "train.h"
NewTrain::NewTrain() {
  moveCount = 0;
  start = nullptr;
}

void NewTrain::addCompartment(bool light) {
  if (start == nullptr) {
    start = new Compartment;
    start->light = light;
    start->next = start;
    start->prev = start;
    return;
  }
  Compartment* newCompartment = new Compartment;
  newCompartment->light = light;
  newCompartment->next = start->next;
  newCompartment->prev = start;
  start->next->prev = newCompartment;
  start->next = newCompartment;
}

int NewTrain::getLength() {
  if (!start->light) {
    start->light = true;
  }
  while (true) {
    int length = 1;
    int transition = 1;
    moveCount++;
    Compartment* current = start->next;
    while (!current->light) {
      current = current->next;
      transition++;
      moveCount++;
    }
    current->light = false;
    for (; transition > 1; transition--) {
      current = current->prev;
      length++;
      moveCount++;
    }
    moveCount++;
    if (!current->prev->light) {
      return length;
    }
  }
}

int NewTrain::getMoveCount() {
  return moveCount;
}
