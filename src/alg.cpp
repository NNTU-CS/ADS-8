// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <cctype>
#include  <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  char ch;

  while (file.get(ch)) {
        // Convert uppercase to lowercase
    ch = std::tolower(ch);
        
        // If character is a letter, add it to current word
    if (std::isalpha(ch)) {
      currentWord += ch;
    }
        // If we encounter a non-letter and we have a word, process it
    else if (!currentWord.empty()) {
      tree.insert(currentWord);
    currentWord.clear();
    }
  }

    // Process the last word if exists
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto frequencyData = tree.getFrequencyData();
    
    // Print to console
  for (const auto& [word, freq] : frequencyData) {
    std::cout << word << ": " << freq << std::endl;
  }
    
    // Save to file
  std::ofstream outFile("result/freq.txt");
  if (outFile) {
    for (const auto& [word, freq] : frequencyData) {
      outFile << word << ": " << freq << std::endl;
    }
    outFile.close();
  } else {
    std::cout << "Error: Could not open result/freq.txt for writing" << std::endl;
  }
} 
