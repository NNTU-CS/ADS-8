// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "bst.h"

static bool isAsciiLetter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalpha(uc) && !(uc & 0x80);
}

void makeTree(WordTree<std::string>& tree, const char* filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File error!\n";
        return;
    }
    std::string buf;
    char ch;
    while (in.get(ch)) {
        if (isAsciiLetter(ch)) {
            buf.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        } else if (!buf.empty()) {
            tree.add(buf);
            buf.clear();
        }
    }
    if (!buf.empty()) {
        tree.add(buf);
    }
}

void printFreq(WordTree<std::string>& tree) {
    auto stats = tree.getFreqs();
    std::sort(stats.begin(), stats.end(),
              [](auto& a, auto& b) {
                  return a.second > b.second
                         || (a.second == b.second && a.first < b.first);
              });
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Cannot open result file\n";
        return;
    }
    for (auto& p : stats) {
        std::cout << p.first << ": " << p.second << "\n";
        out << p.first << ": " << p.second << "\n";
    }
}