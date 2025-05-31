// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insert(Node* node, const T& value) {
    if (!node) {
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

  int depth(Node* node) const {
    if (!node) {
      return -1;
    }
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  void collectFreq(Node* node, std::vector<std::pair<T, int>>& freqList) const {
    if (!node) {
      return;
    }
    collectFreq(node->left, freqList);
    freqList.emplace_back(node->key, node->count);
    collectFreq(node->right, freqList);
  }

  void clear(Node* node) {
    if (!node) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T& value) {
    root = insert(root, value);
  }

  int search(const T& value) const {
    Node* node = root;
    while (node) {
      if (value == node->key) {
        return node->count;
      }
      if (value < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return 0;
  }

  int depth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> freqList;
    collectFreq(root, freqList);
    return freqList;
  }
};

#endif  // INCLUDE_BST_H_
