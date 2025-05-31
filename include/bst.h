// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T word;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& value) : word(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insertNode(Node* node, const T& value) {
        if (!node)
            return new Node(value);
        if (value < node->word)
            node->left = insertNode(node->left, value);
        else if (value > node->word)
            node->right = insertNode(node->right, value);
        else
            node->count++;
        return node;
    }

    Node* findNode(Node* node, const T& value) const {
        if (!node)
            return nullptr;
        if (value == node->word)
            return node;
        else if (value < node->word)
            return findNode(node->left, value);
        else
            return findNode(node->right, value);
    }

    int calculateDepth(Node* node) const {
        if (!node)
            return -1;
        int leftDepth = calculateDepth(node->left);
        int rightDepth = calculateDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    void inOrderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node) {
            inOrderTraversal(node->left, result);
            result.emplace_back(node->word, node->count);
            inOrderTraversal(node->right, result);
        }
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        deleteTree(root);
    }

    void add(const T& value) {
        root = insertNode(root, value);
    }

    bool search(const T& value) const {
        return findNode(root, value) != nullptr;
    }

    int depth() const {
        return calculateDepth(root);
    }

    void getAllWords(std::vector<std::pair<T, int>>& result) const {
        inOrderTraversal(root, result);
    }
};

#endif  // INCLUDE_BST_H_
