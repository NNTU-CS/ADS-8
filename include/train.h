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
  Train::Cage* create(bool _light);

  Cage *first;
  Cage *last;

  int countOp = 0;

 public:
  Train() : first(nullptr), last(nullptr) { }
  void addCage(bool _light);
  int getLength();
  int getOpCount();
  ~Train();
};
#endif  // INCLUDE_TRAIN_H_
