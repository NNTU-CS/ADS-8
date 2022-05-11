// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
    struct Cage {
        bool StateOfLight; // состояние лампочки
        Cage* next;
        Cage* prev;
    };
    int countOp; // счетчик шагов (число переходов из вагона в вагон)
    Cage* first, *tail; // точка входа в поезд (первый вагон)
 public:
    Train::Cage* create(bool StateOfLight) {
        Cage* cage = new Cage;
        cage->StateOfLight = StateOfLight;
        cage->next = nullptr;
        cage->prev = nullptr;
        return cage;
    }
    Train() : countOp(0), first(nullptr), tail(nullptr) {}
    void addCage(bool light); // добавить вагон с начальным состоянием лампочки
    int getLength();          // вычислить длину поезда
    int getOpCount();         // вернуть число переходов (из вагона в вагон)
};
#endif  // INCLUDE_TRAIN_H_
