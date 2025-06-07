// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  <algorithm>
#include  <cctype>
#include  <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "File error: " << filename << '\n';
        return;
    }

    std::string word;
    char        ch;

    auto flush_word = [&]{
        if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    };

    while (file.get(ch)) {
        unsigned char uch = static_cast<unsigned char>(ch);

        if (std::isalpha(uch) && uch < 128) {
            word.push_back(static_cast<char>(std::tolower(uch)));
        } else {
            flush_word();
        }
    }
    flush_word();
}


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, std::size_t>> v;
    tree.inorder([&](const std::string& w, std::size_t c){
        v.emplace_back(w, c);
    });

    std::sort(v.begin(), v.end(),
              [](const auto& a, const auto& b){
                  return (a.second == b.second) ? a.first < b.first
                                                : a.second > b.second;
              });

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Cannot open result/freq.txt for writing!\n";
    }

    for (const auto& [w, c] : v) {
        std::cout << w << " : " << c << '\n';
        if (out) out << w << ' ' << c << '\n';
    }
}
