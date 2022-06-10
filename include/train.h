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
  int countOp; // счетчик шагов (число переходов из вагона в вагон)
  Cage *first; // точка входа в поезд (первый вагон)
    struct Cage {
        bool light;
        Cage* next = nullptr;
        Cage* prev = nullptr;
    };
    int countOp = 0;
    Cage* first = new Cage;
    bool firstAdded = false;
 public:
  Train();
  void addCage(bool light); // добавить вагон с начальным состоянием лампочки
  int getLength();          // вычислить длину поезда
  int getOpCount();         // вернуть число переходов (из вагона в вагон)
    int getLength();
    int getOpCount() { return countOp; }
    void addCage(bool);
};

#endif  // INCLUDE_TRAIN_H_
