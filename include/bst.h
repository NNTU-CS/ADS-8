// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
class BST {
public:
    BST() : root(nullptr), tree_size(0) {}

    void insert(const T& value) {
        root = insertNode(std::move(root), value);
        ++tree_size;
    }

    bool search(const T& value) const {
        return searchNode(root, value);
    }

    int depth() const {
        return nodeDepth(root);
    }

    int size() const {
        return tree_size;
    }

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;
    int tree_size;

    std::unique_ptr<Node> insertNode(std::unique_ptr<Node> node, const T& value) {
        if (!node) {
            return std::make_unique<Node>(value);
        }
        if (value < node->data) {
            node->left = insertNode(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insertNode(std::move(node->right), value);
        }
        return node;
    }

    bool searchNode(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    int nodeDepth(const std::unique_ptr<Node>& node) const {
        if (!node) return 0;
        return 1 + std::max(nodeDepth(node->left), nodeDepth(node->right));
    }
};

#endif  // INCLUDE_BST_H_
