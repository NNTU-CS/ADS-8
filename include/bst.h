// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>

template <typename T>
struct BSTNode {
    T key;
    int count;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value) {
        root = insert(root, value);
    }

    int search(const T& value) const {
        BSTNode<T>* cur = root;
        while (cur) {
            if (value < cur->key) {
                cur = cur->left;
            } else if (cur->key < value) {
                cur = cur->right;
            } else {
                return cur->count;
            }
        }
        return 0;
    }

    int depth() const {
        return depth(root);
    }

    template <typename Func>
    void inorder(Func func) const {
        inorder(root, func);
    }

 private:
    BSTNode<T>* root;

    BSTNode<T>* insert(BSTNode<T>* node, const T& value) {
        if (!node) {
            return new BSTNode<T>(value);
        }
        if (value < node->key) {
            node->left = insert(node->left, value);
        } else if (node->key < value) {
            node->right = insert(node->right, value);
        } else {
            ++node->count;
        }
        return node;
    }

    int depth(BSTNode<T>* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    template <typename Func>
    void inorder(BSTNode<T>* node, Func func) const {
        if (!node) return;
        inorder(node->left, func);
        func(node);
        inorder(node->right, func);
    }

    void clear(BSTNode<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

#endif  // INCLUDE_BST_H_