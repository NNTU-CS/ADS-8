// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fl(filename);
    if (!fl) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string crrWrd;
    while (!fl.eof()) {
        char ch = fl.get();
        if (isalpha(ch)) {
            crrWrd += tolower(ch);
        } else {
            if (!crrWrd.empty()) {
                tree.insrt(crrWrd);
                crrWrd.clear();
            }
        }
    }
    if (!crrWrd.empty()) {
        tree.insrt(crrWrd);
    }
    fl.close();
}

struct WrdFrq {
    std::string wrd;
    int cnt;
};

bool cmpWrdFrq(const WrdFrq& a, const WrdFrq& b) {
    return a.cnt > b.cnt;
}

void printFreq(BST<std::string>& tree) {
    std::vector<WrdFrq> wrds;
    auto clctWrds = [&wrds](BST<std::string>::Node* node) {
        wrds.push_back({node->key, node->cnt});
    };
    tree.inOrd(clctWrds);
    std::sort(wrds.begin(), wrds.end(), cmpWrdFrq);
    for (const auto& wf : wrds) {
        std::cout << wf.wrd << " - " << wf.cnt << std::endl;
    }
    
    std::ofstream out("result/freq.txt");
    for (const auto& wf : wrds) {
        out << wf.wrd << " - " << wf.cnt << std::endl;
    }
    out.close();
}
