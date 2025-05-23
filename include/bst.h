// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
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

        explicit Node(const T& data) : data(data), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& data);
    int depth(Node* node) const;
    Node* search(Node* node, const T& value);
    void printInOrder(Node* node) const;
    void collectFrequencies(Node* node, std::vector<std::pair<T, int>>& frequencies) const;
    void freeMemory(Node* node);

 public:
    BST() : root(nullptr) {}
    ~BST();

    void insert(const T& data);
    int depth() const;
    int search(const T& value);
    void printInOrder() const;

    std::vector<std::pair<T, int>> getFrequencies() const;
};

template <typename T>
BST<T>::~BST() {
    freeMemory(root);
}

template <typename T>
void BST<T>::freeMemory(Node* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

template <typename T>
void BST<T>::insert(const T& data) {
    insert(root, data);
}

template <typename T>
void BST<T>::insert(Node*& node, const T& data) {
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

template <typename T>
int BST<T>::depth() const {
    return depth(root)-1;
}

template <typename T>
int BST<T>::depth(Node* node) const {
    if (node == nullptr) {
        return 0;
    } else {
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return std::max(leftDepth, rightDepth)+1;
    }
}

template <typename T>
int BST<T>::search(const T& value) {
    Node* result = search(root, value);
    return result ? result->count : 0;
}

template <typename T>
typename BST<T>::Node* BST<T>::search(Node* node, const T& value) {
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

template <typename T>
void BST<T>::printInOrder() const {
    printInOrder(root);
}

template <typename T>
void BST<T>::printInOrder(Node* node) const {
    if (node != nullptr) {
        printInOrder(node->left);
        std::cout << node->data << " (" << node->count << ")" << std::endl;
        printInOrder(node->right);
    }
}

template <typename T>
std::vector<std::pair<T, int>> BST<T>::getFrequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    collectFrequencies(root, frequencies);
    return frequencies;
}

template <typename T>
void BST<T>::collectFrequencies(Node* node, std::vector<std::pair<T, int>>& frequencies) const {
    if (node != nullptr) {
        collectFrequencies(node->left, frequencies);
        frequencies.push_back({ node->data, node->count });
        collectFrequencies(node->right, frequencies);
    }
}

#endif  // INCLUDE_BST_H_
