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
  int countOp, stepsForward; // счетчик шагов
  Cage *first, *current; // точка входа в поезд (первый вагон)
  Train::Cage* create(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
  }
 public:
  Train() : countOp(0), first(nullptr), current(nullptr) {}
  void addCage(bool); // добавить вагон с начальным состоянием лампочки
  int getLength(); // вычислить длину поезда
  int getOpCount(); // вернуть число переходов (из вагона в вагон)
};
#endif  // INCLUDE_TRAIN_H_
