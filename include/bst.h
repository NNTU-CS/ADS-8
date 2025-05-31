// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

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
    if (node != nullptr) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }


  int depth(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + std::max(left_depth, right_depth);
  }

  // Рекурсивный поиск узла
  Node* search(Node* node, const T& value) const {
    if (node == nullptr || value == node->data) {
      return node;
    }

    return (value < node->data) ? search(node->left, value) : search(node->right, value);
  }


  Node* insert(Node* node, const T& value) {
    if (node == nullptr) {
      return new Node(value);
    }

    if (value == node->data) {
      ++node->frequency;
    } else if (value < node->data) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }

    return node;
  }

  void inorderTraversal(Node* node, std::vector<std::pair<T, int>>& data) {
    if (node != nullptr) {
      inorderTraversal(node->left, data);
      data.emplace_back(node->data, node->frequency);
      inorderTraversal(node->right, data);
    }
  }

  int size(Node* node) const {
    return (node == nullptr) ? 0 : 1 + size(node->left) + size(node->right);
  }

 public:
  BST() : root(nullptr) {}

  ~BST() { destroyTree(root); }

  int depth() const { return depth(root); }

  int search(const T& value) const {
    Node* node = search(root, value);
    return (node != nullptr) ? node->frequency : 0;
  }

  void insert(const T& value) { root = insert(root, value); }

  std::vector<std::pair<T, int>> getFrequencies() {
    std::vector<std::pair<T, int>> frequencies;
    inorderTraversal(root, frequencies);
    return frequencies;
  }

  int size() const { return size(root); }
};

#endif  // INCLUDE_BST_H_
