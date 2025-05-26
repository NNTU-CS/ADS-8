// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
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

    void collect(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        collect(node->left, result);
        result.emplace_back(node->value, node->count);
        collect(node->right, result);
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

    void insert(const T& value) { root = insert(root, value); }
    bool search(const T& value) const { /* реализация поиска */ }
    int depth() const { return depth(root); }
    
    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
