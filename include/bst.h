// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T> class BST {
 private:
  struct Node {
    T word;
    Node* left;
    Node* right;
    int count;
  };
  Node* root;

  using Item = std::pair<T, int>;

  Node* addNode(Node* root, const T& word) {
    if (root == nullptr) {
      root = new Node;
      root->word = word;
      root->count = 1;
      root->left = root->right = nullptr;
    } else if (word > root->word) {
      root->right = addNode(root->right, word);
    } else if (word < root->word) {
      root->left = addNode(root->left, word);
    } else {
      root->count++;
    }
    return root;
  }

  int searchNode(Node* root, const T& word) const {
    if (root == nullptr) {
      return 0;
    } else if (word > root->word) {
      return searchNode(root->right, word);
    } else if (word < root->word) {
      return searchNode(root->left, word);
    } else {
      return root->count;
    }
  }

  void printTree(Node* root) const {
    if (root == nullptr) {
      return;
    }
    printTree(root->left);
    for (int i = 0; i < root->count; ++i) {
      std::cout << root->word << " ";
    }
    printTree(root->right);
  }

  int depthTree(const Node* root) const {
    if (root == nullptr) {
      return -1;
    }
    if (root->left == nullptr && root->right == nullptr) {
      return 0;   // Глубина листа 0
    }
    return std::max(depthTree(root->left), depthTree(root->right)) + 1;
  }

  void delTree(Node* root) {
    if (root == nullptr) {
      return;
    }
    delTree(root->left);
    delTree(root->right);
    delete root;
  }

  Node* delNode(Node* root, const T& word) {
    Node* p, * w;
    if (root == nullptr) {
      return nullptr;
    } else if (word > root->word) {
      root->right = delNode(root->right, word);
    } else if (word < root->word) {
      root->left = delNode(root->left, word);
    } else {
      p = root;
      if (root->right == nullptr) {
        root = root->left;
      } else if (root->left == nullptr) {
        root = root->right;
      } else {
        w = root->left;
        if (w->right != nullptr) {
          while (w->right->right != nullptr) {
            w = w->right;
          }
          root->word = w->right->word;
          root->count = w->right->count;
          p = w->right;
          w->right = w->right->left;
          } else {
            root->word = w->word;
            root->count = w->count;
            p = w;
            root->left = root->left->left;
          }
        }
        delete p;
    }
    return root;
  }

  void fillVector(Node* node, std::vector<Item>& result) const {
    if (!node) return;
    fillVector(node->left, result);
    result.emplace_back(node->word, node->count);
    fillVector(node->right, result);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(); }

  void add(const T& word) {
    root = addNode(root, word);
  }

  int search(const T& word) const {
    return searchNode(root, word);
  }

  int depth() const {
    return depthTree(root);
  }

  void print() const {
    printTree(root);
  }

  void clear() {
    delTree(root);
    root = nullptr;
  }

  Node* del(const T& word) {
    return delNode(root, word);
  }

  std::vector<Item> getAll() const {
    std::vector<Item> result;
    fillVector(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
