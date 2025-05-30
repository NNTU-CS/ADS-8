// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template <typename T>
class BST {
 private:
  struct Node {
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    T key;
    int count;
    Node* left;
    Node* right;
  };

  Node* root;

  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);
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

  Node* search(Node* node, T value) const {
    if (!node || node->key == value) {
      return node;
    }
    if (value < node->key) {
      return search(node->left, value);
    }
    return search(node->right, value);
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  void printFreq(Node* node, std::ostream& out) const {
    if (!node) return;
    printFreq(node->right, out);
    out << node->key << " " << node->count << std::endl;
    printFreq(node->left, out);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) { root = insert(root, value); }
  int search(T value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }
  int depth() const { return depth(root); }
  void printFreq(std::ostream& out = std::cout) const { printFreq(root, out); }
};

#endif  // INCLUDE_BST_H_
