// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;

    Node(const T& value)
        : data(value), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value == node->data) {
      node->count++;
    } else if (value < node->data) {
      insert(node->left, value);
    } else {
      insert(node->right, value);
    }
  }

  void inOrder(Node* node, std::vector<std::pair<T, int>>& freqList) {
    if (!node) return;
    inOrder(node->left, freqList);
    freqList.emplace_back(node->data, node->count);
    inOrder(node->right, freqList);
  }

  int depth(Node* node) {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
  }

  Node* search(Node* node, const T& value) {
    if (!node || node->data == value) {
      return node;
    }
    if (value < node->data) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

 public:
  BST() : root(nullptr) {}

  void insert(const T& value) { insert(root, value); }

  void inOrder(std::vector<std::pair<T, int>>& freqList) {
    inOrder(root, freqList);
  }

  int depth() { return depth(root); }

  int search(const T& value) {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }
};

#endif  // INCLUDE_BST_H_
