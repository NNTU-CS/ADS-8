// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>

template <typename T>
class BST {
private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
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
    if (!node) return 0;
    int left = depth(node->left);
    int right = depth(node->right);
    return std::max(left, right) + 1;
  }

  Node* search(Node* node, const T& val) const {
    if (!node || node->value == val) return node;
    if (val < node->value) return search(node->left, val);
    else return search(node->right, val);
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back({node->value, node->count});
    inorder(node->right, result);
  }

public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }

  void insert(const T& val) { insert(root, val); }

  bool search(const T& val) const { return search(root, val) != nullptr; }

  int depth() const { return depth(root); }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
