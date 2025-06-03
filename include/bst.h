// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    int frequency;
    Node* left;
    Node* right;

    explicit Node(const T& value) : data(value), frequency(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insertHelper(Node* node, const T& value) {
    if (node == nullptr) {
      return new Node(value);
    }
    if (value < node->data) {
      node->left = insertHelper(node->left, value);
    } else if (value > node->data) {
      node->right = insertHelper(node->right, value);
    } else {
      node->frequency++;
    }
    return node;
  }

  void destroyHelper(Node* node) {
    if (node != nullptr) {
      destroyHelper(node->left);
      destroyHelper(node->right);
      delete node;
    }
  }

  int depthHelper(Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    int leftDepth = depthHelper(node->left);
    int rightDepth = depthHelper(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  int countHelper(Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    return 1 + countHelper(node->left) + countHelper(node->right);
  }

  int totalWordsHelper(Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    return node->frequency + totalWordsHelper(node->left) + totalWordsHelper(node->right);
  }
  int searchHelper(Node* node, const T& value) const {
    if (node == nullptr) {
      return 0;
    }
    if (value == node->data) {
      return node->frequency;
    } else if (value < node->data) {
      return searchHelper(node->left, value);
    } else {
      return searchHelper(node->right, value);
    }
  }

  void inorderHelper(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node != nullptr) {
      inorderHelper(node->left, result);
      result.push_back({node->data, node->frequency});
      inorderHelper(node->right, result);
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    destroyHelper(root);
  }

  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;

  void insert(const T& value) {
    root = insertHelper(root, value);
  }

  int search(const T& value) const {
    return searchHelper(root, value);
  }

  int depth() const {
    return depthHelper(root);
  }

  int count() const {
    return countHelper(root);
  }

  int totalWords() const {
    return totalWordsHelper(root);
  }

  bool empty() const {
    return root == nullptr;
  }
  std::vector<std::pair<T, int>> getInOrder() const {
    std::vector<std::pair<T, int>> result;
    inorderHelper(root, result);
    return result;
  }

  std::vector<std::pair<T, int>> getByFrequency() const {
    std::vector<std::pair<T, int>> result = getInOrder();
    std::sort(result.begin(), result.end(),
              [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                if (a.second != b.second) {
                  return a.second > b.second;
                }
                return a.first < b.first;
              });
        return result;
  }
};

#endif  // INCLUDE_BST_H_
