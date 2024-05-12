// Copyright 2022 CheginArtyom
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
    struct Cage {
        bool light; // состояние лампочки
        Cage *next;
        Cage *prev;
    };
    int countOp = 0; // счетчик шагов (число переходов из вагона в вагон)
    Cage *first; // точка входа в поезд (первый вагон)
    Cage *end;
 public:
    Train();
    void addCage(bool light); // добавить вагон с начальным состоянием лампочки
    int getLength();          // вычислить длину поезда
    int getOpCount();         // вернуть число переходов (из вагона в вагон)
};
#endif  // INCLUDE_TRAIN_H_
