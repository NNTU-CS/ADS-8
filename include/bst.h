// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>

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
  using NodeVisitor = void (*)(const Node*);
private:
  Node* root;
  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);
    if (value == node->key) {
      node->count++;
    } else if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }
    return node;
  }
  void inOrder(Node* node, NodeVisitor visit) const {
   if(!node) return;
   inOrder(node->left, visit);
   visit(node);
   inOrder(nod->right, visit);
  }
  int depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }
  Node* search(Node* node, T value) const {
    if (!node) return nullptr;
    if (value == node->key) return node;
    if (value < node->key) return search(node->left, value);
    return search(node->right, value);
  }
  void inOrder(Node* node, void (*visit)(const Node*)) const {
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
  void inOrder (NodeVisitor visist) const {
   inOrder(root, visit);
  }
  BST() : root(nullptr) {}
  ~BST() { clear(root); }
  void insert(T value) {
    root = insert(root, value);
  }
  int depth() const {
    return depth(root);
  }
  int search(T value) const {
    Node* node = search(root, value);
    return node ? node->count : 0;
  }
  void inOrder(void (*visit)(const Node*)) const {
    inOrder(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
