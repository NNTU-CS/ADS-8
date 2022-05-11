// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Cage {
    bool glim;
    Cage *next;
    Cage *prev;
  };
  int countOp; // счетчик шагов (число переходов из вагона в вагон)
  Cage *first; // точка входа в поезд (первый вагон)
 public:
  Train();
  void addCage(bool glim); // добавить вагон с начальным состоянием лампочки
  int getLength();// вычислить длину поезда
  int getOpCount();
};

#endif  // INCLUDE_TRAIN_H_
