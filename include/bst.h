// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template <typename T>
class BST {
 public:
  BST();
  ~BST();
  void insert(const T& value);
  bool search(const T& value) const;
  int depth() const;
  void toVector(std::vector<std::pair<T, int>>* vec) const;

 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  Node* insertNode(Node* node, const T& value);
  Node* searchNode(Node* node, const T& value) const;
  int depthNode(Node* node) const;
  void clearNode(Node* node);
  void collectNode(Node* node, std::vector<std::pair<T, int>>* vec) const;
};

template <typename T>
BST<T>::BST() : root_(nullptr) {}

template <typename T>
BST<T>::~BST() {
  clearNode(root_);
}

template <typename T>
void BST<T>::insert(const T& value) {
  root_ = insertNode(root_, value);
}

template <typename T>
typename BST<T>::Node* BST<T>::insertNode(Node* node, const T& value) {
  if (node == nullptr) {
    return new Node(value);
  }
  if (value < node->key) {
    node->left = insertNode(node->left, value);
  } else if (value > node->key) {
    node->right = insertNode(node->right, value);
  } else {
    node->count++;
  }
  return node;
}

template <typename T>
bool BST<T>::search(const T& value) const {
  return (searchNode(root_, value) != nullptr);
}

template <typename T>
typename BST<T>::Node* BST<T>::searchNode(Node* node, const T& value) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (value < node->key) {
    return searchNode(node->left, value);
  } else if (value > node->key) {
    return searchNode(node->right, value);
  } else {
    return node;
  }
}

template <typename T>
int BST<T>::depth() const {
  return depthNode(root_);
}

template <typename T>
int BST<T>::depthNode(Node* node) const {
  if (node == nullptr) {
    return 0;
  }
  int left_depth = depthNode(node->left);
  int right_depth = depthNode(node->right);
  return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

template <typename T>
void BST<T>::toVector(std::vector<std::pair<T, int>>* vec) const {
  collectNode(root_, vec);
}

template <typename T>
void BST<T>::collectNode(Node* node, std::vector<std::pair<T, int>>* vec) const {
  if (node == nullptr) {
    return;
  }
  collectNode(node->left, vec);
  vec->emplace_back(node->key, node->count);
  collectNode(node->right, vec);
}

template <typename T>
void BST<T>::clearNode(Node* node) {
  if (node == nullptr) {
    return;
  }
  clearNode(node->left);
  clearNode(node->right);
  delete node;
}

#endif  // INCLUDE_BST_H_
