// Copyright 2021 NNTU-CS
#pragma once

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& data)
            : data(data), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& data);
    int calculate_depth(const Node* node) const;
    const Node* find_node(const Node* node, const T& value) const;
    void traverse_in_order(const Node* node) const;
    void gather_frequencies(const Node* node, std::vector<std::pair<T, int>>& frequencies) const;
    void clear_tree(Node* node);

 public:
    BST() : root(nullptr) {}
    ~BST();
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& data);
    int depth() const;
    bool search(const T& value) const;
    int count(const T& value) const;
    void print_in_order() const;
    std::vector<std::pair<T, int>> get_frequencies() const;
};

template <typename T>
BST<T>::~BST() {
    clear_tree(root);
}

template <typename T>
void BST<T>::clear_tree(Node* node) {
    if (node) {
        clear_tree(node->left);
        clear_tree(node->right);
        delete node;
    }
}

template <typename T>
bool BST<T>::search(const T& value) const {
    return find_node(root, value) != nullptr;
}

template <typename T>
void BST<T>::insert(const T& data) {
    insert(root, data);
}

template <typename T>
void BST<T>::insert(Node*& node, const T& data) {
    if (!node) {
        node = new Node(data);
        return;
    }

    if (data < node->data) {
        insert(node->left, data);
    } else if (data > node->data) {
        insert(node->right, data);
    } else {
        node->count++;
    }
}

template <typename T>
int BST<T>::depth() const {
    return calculate_depth(root);
}

template <typename T>
int BST<T>::calculate_depth(const Node* node) const {
    if (!node) return 0;
    return 1 + std::max(calculate_depth(node->left),
        calculate_depth(node->right));
}

template <typename T>
int BST<T>::count(const T& value) const {
    const Node* result = find_node(root, value);
    return result ? result->count : 0;
}

template <typename T>
const typename BST<T>::Node* BST<T>::find_node(const Node* node, const T& value) const {
    if (!node) return nullptr;

    if (value == node->data) {
        return node;
    }
    return value < node->data ? find_node(node->left, value)
        : find_node(node->right, value);
}

template <typename T>
void BST<T>::print_in_order() const {
    traverse_in_order(root);
}

template <typename T>
void BST<T>::traverse_in_order(const Node* node) const {
    if (node) {
        traverse_in_order(node->left);
        std::cout << node->data << " (" << node->count << ")\n";
        traverse_in_order(node->right);
    }
}

template <typename T>
std::vector<std::pair<T, int>> BST<T>::get_frequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    gather_frequencies(root, frequencies);
    return frequencies;
}

template <typename T>
void BST<T>::gather_frequencies(const Node* node,
    std::vector<std::pair<T, int>>& frequencies) const {
    if (node) {
        gather_frequencies(node->left, frequencies);
        frequencies.emplace_back(node->data, node->count);
        gather_frequencies(node->right, frequencies);
    }
}

#endif  // INCLUDE_BST_H_
