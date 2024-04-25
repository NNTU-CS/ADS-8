// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private :
    struct Cage {
        bool light;
        Cage *next;
        Cage *prev;
    };

    int iPerem = 0;
    int countOp;
    Cage *first;
    Cage *TailOfTrain;

 public :
    Train() : first(nullptr), TailOfTrain(nullptr), countOp(0) {
    }

    void addCage(bool light);

    int getLength();

    int getOpCount();
};
#endif  // INCLUDE_TRAIN_H_
