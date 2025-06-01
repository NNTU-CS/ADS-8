// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <fstream>
#include <iostream>
#include <string>

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

  Node* insert(Node* node, const T& key) {
    if (!node) return new Node(key);
    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      node->count++;
    return node;
  }

  Node* search(Node* node, const T& key) const {
    if (!node || node->key == key) return node;
    if (key < node->key)
      return search(node->left, key);
    else
      return search(node->right, key);
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  void inorder(Node* node, std::ofstream& out) const {
    if (node) {
      inorder(node->right, out);  // обратный порядок для убывания
      out << node->key << " " << node->count << "\n";
      std::cout << node->key << " " << node->count << "\n";
      inorder(node->left, out);
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

  ~BST() { clear(root); }

  void insert(const T& key) { root = insert(root, key); }

  bool search(const T& key) const { return search(root, key) != nullptr; }

  int depth() const { return depth(root); }

  void printToFileAndConsole() const {
    std::ofstream out("result/freq.txt");
    inorder(root, out);
    out.close();
  }
};

#endif  // INCLUDE_BST_H_
