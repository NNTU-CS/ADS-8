// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template <typename T>
class BST {
private:
    struct Node {
        T key;
        int count; 
        Node* left;
        Node* right;
        
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

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

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, T value) const {
        if (!node || node->key == value) return node;
        
        if (value < node->key) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void inOrder(Node* node, void (*visit)(Node*)) const {
        if (node) {
            inOrder(node->left, visit);
            visit(node);
            inOrder(node->right, visit);
        }
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

    bool search(T value) const {
        return search(root, value) != nullptr;
    }

    int getCount(T value) const {
        Node* found = search(root, value);
        return found ? found->count : 0;
    }

    void inOrder(void (*visit)(Node*)) const {
        inOrder(root, visit);
    }
};

#endif  // INCLUDE_BST_H_
