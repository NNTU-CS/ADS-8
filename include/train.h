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
    void calculate();
    int countOp = 0;
    int length = 1;
    bool calculated = false;
    Cage *first = nullptr;
    Cage *last = nullptr;
 public:
    void addCage(bool light);
    int getLength();
    int getOpCount();
};
#endif  // INCLUDE_TRAIN_H_
