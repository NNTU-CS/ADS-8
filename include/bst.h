// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template<typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    Node(const T& value) : key(value), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, const T& key) {
        if (!node) return new Node<T>(key);
        if (key == node->key) {
            node->count++;
        } else if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        return node;
    }

    int depth(Node<T>* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    bool search(Node<T>* node, const T& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    void clear(Node<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& key) { root = insert(root, key); }

    int depth() const { return depth(root); }

    bool search(const T& key) const { return search(root, key); }

    Node<T>* getRoot() const { return root; }
};

#endif  // INCLUDE_BST_H_
