// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

class Train {
  private:
struct Cage {
bool light; 
Cage *next;
Cage *prev;
};
int countOp; 
Cage *first; 
  public:
Train() {
  first = nullptr;
  countOp = 0;
}

void addCage(bool light) {
  if (first == nullptr) {
    first = new Cage{light, nullptr, nullptr};
    first->next = first;
    first->prev = first;
  } else {
    Cage *newCage = new Cage{light, first, first->prev};
    first->prev->next = newCage;
    first->prev = newCage;
  }
}
int getLength() {
  if (first == nullptr) {
    return 0;
  }
  int length = 1;
  Cage *current = first->next;
  while (current != first) {
    length++;
    current = current->next;
  }
  return length;
}
int getOpCount() {
  return countOp;
}
};
