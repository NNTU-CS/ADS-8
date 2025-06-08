// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"

#include <algorithm>
#include <string>
#include <vector>

void makeTree(BST<std::string>& bstInstance, const char* inputFile) {
  std::ifstream inputStream(inputFile);
  if (!inputStream) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  while (inputStream) {
    char character = inputStream.get();
    if (isupper(character)) character = tolower(character);
    
    if (islower(character)) {
      currentWord += character;
    } else if (!currentWord.empty()) {
      bstInstance.add(currentWord);
      currentWord.clear();
    }
  }
}

void printFreq(const BST<std::string>& bstInstance) {
  auto sortedWords = bstInstance.array_words();
  
  std::sort(sortedWords.begin(), sortedWords.end(),
    [](const auto& first, const auto& second) {
      return first.second > second.second;
    });

  std::ofstream outputFile("result/freq.txt");
  if (!outputFile) {
    std::cerr << "Failed to open output file!" << std::endl;
    return;
  }

  for (const auto& wordData : sortedWords) {
    std::cout << wordData.first << "-" << wordData.second << '\n';
    outputFile << wordData.first << "-" << wordData.second << '\n';
  }
}
