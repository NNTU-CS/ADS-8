// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>
#include <vector>
#include <stack>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        expliced Node(const T& value): count(1), left(nullptr), right(nullptr), value(value) {}
    };
    Node* root; 
    Node* addNode(Node*, const T&);
    void delTree(Node*);
    int depth(const Node*) const;
    void collectNodes(Node*, std::vector<std::pair<T, int>>&) const;
 public:
    BST();
    ~BST();
    void add(const T&);
    void clear();
    int depth() const;
    int search(const T&) const;
    std::vector<std::pair<T, int>> getWordsWithCounts() const;
};

template<typename T>
BST<T>::BST() : root(nullptr) {}

template<typename T>
BST<T>::~BST() {
    clear();
}

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* node, const T& value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value == node->value) {
        node->count++;
    } else if (value < node->value) {
        node->left = addNode(node->left, value);
    } else {
        node->right = addNode(node->right, value);
    }
    return node;
}

template<typename T>
void BST<T>::add(const T& value) {
    root = addNode(root, value);
}

template<typename T>
void BST<T>::delTree(Node* node) {
    if (node) {
        delTree(node->left);
        delTree(node->right);
        delete node;
    }
}

template<typename T>
void BST<T>::clear() {
    delTree(root);
    root = nullptr;
}

template<typename T>
int BST<T>::depth(const Node* node) const {
    if (!node) return 0;
    return std::max(depth(node->left), depth(node->right)) + 1;
}

template<typename T>
int BST<T>::depth() const {
    return depth(root)-1;
}

template<typename T>
int BST<T>::search(const T& value) const {
    Node* current = root;
    while (current) {
        if (value == current->value) {
            return current->count;
        }
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0;
}

template<typename T>
std::vector<std::pair<T, int>> BST<T>::getWordsWithCounts() const {
    std::vector<std::pair<T, int>> result;
    collectNodes(root, result);
    return result;
}

template<typename T>
void BST<T>::collectNodes(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    collectNodes(node->left, result);
    result.emplace_back(node->value, node->count);
    collectNodes(node->right, result);
}

#endif  // INCLUDE_BST_H_

