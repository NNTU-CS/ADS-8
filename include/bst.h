// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#pragma once
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        } else if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, const T& key) const {
        if (!node || node->key == key) return node;
        return (key < node->key) ? search(node->left, key) : search(node->right, key);
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inorder(node->left, result);
        result.push_back({node->key, node->count});
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

    void insert(const T& key) { insert(root, key); }
    int depth() const { return depth(root); }
    bool search(const T& key) const { return search(root, key) != nullptr; }
    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> result;
        inorder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
