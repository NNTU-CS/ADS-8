// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
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
    int depthRec(Node* node) const {
        if (!node) return 0;
        return std::max(depthRec(node->left), depthRec(node->right)) + 1;
    }
    void inOrderRec(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inOrderRec(node->left, result);
        result.emplace_back(node->key, node->count);
        inOrderRec(node->right, result);
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
    int search(T value) const {
        Node* found = searchNode(value);
        return found ? found->count : 0;
    }
    int depth() const {
        return depthRec(root)-1;
    }
    std::vector<std::pair<T, int>> getItems() const {
        std::vector<std::pair<T, int>> result;
        inOrderRec(root, result);
        return result;
    }

 private:
    Node* searchNode(T value) const {
    Node* current = root;
    while (current) {
        if (value == current->key) return current;
        current = value < current->key ? current->left : current->right;
    }
        return nullptr;
    }
};

#endif  // INCLUDE_BST_H_
