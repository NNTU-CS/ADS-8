// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

template <typename T>
class BST {
private:
    struct Node {
        T info;
        int kol;
        Node* left;
        Node* right;
        
        Node(T k) : info(k), kol(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value == node->info) {
            node->kol++;
            return node;
        }
        
        if (value < node->info) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        
        return node;
    }

    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, T value) const {
        if (node == nullptr || node->info == value) {
            return node;
        }
        
        if (value < node->info) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node != nullptr) {
            inOrder(node->left, result);
            result.emplace_back(node->info, node->kol);
            inOrder(node->right, result);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clear(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    bool search(T value) const {
        return search(root, value) != nullptr;
    }

    std::vector<std::pair<T, int>> inOrder() const {
        std::vector<std::pair<T, int>> result;
        inOrder(root, result);
        return result;
    }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
