// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

template <typename T>
class BST {
 private:
  struct Node {
        T slovo;
        int kol;
        Node* left;
        Node* right;
        explicit Node(T s) : slovo(s), kol(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  Node* insert(Node* spot, T value) {
    if (spot == nullptr) {
      Node* newNode = new Node(value);
      return newNode;
    } else if (value < spot->slovo) {
      spot->left = insert(spot->left, value);
    } else if (value > spot->slovo) {
      spot->right = insert(spot->right, value);
    } else {
      spot->kol++;
    }
    return spot;
  }

  int depth(Node* root) {
    if (root == nullptr) {
      return 0;
    }
    int leftH = heightT(root->left);
    int rightH = heightT(root->right);
    return std::max(leftH, rightH) + 1;
  }

  int search(Node* spot, T value) const {
    if (spot == nullptr) {
        return 0;
    } else if (value < spot->slovo) {
        return search(spot->left, value);
    } else if (value > spot->slovo) {
        return search(spot->right, value);
    }
    return spot->kol;
  }

  template <typename Visitor>
  void inOrder(Node* node, Visitor visit) const {
    if (node != nullptr) {
      inOrder(node->left, visit);
      visit(node);
      inOrder(node->right, visit);
    }
  }

  void delet(Node* root) {
    if (root == nullptr)
      return;
    delet(root->left);
    delet(root->right);
    delete root;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T value) {
    root = insert(root, value);
  }

    int depth() const {
        return depth(root);
    }

    Node* search(T value) const {
        return search(root, value);
    }

    void inOrder(void (*visit)(Node*)) const {
        inOrder(root, visit);
    }
};

#endif  // INCLUDE_BST_H_
