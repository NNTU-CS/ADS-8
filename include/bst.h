// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename T>
struct Node {
  T key;
  int cnt;
  Node* l;
  Node* r;

  explicit Node(const T& n) : key(n), cnt(1), l(nullptr), r(nullptr) {}
};

template <typename T>
class BST {
 public:
  BST() : rt(nullptr) {}

  ~BST() { destroyTree(rt); }

  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;

  void insert(const T& n) { rt = insertRecursive(rt, n); }

  int search(const T& n) const {
    Node<T>* f_n = searchNodeRecursive(rt, n);
    if (f_n != nullptr) {
      return f_n->cnt;
    }
    return 0;
  }

  int depth() const {
    if (rt == nullptr) {
      return 0;
    }
    return depthRecursive(rt) - 1;
  }

  void getWordFrequencies(std::vector<std::pair<T, int>>& vec) const {
    getWordFrequenciesRecursive(rt, vec);
  }

 private:
  Node<T>* rt;

  Node<T>* insertRecursive(Node<T>* node, const T& n) {
    if (node == nullptr) {
      return new Node<T>(n);
    }

    if (n < node->key) {
      node->l = insertRecursive(node->l, n);
    } else if (n > node->key) {
      node->r = insertRecursive(node->r, n);
    } else {
      node->cnt++;
    }
    return node;
  }

  Node<T>* searchNodeRecursive(Node<T>* node, const T& n) const {
    if (node == nullptr || node->key == n) {
      return node;
    }

    if (n < node->key) {
      return searchNodeRecursive(node->l, n);
    } else {
      return searchNodeRecursive(node->r, n);
    }
  }

  int depthRecursive(Node<T>* node) const {
    if (node == nullptr) {
      return 0;
    }
    int l_depth = depthRecursive(node->l);
    int r_depth = depthRecursive(node->r);
    return 1 + std::max(l_depth, r_depth);
  }

  void destroyTree(Node<T>* node) {
    if (node != nullptr) {
      destroyTree(node->l);
      destroyTree(node->r);
      delete node;
    }
  }

  void getWordFrequenciesRecursive(Node<T>* node,
                                   std::vector<std::pair<T, int>>& vec) const {
    if (node != nullptr) {
      getWordFrequenciesRecursive(node->l, vec);
      vec.push_back({node->key, node->cnt});
      getWordFrequenciesRecursive(node->r, vec);
    }
  }
};

#endif  // INCLUDE_BST_H_
