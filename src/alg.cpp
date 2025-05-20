// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    unsigned char uch = static_cast<unsigned char>(ch);
    if (std::isalpha(uch)) {
      uch = std::tolower(uch);
      if (uch >= 'a' && uch <= 'z') {
        word += static_cast<char>(uch);
      }
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

struct WordFreq {
  std::string word;
  int count;
};

template <typename T>
void collectInorder(const BST<T>& tree, std::vector<WordFreq>& result) {
  tree.inorder([&result](const T& val, int count) {
    result.push_back({val, count});
  });
}

void printFreq(BST<std::string>& tree) {
  std::vector<WordFreq> words;
  collectInorder(tree, words);

  std::sort(words.begin(), words.end(),
            [](const WordFreq& a, const WordFreq& b) {
              return a.count > b.count;
            });

  std::filesystem::create_directories("result");
  std::ofstream fout("result/freq.txt");

  for (const auto& wf : words) {
    std::cout << std::setw(6) << wf.count << " - " << wf.word << "\n";
    fout << wf.count << " - " << wf.word << "\n";
  }

  fout.close();
}
