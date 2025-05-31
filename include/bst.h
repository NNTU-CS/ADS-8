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
  Node* addNode(Node* spot, T value) {
    if (spot == nullptr) {
      Node* newNode = new Node(value);
      return newNode;
    } else if (value < spot->slovo) {
      spot->left = addNode(spot->left, value);
    } else if (value > spot->slovo) {
      spot->right = addNode(spot->right, value);
    } else {
      spot->kol++;
    }
    return spot;
  }

  int heightT(Node* root) {
    if (root == nullptr) {
      return 0;
    }
    int leftH = heightT(root->left);
    int rightH = heightT(root->right);
    return std::max(leftH, rightH) + 1;
  }

  int searchNode(Node* spot, T value) const {
    if (spot == nullptr) {
        return 0;
    } else if (value < spot->slovo) {
        return searchNode(spot->left, value);
    } else if (value > spot->slovo) {
        return searchNode(spot->right, value);
    }
    return spot->kol;
  }

  template <typename Visitor>
  void obhod(Node* node, Visitor visit) const {
    if (node != nullptr) {
      obhod(node->left, visit);
      visit(node);
      obhod(node->right, visit);
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
  ~BST() { delet(root); }

  void addNode(T value) {
    root = addNode(root, value);
  }

  int heightT() const {
      return heightT(root);
  }

  int searchNode(T value) const {
      return searchNode(root, value);
  }


  void obhod(void (*visit)(Node*)) const {
      obhod(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
