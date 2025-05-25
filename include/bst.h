// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        Node(const T& data) : data(data), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& data) {
        if (node == nullptr) {
            node = new Node(data);
        } else if (data < node->data) {
            insert(node->left, data);
        } else if (data > node->data) {
            insert(node->right, data);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, const T& value) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (value == node->data) {
            return node;
        } else if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void inorderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back(std::make_pair(node->data, node->count));
            inorderTraversal(node->right, result);
        }
    }

    void freeTree(Node* node) {
        if (node) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        freeTree(root);
    }

    void insert(const T& data) {
        insert(root, data);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    int getCount(const T& value) const {
        Node* node = search(root, value);
        if (node) {
            return node->count;
        } else {
            return 0;
        }
    }

    std::vector<std::pair<T, int>> getWordFrequencies() const {
        std::vector<std::pair<T, int>> result;
        inorderTraversal(root, result);
        return result;
    }
};
#endif  // INCLUDE_BST_H_
