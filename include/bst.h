// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

template <typename T>
class BST {
 public:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  using NodePtr = Node*;
  using Visitor = std::function<void(NodePtr)>;

 private:
  Node* root;

  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);

    if (value == node->key) {
      node->count++;
      return node;  // Возвращаем существующий узел без изменений
    } else if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }
    return node;
  }

  Node* search(Node* node, T value) const {
    if (!node || node->key == value) {
      return node;
    }
    return value < node->key ? search(node->left, value)
                             : search(node->right, value);
  }

  int depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  template <typename F>
  void inOrder(Node* node, F visit) const {
    if (!node) return;
    inOrder(node->left, visit);
    visit(node);
    inOrder(node->right, visit);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) { root = insert(root, value); }

  int search(T value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }

  int depth() const { return depth(root); }

  template <typename F>
  void inOrder(F visit) const {
    inOrder(root, visit);
  }

  static std::pair<T, int> getNodeData(NodePtr node) {
    return {node->key, node->count};
  }
};

#endif  // INCLUDE_BST_H_
