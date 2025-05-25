// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#pragma once
#include <algorithm>
#include <vector>
#include <utility>
#pragma once

template<typename T>
class BST {
private:
    struct Node {
        T    key;
        int  count;
        Node* left;
        Node* right;
        explicit Node(const T& k)
            : key(k), count(1), left(nullptr), right(nullptr) {
        }
    };
    Node* root_{ nullptr };

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        }
        else if (key == node->key) {
            node->count++;
        }
        else if (key < node->key) {
            insert(node->left, key);
        }
        else {
            insert(node->right, key);
        }
    }

    Node* searchNode(Node* node, const T& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key)  return searchNode(node->left, key);
        return searchNode(node->right, key);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorderCollect(Node* node,
        std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        inorderCollect(node->left, out);
        out.emplace_back(node->key, node->count);
        inorderCollect(node->right, out);
    }

public:
    BST() = default;
    ~BST() { clear(root_); }

    void insert(const T& key) {
        insert(root_, key);
    }

    int search(const T& key) const {
        Node* n = searchNode(root_, key);
        return n ? n->count : 0;
    }

    int depth() const {
        int nodes = depth(root_);
        return nodes > 0 ? nodes - 1 : 0;
    }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> v;
        inorderCollect(root_, v);
        return v;
    }
};
#endif  // INCLUDE_BST_H_
