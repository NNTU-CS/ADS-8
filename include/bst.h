// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

template <typename T>
class BST {
 public:
  struct Node {
        T slovo;
        int kol;
        Node* left;
        Node* right;
        explicit Node(T s) : slovo(s), kol(1), left(nullptr), right(nullptr) {}
  };

 private:
  Node* root;
  Node* addNode(Node* root, const T& value) {
        if (root == nullptr) {
            return new Node(value);
        }
        if (value < root->slovo) {
            root->left = addNode(root->left, value);
        } else if (value > root->slovo) {
            root->right = addNode(root->right, value);
        } else {
            ++root->kol;
        }
        return root;
    }

  int heightT(Node* root) const {
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

  void deleteT(Node* root) {
    if (root == nullptr)
      return;
    deleteT(root->left);
    deleteT(root->right);
    delete root;
  }

 public:
  struct Node;
  BST() : root(nullptr) {}
  ~BST() { deleteT(root); }

  void insert(T value) {
    root = addNode(root, value);
  }

  int height() const {
      return heightT(root);
  }

  int search(T value) const {
      return searchNode(root, value);
  }

  template <typename Visitor>
  void inorder(Visitor visit) const {
      obhod(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
