// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        
        Node(T k) : key(std::move(k)), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& value) {
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

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        
        if (value == node->key) {
            return node;
        } else if (value < node->key) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inorder(node->left, result);
        result.emplace_back(node->key, node->count);
        inorder(node->right, result);
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

    void insert(const T& value) {
        root = insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::pair<T, int> search(const T& value) const {
        Node* found = search(root, value);
        if (found) {
            return {found->key, found->count};
        }
        return {T(), 0};
    }

    std::vector<std::pair<T, int>> inorder() const {
        std::vector<std::pair<T, int>> result;
        inorder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
