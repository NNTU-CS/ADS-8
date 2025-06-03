// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* fname) {
  std::ifstream input(fname);
  if (!input) {
    std::cerr << "Unable to open file!" << std::endl;
    return;
  }

  std::string token;
  char symbol;
  while (input.get(symbol)) {
    if (std::isalpha(static_cast<unsigned char>(symbol))) {
      token += static_cast<char>(std::tolower(symbol));
    } else if (!token.empty()) {
      tree.add(token);
      token.clear();
    }
  }

  if (!token.empty()) {
    tree.add(token);
  }

  input.close();
}

void printFreq(const BST<std::string>& tree) {
  auto list = tree.getWords();

  std::sort(list.begin(), list.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.second > rhs.second;
  });

  std::ofstream output("result/freq.txt");
  if (!output) {
    std::cerr << "Can't write to result file!" << std::endl;
    return;
  }

  for (const auto& [word, count] : list) {
    std::cout << word << "-" << count << '\n';
    output << word << "-" << count << '\n';
  }

  output.close();
}
