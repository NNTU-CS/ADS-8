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
  int shagi;
  Cage *first; // точка входа в поезд (первый вагон)
  Cage *now;
  Train::Cage* newvagon(bool light) {
    Cage* vagon = new Cage;
    vagon->prev = nullptr;
    vagon->next = nullptr;
    vagon->light = light;
    return vagon;
  }
 public:
  Train() : countOp(0), first(nullptr), now(nullptr) {}
  void addCage(bool light); // добавить вагон с начальным состоянием лампочки
  int getLength();          // вычислить длину поезда
  int getOpCount();         // вернуть число переходов (из вагона в вагон)
};
#endif  // INCLUDE_TRAIN_H_
