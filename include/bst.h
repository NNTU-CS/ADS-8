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
Node* right; ///
Node* left;
explicit Node(const T& elem) : element(elem), cnt(1), right(nullptr), left(nullptr) {}
};
Node* root = nullptr;
Node* addNode(Node* node, const T& value);
Node* searchNode(Node* node, const T& value) const;
void inorderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const;
int calcDepth(Node* node) const;
void clearTree(Node* node) {
if (node) {
clearTree(node->right); ///
clearTree(node->left);
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
/*if (!root) return 0;*/
return calcDepth(root);
}
void clear() {clearTree(root); root = nullptr;}
};
#endif  // INCLUDE_BST_H_
