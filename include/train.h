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
    int countOp;
    Cage *first;
 public:
    Train();
    void addCage(bool light);
    int getLength();
    int getOpCount();
};
#endif  // INCLUDE_TRAIN_H_
