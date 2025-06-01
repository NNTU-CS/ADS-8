// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  <cctype>
#include  <algorithm>
#include  <string>
#include  <cstring>
#include  "bst.h"

void processFile(BST<std::string>& tree, std::ifstream& file) {
char c;
std::string currentWord;
while (file.get(c)) {
unsigned char uc = static_cast<unsigned char>(c);
if (std::isalpha(uc)) {
currentWord += static_cast<char>(std::tolower(uc));
} else {
if (!currentWord.empty()) {
tree.add(currentWord);
currentWord.clear();
}
}
}
if (!currentWord.empty()) {
tree.add(currentWord);
}
}

void makeTree(BST<std::string>& tree, const char* filename) {
std::ifstream file(filename);
if (!file.is_open()) {
std::cout << "Error" << std::endl;
return;
}
if (file.is_open()) {
processFile(tree, file);
file.close();
} else {
std::cerr << "Error" << std::endl;
}
}

void printFreq(BST<std::string>& tree) {
std::vector<std::pair<std::string, int>> result;
tree.getSorted(result);
std::ofstream outFile("result/freq.txt");
for (const auto& pair : result) {
std::cout << pair.first << ": " << pair.second << std::endl;
outFile << pair.first << " " << pair.second << std::endl;
}
outFile.close();
}
