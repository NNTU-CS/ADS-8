// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_


class Train {
 private:
  struct Cage {
@@ -10,7 +11,9 @@ class Train {
    Cage *prev;
  };
  int countOp; // счетчик шагов (число переходов из вагона в вагон)
  int count = 1, len = 0;
  Cage *first; // точка входа в поезд (первый вагон)
  Cage *last;
 public:
  Train();
  void addCage(bool light); // добавить вагон с начальным состоянием лампочки
  int getLength();          // вычислить длину поезда
  int getOpCount();         // вернуть число переходов (из вагона в вагон)
};
#endif  // INCLUDE_TRAIN_H_
