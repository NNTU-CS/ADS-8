// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <fstream>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T word;
    int freq;
    Node* left;
    Node* right;

    explicit Node(const T& w) : word(w), freq(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insertNode(Node*& node, const T& word) {
    if (!node) {
      node = new Node(word);
    } else if (word == node->word) {
      node->freq++;
    } else if (word < node->word) {
      insertNode(node->left, word);
    } else {
      insertNode(node->right, word);
    }
  }

  int measureDepth(Node* node) const {
    if (!node) return -1;
    int left = measureDepth(node->left);
    int right = measureDepth(node->right);
    return 1 + (left > right ? left : right);
  }

  Node* find(Node* node, const T& word) const {
    if (!node) return nullptr;
    if (word == node->word) return node;
    return (word < node->word) ? find(node->left, word)
                               : find(node->right, word);
  }

  void collectWords(Node* node, std::vector<std::pair<T, int>>& list) const {
    if (!node) return;
    collectWords(node->left, list);
    list.push_back({node->word, node->freq});
    collectWords(node->right, list);
  }

  void free(Node* node) {
    if (node) {
      free(node->left);
      free(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() { free(root); }

  void insert(const T& word) { insertNode(root, word); }

  int depth() const { return measureDepth(root); }

  int search(const T& word) const {
    Node* node = find(root, word);
    return node ? node->freq : 0;
  }

  void getFrequencyList(std::vector<std::pair<T, int>>& list) const {
    collectWords(root, list);
  }
};
#endif  // INCLUDE_BST_H_
