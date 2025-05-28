// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template <typename T>
class BST {
 public:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

 private:
  Node* root;

  Node* insert(Node* node, T value) {
    if (node == nullptr) {
      return new Node(value);
    }
    if (value == node->key) {
      node->count++;
      return node;
    }
    if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }
    return node;
  }

  void destroyTree(Node* node) {
    if (node) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  int depth(Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  Node* search(Node* node, T value) const {
    if (node == nullptr || node->key == value) {
      return node;
    }
    if (value < node->key) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

  void inOrder(Node* node, void (*visit)(Node*)) const {
    if (node) {
      inOrder(node->left, visit);
      visit(node);
      inOrder(node->right, visit);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { destroyTree(root); }

  void insert(T value) {
    root = insert(root, value);
  }

  int depth() const {
    return depth(root);
  }

  bool search(T value) const {
    return search(root, value) != nullptr;
  }

  int getCount(T value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }

  void inOrder(void (*visit)(Node*)) const {
    inOrder(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
