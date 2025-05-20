// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
  private:
    struct Node {
      T value;
      int count;
      Node* left;
      Node* right;

      explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

  Node* root;

  void insert(Node*& node, const T& val) {
    if (!node)
      node = new Node(val);
    else if (val < node->value)
      insert(node->left, val);
    else if (val > node->value)
      insert(node->right, val);
    else
      node->count++;
  }

int depth(Node* node) const {
  if (!node) return -1;
  int l = depth(node->left);
  int r = depth(node->right);
  return std::max(l, r) + 1;
}

  int search(Node* node, const T& val) const {
    if (!node) return 0;
    if (val < node->value)
      return search(node->left, val);
    else if (val > node->value)
      return search(node->right, val);
    else
      return node->count;
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& val) { insert(root, val); }

    int search(const T& val) const { return search(root, val); }

    int depth() const { return depth(root); }
};

#endif  // INCLUDE_BST_H_
