// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <functional>

template <typename T>
class BST {
private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insert(Node* node, T value);
  Node* search(Node* node, T value) const;
  int depth(Node* node) const;
  void inOrder(Node* node, std::function<void(const T&, int)> visit) const;
  void clear(Node* node);

public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) { root = insert(root, value); }
  int search(T value) const;
  int depth() const { return depth(root); }
  void inOrder(std::function<void(const T&, int)> visit) const { inOrder(root, visit); }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

template <typename T>
typename BST<T>::Node* BST<T>::insert(Node* node, T value) {
  if (!node) {
    return new Node(value);
  }
  if (value == node->key) {
    node->count++;
  }
  else if (value < node->key) {
    node->left = insert(node->left, value);
  }
  else {
    node->right = insert(node->right, value);
  }
  return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::search(Node* node, T value) const {
  if (!node || node->key == value) {
    return node;
  }
  if (value < node->key) {
    return search(node->left, value);
  }
  else {
    return search(node->right, value);
  }
}

template <typename T>
int BST<T>::search(T value) const {
  Node* node = search(root, value);
  return node ? node->count : 0;
}

template <typename T>
int BST<T>::depth(Node* node) const {
  if (!node) {
    return 0;
  }
  int leftDepth = depth(node->left);
  int rightDepth = depth(node->right);
  return std::max(leftDepth, rightDepth) + 1;
}

template <typename T>
void BST<T>::inOrder(Node* node, std::function<void(const T&, int)> visit) const {
  if (node) {
    inOrder(node->left, visit);
    visit(node->key, node->count);
    inOrder(node->right, visit);
  }
}

template <typename T>
void BST<T>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}
#endif  // INCLUDE_BST_H_
