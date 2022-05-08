// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Cage {
    bool light; // состояние лампочки
    Cage *next;
    Cage *prev;
  };

 int countOp, stepsForward;
 Cage *first, *current;
 Train::Cage* create(bool light) {
  Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
 }
 
 public:
  Train() : countOp(0), first(nullptr), current(nullptr) {}
  void addCage(bool);
  int getLength();
  int getOpCount();
};
#endif  // INCLUDE_TRAIN_H_
