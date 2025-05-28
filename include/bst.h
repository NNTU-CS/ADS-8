// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template <typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& value) : key(value), count(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
 public:
    BST() : root_(nullptr) {}

    ~BST() {
        destroyTree(root_);
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& value) {
        root_ = insertRecursive(root_, value);
    }

    Node<T>* search(const T& value) const {
        return searchRecursive(root_, value);
    }

    int depth() const {
        return depthRecursive(root_);
    }

    void getWordFrequencies(std::vector<std::pair<T, int>>& vec) const {
        getWordFrequenciesRecursive(root_, vec);
    }

 private:
    Node<T>* root_;

    Node<T>* insertRecursive(Node<T>* node, const T& value) {
        if (node == nullptr) {
            return new Node<T>(value);
        }

        if (value < node->key) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->key) {
            node->right = insertRecursive(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    Node<T>* searchRecursive(Node<T>* node, const T& value) const {
        if (node == nullptr || node->key == value) {
            return node;
        }

        if (value < node->key) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }

    int depthRecursive(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        int left_depth = depthRecursive(node->left);
        int right_depth = depthRecursive(node->right);
        return 1 + std::max(left_depth, right_depth);
    }

    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void getWordFrequenciesRecursive(Node<T>* node, std::vector<std::pair<T, int>>& vec) const {
        if (node != nullptr) {
            getWordFrequenciesRecursive(node->left, vec);
            vec.push_back({node->key, node->count});
            getWordFrequenciesRecursive(node->right, vec);
        }
    }
};

#endif  // INCLUDE_BST_H_
