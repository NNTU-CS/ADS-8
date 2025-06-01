// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <algorithm>
#include <iostream>

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

    Node* insertRec(Node* node, T value) {
        if (!node) return new Node(value);
        
        if (value < node->key) {
            node->left = insertRec(node->left, value);
        } else if (value > node->key) {
            node->right = insertRec(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    Node* searchRec(Node* node, T value) const {
        if (!node || node->key == value) 
            return node;
            
        if (value < node->key) 
            return searchRec(node->left, value);
        else 
            return searchRec(node->right, value);
    }

    int depthRec(Node* node) const {
        if (!node) return 0;
        return std::max(depthRec(node->left), depthRec(node->right)) + 1;
    }

    void inOrderRec(Node* node, std::vector<Node*>& nodes) const {
        if (!node) return;
        inOrderRec(node->left, nodes);
        nodes.push_back(node);
        inOrderRec(node->right, nodes);
    }

    void clearRec(Node* node) {
        if (!node) return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clearRec(root); }

    void insert(T value) {
        root = insertRec(root, value);
    }

    Node* search(T value) const {
        return searchRec(root, value);
    }

    int depth() const {
        return depthRec(root);
    }

    void inOrderTraversal(std::vector<Node*>& nodes) const {
        inOrderRec(root, nodes);
    }
};

#endif // BST_H
