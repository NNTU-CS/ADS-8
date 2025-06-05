// Copyright 2021 NNTU-CS
// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template <typename T>
class BST {
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(const T& k): key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  int insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
      return 0;
    }
    if (key < node->key) {
      return 1 + insert(node->left, key);
    } else if (node->key < key) {
      return 1 + insert(node->right, key);
    } else {
      node->count++;
      return 0;
    }
  }

  Node* find(Node* node, const T& key) const {
    if (!node) return nullptr;
    if (key < node->key) return find(node->left, key);
    if (node->key < key) return find(node->right, key);
    return node;
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int dl = depth(node->left);
    int dr = depth(node->right);
    return 1 + (dl > dr ? dl : dr);
  }

  void traverse(Node* node, std::vector<std::pair<T,int>>& vec) const {
    if (!node) return;
    vec.emplace_back(node->key, node->count);
    traverse(node->left, vec);
    traverse(node->right, vec);
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

 public:
  BST(): root(nullptr) {}
  ~BST() { destroy(root); }

  void insert(const T& key) { insert(root, key); }

  int search(const T& key) const {
    Node* nd = find(root, key);
    return nd ? nd->count : 0;
  }

  int depth() const { return depth(root); }

  void getAll(std::vector<std::pair<T,int>>& vec) const {
    traverse(root, vec);
  }
};

#endif  // INCLUDE_BST_H_
