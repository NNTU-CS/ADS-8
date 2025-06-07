// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template <typename T> class BST {
private:
  struct Node {
    T data;
    int count;
    Node *left;
    Node *right;
    Node(const T &value)
        : data(value), count(1), left(nullptr), right(nullptr) {}
  };

  Node *root;

  void insertNode(Node *&node, const T &value) {
    if (!node) {
      node = new Node(value);
      return;
    }
    if (value < node->data) {
      insertNode(node->left, value);
    } else if (value > node->data) {
      insertNode(node->right, value);
    } else {
      node->count++;
    }
  }

  Node *searchNode(Node *node, const T &value) const {
    if (!node || node->data == value) {
      return node;
    }
    if (value < node->data) {
      return searchNode(node->left, value);
    }
    return searchNode(node->right, value);
  }

  int getDepth(Node *node) const {
    if (!node)
      return 0;
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  void clear(Node *node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  void collectFrequencies(Node *node,
                          std::vector<std::pair<T, int>> &freq) const {
    if (node) {
      collectFrequencies(node->left, freq);
      freq.push_back({node->data, node->count});
      collectFrequencies(node->right, freq);
    }
  }

public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T &value) { insertNode(root, value); }

  bool search(const T &value) const {
    return searchNode(root, value) != nullptr;
  }

  int depth() const { return getDepth(root); }

  std::vector<std::pair<T, int>> getFrequencies() const {
    std::vector<std::pair<T, int>> freq;
    collectFrequencies(root, freq);
    return freq;
  }
};

void makeTree(BST<std::string> &tree, const char *filename);
void printFreq(BST<std::string> &tree);

#endif // INCLUDE_BST_H_
