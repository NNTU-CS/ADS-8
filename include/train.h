// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

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
  Train() : countOp(0), first(nullptr) {}
  void addCage(bool light);
  int getLength();
  int getOpCount() { return countOp; }
};
#endif  // INCLUDE_TRAIN_H_
