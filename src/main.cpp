// Copyright 2022 NNTU-CS
#include <iostream>
#include "train.h"

int main() {
  Train train;
  int count = 60;

  while (count--)
    train.addCage(false);

  std::cout << train.getLength() << std::endl;
  std::cout << train.getOpCount() << std::endl;
  return 0;
}
