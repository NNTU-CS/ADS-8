// Copyright 2021 NNTU-CS
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

    void insert_helper(Node*& node, const T& data);
    int calculate_depth(const Node* node) const;
    Node* find_node(Node* node, const T& value);
    void traverse_in_order(const Node* node) const;
    void collect_frequencies(const Node* node, std::vector<std::pair<T, int>>& freqs) const;
    void clear_subtree(Node* node);

 public:
    BST() : root(nullptr) {}
    ~BST();
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& data);
    int depth() const;
    int search(const T& value) const;
    void print_in_order() const;
    std::vector<std::pair<T, int>> get_frequencies() const;
};


template <typename T>
BST<T>::~BST() {
    clear_subtree(root);
}

template <typename T>
void BST<T>::clear_subtree(Node* node) {
    if (node) {
        clear_subtree(node->left);
        clear_subtree(node->right);
        delete node;
    }
}

template <typename T>
void BST<T>::insert(const T& data) {
    insert_helper(root, data);
}

template <typename T>
void BST<T>::insert_helper(Node*& node, const T& data) {
    if (!node) {
        node = new Node(data);
        return;
    }

    if (data < node->data) {
        insert_helper(node->left, data);
    } else if (data > node->data) {
        insert_helper(node->right, data);
    } else {
        node->count++;
    }
}

template <typename T>
int BST<T>::depth() const {
    return calculate_depth(root) - 1;
}

template <typename T>
int BST<T>::calculate_depth(const Node* node) const {
    if (!node) return 0;
    return 1 + std::max(calculate_depth(node->left),
        calculate_depth(node->right));
}

template <typename T>
int BST<T>::search(const T& value) const {
    const Node* result = find_node(root, value);
    return result ? result->count : 0;
}

template <typename T>
typename BST<T>::Node* BST<T>::find_node(const Node* node, const T& value) const {
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
    collect_frequencies(root, frequencies);
    return frequencies;
}

template <typename T>
void BST<T>::collect_frequencies(const Node* node,
    std::vector<std::pair<T, int>>& freqs) const {
    if (node) {
        collect_frequencies(node->left, freqs);
        freqs.emplace_back(node->data, node->count);
        collect_frequencies(node->right, freqs);
    }
}

#endif  // INCLUDE_BST_H_
