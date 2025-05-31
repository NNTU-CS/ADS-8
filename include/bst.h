// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    T key;
    int count;
    Node* left;
    Node* right;
  };

    Node* root;

    Node* insertNode(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value == node->key) {
            node->count++;
        } else if (value < node->key) {
            node->left = insertNode(node->left, value);
        } else {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    int calculateDepth(Node* node) const {
        if (!node) return -1;
        return 1 + std::max(calculateDepth(node->left),
            calculateDepth(node->right));
    }

    Node* findNode(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->key) return node;
        return findNode(value < node->key ? node->left : node->right, value);
    }

    void clearTree(Node* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

    void inOrderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inOrderTraversal(node->left, result);
        result.emplace_back(node->key, node->count);
        inOrderTraversal(node->right, result);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clearTree(root); }

    void insert(const T& value) {
        root = insertNode(root, value);
    }

    int depth() const {
        return calculateDepth(root);
    }

    int search(const T& value) const {
        Node* node = findNode(root, value);
        return node ? node->count : 0;
    }

    std::vector<std::pair<T, int>> getAllItems() const {
        std::vector<std::pair<T, int>> result;
        inOrderTraversal(root, result);
        return result;
    }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
