// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: cannot open " << filename << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
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
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto vec = tree.toVector();
    std::sort(vec.begin(), vec.end(),
              [](auto& a, auto& b) {
                  if (a.second != b.second)
                      return a.second > b.second;
                  return a.first < b.first;
              });
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "File error: cannot write to result/freq.txt" << std::endl;
        return;
    }
    for (auto& p : vec) {
        std::cout << p.first << " " << p.second << "\n";
        out << p.first << " " << p.second << "\n";
    }
    out.close();
}
