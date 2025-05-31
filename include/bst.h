// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#pragma once

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
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

  void Insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key < node->key) {
      Insert(node->left, key);
    } else if (key > node->key) {
      Insert(node->right, key);
    } else {
      node->count++;
    }
  }

  int Depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(Depth(node->left), Depth(node->right));
  }

  Node* Search(Node* node, const T& key) const {
    if (!node || node->key == key) return node;
    return (key < node->key) ? Search(node->left, key) : Search(node->right, key);
  }

  void Inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    Inorder(node->left, result);
    result.push_back({node->key, node->count});
    Inorder(node->right, result);
  }

  void Clear(Node* node) {
    if (!node) return;
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { Clear(root); }

  void Insert(const T& key) { Insert(root, key); }
  int Depth() const { return Depth(root); }
  int Search(const T& key) const {
    Node* result = Search(root, key);
    return result ? result->count : 0;
  }
  std::vector<std::pair<T, int>> ToVector() const {
    std::vector<std::pair<T, int>> result;
    Inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
