// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "bst.h"

static bool isLatin(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) && (c & 0x80) == 0;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream f(filename);
    if (!f) { std::cout << "File error!\n"; return; }
    std::string w;
    char ch;
    while (f.get(ch)) {
        if (isLatin(ch)) w += char(std::tolower((unsigned char)ch));
        else if (!w.empty()) { tree.insert(w); w.clear(); }
    }
    if (!w.empty()) tree.insert(w);
}

void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getNodes();
    std::sort(nodes.begin(), nodes.end(),
              [](auto a, auto b){ return a->count > b->count; });

    std::ofstream out("result/freq.txt");
    for (auto n : nodes) {
        std::cout << n->key << " : " << n->count << "\n";
        out << n->key << " : " << n->count << "\n";
    }
    out.close();
}