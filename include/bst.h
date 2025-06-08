// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <functional>
#include <string>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  static Node* insert(Node* node, T value);
  static Node* search(Node* node, T value);
  static int depth(Node* node);
  static void inOrder(Node* node,
                      const std::function<void(const T&, int)>& visit);
  static void clear(Node* node);

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) { root = insert(root, value); }
  int search(T value) const;
  int depth() const { return root ? depth(root) : 0; }
  void inOrder(const std::function<void(const T&, int)>& visit) const {
    inOrder(root, visit);
  }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

template <typename T>
typename BST<T>::Node* BST<T>::insert(Node* node, T value) {
  if (node == nullptr) return new Node(value);
  if (value == node->key) {
    ++node->count;
  } else if (value < node->key) {
    node->left = insert(node->left, value);
  } else {
    node->right = insert(node->right, value);
  }
  return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::search(Node* node, T value) {
  if (node == nullptr || node->key == value) return node;
  return value < node->key ? search(node->left, value)
                           : search(node->right, value);
}

template <typename T>
int BST<T>::search(T value) const {
  Node* res = search(root, value);
  return res ? res->count : 0;
}

template <typename T>
int BST<T>::depth(Node* node) {
  return node ? std::max(depth(node->left), depth(node->right)) + 1 : -1;
}

template <typename T>
void BST<T>::inOrder(Node* node,
                     const std::function<void(const T&, int)>& visit) {
  if (!node) return;
  inOrder(node->left, visit);
  visit(node->key, node->count);
  inOrder(node->right, visit);
}

template <typename T>
void BST<T>::clear(Node* node) {
  if (!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

#endif  // INCLUDE_BST_H_
