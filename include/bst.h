// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    int frequency;
    Node* left;
    Node* right;

    explicit Node(const T& d) : data(d), frequency(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void destroyTree(Node* node) {
    if (node) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  int depth(Node* node) const {
    if (!node) {
      return 0;
    }
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  Node* search(Node* node, const T& value) const {
    if (!node) {
      return nullptr;
    }

    if (value == node->data) {
      return node;
    } else if (value < node->data) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

  Node* insert(Node* node, const T& value) {
    if (!node) {
      return new Node(value);
    }

    if (value == node->data) {
      node->frequency++;
    } else if (value < node->data) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }

    return node;
  }


  void inorderTraversal(Node* node, std::vector<std::pair<T, int>>& data) {
    if (node) {
      inorderTraversal(node->left, data);
      data.push_back(std::make_pair(node->data, node->frequency));
      inorderTraversal(node->right, data);
    }
  }



 public:
  BST() : root(nullptr) {}

  ~BST() {
    destroyTree(root);
  }

  int depth() const {
    return depth(root);
  }

  bool search(const T& value) const {
    return search(root, value) != nullptr;
  }

  void insert(const T& value) {
    root = insert(root, value);
  }


  std::vector<std::pair<T, int>> getFrequencies() {
    std::vector<std::pair<T, int>> frequencies;
    inorderTraversal(root, frequencies);
    return frequencies;
  }
};

#endif  // INCLUDE_BST_H_
