// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class NewTrain {
 private:
  struct Compartment {
    bool light; 
    Compartment *next;
    Compartment *prev;
  };
  int moveCount; 
  Compartment *start; 

 public:
  NewTrain();
  void addCompartment(bool light); 
  int getLength();          
  int getMoveCount();       
};
#endif  // INCLUDE_TRAIN_H_
