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
        T key;
        int count;
        Node* left;
        Node* right;
        
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);
        
        if (value == node->key) {
            node->count++;
        } else if (value < node->key) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    Node* searchNode(Node* node, T value) const {
        if (!node) return nullptr;
        
        if (value == node->key) {
            return node;
        } else if (value < node->key) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inOrder(Node* node, std::function<void(Node*)> visit) const {
        if (!node) return;
        inOrder(node->left, visit);
        visit(node);
        inOrder(node->right, visit);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(T value) {
        root = insert(root, value);
    }

    bool search(T value) const {
        return searchNode(root, value) != nullptr;
    }

    int getCount(T value) const {
        Node* node = searchNode(root, value);
        return node ? node->count : 0;
    }

    int depth() const {
        return depth(root);
    }

    void inOrder(std::function<void(Node*)> visit) const {
        inOrder(root, visit);
    }
};

#endif  // INCLUDE_BST_H_
