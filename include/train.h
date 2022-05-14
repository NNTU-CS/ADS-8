// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
    struct Cage {
        bool light;
        Cage* next = nullptr;
        Cage* prev = nullptr;
    };
    int countOp = 0;
    Cage* first = new Cage;
    bool firstAdded = false;
 public:
    void addCage(bool);
    int getLength();
    int getOpCount() { return countOp; }
};

#endif  // INCLUDE_TRAIN_H_
