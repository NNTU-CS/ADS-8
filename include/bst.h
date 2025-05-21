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
    T key;
    int count;
    Node* left;
    Node* right;
    Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
      return;
    }
    if (key == node->key) {
      node->count++;
    } else if (key < node->key) {
      insert(node->left, key);
    } else {
      insert(node->right, key);
    }
  }

  int Search(Node* node, const T& key) const {
    if (!node) return 0;
    if (key == node->key) return node->count;
    if (key < node->key) return Search(node->left, key);
    return Search(node->right, key);
  }

  int Depth(Node* node) const {
    if (!node) return 0;
    int dl = Depth(node->left);
    int dr = Depth(node->right);
    return 1 + (dl > dr ? dl : dr);
  }
  void inorder(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    inorder(node->left, vec);
    vec.push_back({node->key, node->count});
    inorder(node->right, vec);
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

  void insert(const T& key) { insert(root, key); }

  int search(const T& key) const { return Search(root, key); }

  int depth() const { return Depth(root); }

  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> vec;
    inorder(root, vec);
    return vec;
  }
};

#endif  // INCLUDE_BST_H_
