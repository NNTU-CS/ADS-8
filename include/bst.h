// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

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

  void clear(Node* node) {
    node ? (clear(node->left), clear(node->right), delete node) : void();
  }

  void insert(Node*& node, const T& key) {
    !node ? node = new Node(key) : 
    (key == node->key ? node->count++ : 
     (key < node->key ? insert(node->left, key) : insert(node->right, key)));
  }

  int Search(Node* node, const T& key) const {
    return !node ? 0 : 
           key == node->key ? node->count : 
           Search(key < node->key ? node->left : node->right, key);
  }

  int Depth(Node* node) const {
    return !node ? -1 : 
           1 + (Depth(node->left) > Depth(node->right) ? Depth(node->left) : Depth(node->right));
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (node) {
      inorder(node->left, vec);
      vec.push_back({node->key, node->count});
      inorder(node->right, vec);
    }
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
