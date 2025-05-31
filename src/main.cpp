// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>

void processTextFile(const std::string& filename);

int main() {
  try {
    const std::string filename = "src/war_peace.txt";
    FrequencyTree<std::string> word_tree;
    
    buildFrequencyTree(word_tree, filename);
    
    std::cout << "Tree depth: " << word_tree.getDepth() << std::endl;
    displayFrequencyResults(word_tree);
    
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
