// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>

template <typename T>
struct BSTNode {
  explicit BSTNode(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  T key;
  int count;
  BSTNode* left;
  BSTNode* right;
};

template <typename T>
class BST {
 private:
  BSTNode<T>* root;

    void insert(BSTNode<T>*& node, const T& value) {
      if (!node) {
        node = new BSTNode<T>(value);
      } else if (value == node->key) {
        node->count++;
      } else if (value < node->key) {
        insert(node->left, value);
      } else {
        insert(node->right, value);
      }
    }

    BSTNode<T>* search(BSTNode<T>* node, const T& value) const {
      if (!node) {
        return nullptr;
      } else if (value == node->key) {
        return node;
      } else if (value < node->key) {
        return search(node->left, value);
      } else {
        return search(node->right, value);
      }
    }

    int depth(BSTNode<T>* node) const {
      if (!node) return 0;
      int l = depth(node->left);
      int r = depth(node->right);
      return 1 + (l > r ? l : r);
    }

    void inorder(BSTNode<T>* node, void(*visitor)(BSTNode<T>*, void*), void* arg) const {
      if (!node) return;
      inorder(node->left, visitor, arg);
      visitor(node, arg);
      inorder(node->right, visitor, arg);
    }

    void free(BSTNode<T>* node) {
      if (!node) return;
      free(node->left);
      free(node->right);
      delete node;
    }

 public:
  BST() : root(nullptr) {}
  ~BST() { free(root); }

  void insert(const T& value) { insert(root, value); }

  int depth() const { return depth(root); }

  int search(const T& value) const { 
    BSTNode<T>* node = search(root, value); 
    return node ? node->count : 0;
  }

  void inorder(void(*visitor)(BSTNode<T>*, void*), void* arg) const {
  inorder(root, visitor, arg);
  }
};

#endif  // INCLUDE_BST_H_
