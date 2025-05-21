// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>

template<typename T>
class Node {
 public:
  T word;
  int quantity;
  Node* left_pointer;
  Node* right_pointer;
  explicit Node(T value) : word(value), quantity(1), left_pointer(nullptr), right_pointer(nullptr) {}
};

template<typename T>
class BST {
 private:
  Node<T>* first;
  void insert_func(Node<T>*& node, T word) {
    if (node == nullptr) {
      node = new Node<T>(word);
    } else if (word == node->word) {
      node->quantity++;
    } else if (word < node->word) {
      insert_func(node->left_pointer, word);
    } else {
      insert_func(node->right_pointer, word);
    }
  }
  bool search_func(Node<T>* node, T word) {
    if (node == nullptr) {
      return false;
    }
    if (word == node->word) {
      return true;
    } else if (word < node->word) {
      return search(node->left_pointer, word);
    } else {
      return search(node->right_pointer, word);
    }
  }
  int depth_func(Node<T>* node) {
    if (node == nullptr) {
      return 0;
    }
    int leftDepth = depth_func(node->left_pointer);
    int rightDepth = depth_func(node->right_pointer);
    return std::max(leftDepth, rightDepth) + 1;
  }
  void inOrder_func(Node<T>* node) {
    if (node != nullptr) {
      inOrder_func(node->left_pointer);
      std::cout << node->word << " - " << node->quantity << std::endl;
      inOrder_func(node->right_pointer);
    }
  }
 public:
  BST() : first(nullptr) {}
  void insert(T word) {
    insert_func(first, word);
  }
  bool search(T word) {
    return search_func(first, word);
  }
  int depth() {
    return depth_func(first);
  }
  void printInOrder() {
    inOrder_func(first);
  }
};

#endif  // INCLUDE_BST_H_
