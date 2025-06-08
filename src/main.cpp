// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
}
void printFreq(BST<std::string>& tree) {
  auto items = tree.getAll();
  std::sort(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });
  std::ofstream fout("result/freq.txt");
  for (const auto& pair : items) {
    std::cout << pair.first << " : " << pair.second << std::endl;
    fout << pair.first << " : " << pair.second << "\n";
  }
  fout.close();
}
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  BST<std::string> tree;
  makeTree(tree, argv[1]);
  printFreq(tree);
  return 0;
}
