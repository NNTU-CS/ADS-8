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

template<typename T>
typename BST<T>::Node* BST<T>::searchNode(Node* node, const T& value) const {
if (!node || node->element == value) {
return node;
}
return value < node->element ? searchNode(node->left, value) : searchNode(node->right, value);
}

template<typename T>
int BST<T>::calcDepth(Node* node) const {
if (!node) return 0;
int leftDepth = calcDepth(node->left);
int rightDepth = calcDepth(node->right);
return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

template<typename T>
void BST<T>::inorderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
if (node) {
inorderTraversal(node->right, result);
result.emplace_back(node->element, node->cnt);
inorderTraversal(node->left, result);
}
}

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

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* node, const T& value) {
if (!node) return new Node(value);
if (value < node->element) {
node->left = addNode(node->left, value);
} else if (value > node->element) {
node->right = addNode(node->right, value);
} else {
node->cnt++;
}
return node;
}
