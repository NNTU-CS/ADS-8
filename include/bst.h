// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm> // для std::max

template <typename T> class BST {
  struct Node {
    Node *left;
    Node *right;
    int count;
    T word;
    explicit Node(const T &word) : word(word), left(nullptr), right(nullptr), count(1) {}
  };
  Node *root;
  void add(Node *&node, const T &word) {
    if (!node) {
      node = new Node(word);
      return;
    }
    if (word > node->word) {
      add(node->right, word);
    } else if (word < node->word) {
      add(node->left, word);
    } else {
      node->count++;
    }
  }
  int treeHeight(Node *node) const {
    if (!node)
      return 0;
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
  }
  int search(Node *node, const T &word) const {
    if (!node)
      return 0;
    if (word > node->word)
      return search(node->right, word);
    else if (word < node->word)
      return search(node->left, word);
    else
      return node->count;
  }
  void free(Node *node) {
    if (!node)
      return;
    free(node->left);
    free(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { free(root); }
  void add(const T &word) { add(root, word); }
  int depth() const { return treeHeight(root); }
  int search(const T &word) const { return search(root, word); }
};

#endif // INCLUDE_BST_H_
