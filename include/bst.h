// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    Node* right;
    int count;
    Node* left;
    explicitNode(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  Node* addNode(Node* node, const T& value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->data) {
      node->left = addNode(node->left, value);
    } else if (value > node->data) {
      node->right = addNode(node->right, value);
    } else
      node->count++;
    return node;
  }
  void Travel(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node) {
      Travel(node->left, result);
      result.emplace_back(node->data, node->count);
      Travel(node->right, result);
    }
  }
  Node* search(Node* node, const T& value) const {
    if (!node) {
      return nullptr;
    }
    if (value == node->data) {
      return node;
    } else if (value < node->data) {
      return search(node->left, value);
    } else
      return search(node->right, value);
  }
  void clear(Node* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }
  int depth(Node* node) const {
    return !node ? -1 :
      1 + std::max(depth(node->left), depth(node->right));
  }

 public:
  int search(const T& value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }
  BST() : root(nullptr) {}
  int height() const {
    return depth(root);
  }
  void getAll(std::vector<std::pair<T, int>>& result) const {
    Travel(root, result);
  }
  ~BST() {
    clear(root);
  }
  void add(const T& value) {
    root = addNode(root, value);
  }
};

#endif  // INCLUDE_BST_H_
