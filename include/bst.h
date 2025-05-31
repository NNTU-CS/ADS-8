// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <utility>
#include <vector>

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

  void insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key < node->key) {
      insert(node->left, key);
    } else if (key > node->key) {
      insert(node->right, key);
    } else {
      node->count++;
    }
  }

  void toVector(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    toVector(node->left, vec);
    vec.push_back({node->key, node->count});
    toVector(node->right, vec);
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  int countNodes(Node* node) const {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
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

  void insert(const T& key) {
    insert(root, key);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> vec;
    toVector(root, vec);
    return vec;
  }

  int depth() const {
    return depth(root);
  }

  int count() const {
    return countNodes(root);
  }
};

#endif  // INCLUDE_BST_H_
