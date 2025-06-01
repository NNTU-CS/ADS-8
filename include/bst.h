// Copyright 2021 NNTU-CS
#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    Node(T k) : key(std::move(k)), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  Node* insert(Node* node, const T& value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->key) {
      node->left = insert(node->left, value);
    } else if (value > node->key) {
      node->right = insert(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }
  int depth(Node* node) const {
    if (!node) {
      return 0;
    }
    return 1 + std::max(depth(node->left), depth(node->right));
  }
  Node* search(Node* node, const T& value) const {
    if (!node || node->key == value) {
      return node;
    }
    if (value < node->key) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }
  void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node) {
      inOrder(node->left, result);
      result.emplace_back(node->key, node->count);
      inOrder(node->right, result);
    }
  }
  void clear(Node* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    clear(root);
  }
  void insert(const T& value) {
    root = insert(root, value);
  }
  int depth() const {
    return depth(root);
  }
  bool search(const T& value) const {
    return search(root, value) != nullptr;
  }
  int getCount(const T& value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }
  std::vector<std::pair<T, int>> inOrder() const {
    std::vector<std::pair<T, int>> result;
    inOrder(root, result);
    return result;
  }
};
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif // BST_H
