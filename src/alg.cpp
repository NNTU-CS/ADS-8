// Copyright 2021 NNTU-CS
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include "bst.h"
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string cur = "";
  while (!file.eof()) {
    char ch = file.get();
    if (ch >= 'A' && ch <= 'Z') {
      ch = tolower(ch);
      cur.push_back(ch);
    } else if (ch >= 'a' && ch <= 'z') {
      cur.push_back(ch);
    } else {
      if (cur != "") {
        tree.add(cur);
        cur = "";
      } else {
        continue;
      }
    }
  }
  file.close();
}

void printFreq(BST<std::string>& tree) { auto arr = tree.toVector();
  std::sort(arr.begin(), arr.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
  std::ofstream out("freq.txt");
  for (const auto& twos : arr) {
    std::cout << twos.first << " - " << twos.second << std::endl;
    out << twos.first << " - " << twos.second << std::endl;
  }
  out.close();
}
