// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

template<typename T>
class BST {
 private:
struct Node {
T element;
int cnt;
Node* left;
Node* right; ///
explicit Node(const T& elem) : element(elem), cnt(1), left(nullptr), right(nullptr) {}
};
Node* root = nullptr;
Node* addNode(Node* node, const T& value) {
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

Node* searchNode(Node* node, const T& value) const {
if (!node || node->element == value) {
return node;
}
return value < node->element ? searchNode(node->left, value) : searchNode(node->right, value);
}
void inorderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
if (node) {
inorderTraversal(node->right, result);
result.emplace_back(node->element, node->cnt);
inorderTraversal(node->left, result);
}
}
int calcDepth(Node* node) const {
if (!node) return 0;
int leftDepth = calcDepth(node->left);
int rightDepth = calcDepth(node->right);
return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

void clearTree(Node* node) {
if (node) {
clearTree(node->left);
clearTree(node->right); ///
delete node;
}
}

 public:
BST() : root(nullptr) {}
~BST() {clear();}
void add(const T& value) { root = addNode(root, value);}
void getSorted(std::vector<std::pair<T, int>>& result) const { inorderTraversal(root, result); }
int search(const T& value) const {
Node* foundNode = searchNode(root, value);
return foundNode ? foundNode->cnt : 0;
}
int depth() const {
int calculatedNodeDepth = calcDepth(root);
return (calculatedNodeDepth > 0) ? (calculatedNodeDepth - 1) : 0;
}
void clear() {clearTree(root); root = nullptr;}
};
#endif  // INCLUDE_BST_H_
