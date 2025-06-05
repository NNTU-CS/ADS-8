// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& k)
      : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insertRec(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key == node->key) {
      node->count++;
    } else if (key < node->key) {
      insertRec(node->left, key);
    } else {
      insertRec(node->right, key);
    }
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inorder(node->left, out);
    out.emplace_back(node->key, node->count);
    inorder(node->right, out);
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  int searchRec(Node* node, const T& key) const {
    if (!node) return 0;
    if (key == node->key) return node->count;
    if (key < node->key) return searchRec(node->left, key);
    return searchRec(node->right, key);
  }

  int depthRec(Node* node) const {
    if (!node) return 0;
    int dl = depthRec(node->left);
    int dr = depthRec(node->right);
    return (dl > dr ? dl : dr) + 1;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    destroy(root);
  }

  void insert(const T& key) {
    insertRec(root, key);
  }

  int search(const T& key) const {
    return searchRec(root, key);
  }

  int depth() const {
    return depthRec(root);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
