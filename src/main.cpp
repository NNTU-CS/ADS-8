// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);

int main() {
  BST<std::string> tree;
  const char* filename = "src/war_peace.txt";
  makeTree(tree, filename);

  auto wordsVec = tree.toVector();
  std::sort(wordsVec.begin(), wordsVec.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::ofstream out("result/freq.txt");
  for (const auto& pair : wordsVec) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    out << pair.first << " - " << pair.second << std::endl;
  }

  return 0;
}
