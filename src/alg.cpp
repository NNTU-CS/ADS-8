// Copyright 2021 NNTU-CS
#include "bst.h"

#include <cctype>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filePath) {
  std::ifstream inputStream(filePath);
  if (!inputStream) {
    std::cerr << "ERROR " << filePath << std::endl;
  return;
}

std::string wordBuffer;
char character;
while (inputStream.get(character)) {
  if (isalpha(character)) {
    wordBuffer += tolower(static_cast<unsigned char>(character));
  } else if (!wordBuffer.empty()) {
    tree.insert(wordBuffer);
    wordBuffer.clear();
  }
}
  if (!wordBuffer.empty()) {
    tree.insert(wordBuffer);
  }
  inputStream.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> wordCounts;
  auto collectNode = [&wordCounts](BST<std::string>::Node* currentNode) {
    wordCounts.emplace_back(currentNode->key, currentNode->count);
  };
  tree.inOrder(collectNode);
  std::sort(wordCounts.begin(), wordCounts.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  const char* output_filename = "output.txt";
  std::ofstream outputFile(output_filename);
  if (!outputFile) {
    std::cerr << "Ошибка при открытии файла для записи: " << output_filename << std::endl;
    return;
  }

  for (const auto& entry : wordCounts) {
    std::cout << entry.first << ": " << entry.second << std::endl;
  }

    for (const auto& entry : wordCounts) {
      outputFile << entry.first << ": " << entry.second << std::endl;
    }
}


