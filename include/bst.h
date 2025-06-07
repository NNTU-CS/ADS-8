// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
struct Node {
    T key;
    size_t count;
    Node *left;
    Node *right;

    explicit Node(const T &k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
 private:
    Node<T> *root;

    size_t depthHelper(Node<T> *node) const;
    void inorderHelper(std::vector<Node<T> *> &vec, Node<T> *node) const;

 public:
    BST() : root(nullptr) {}
    ~BST();
    bool insert(const T &val);
    bool search(const T &val);
    size_t depth() const;
    void inorder(std::vector<Node<T> *> &vec) const;
    void printFrequency() const;
};

template<typename T>
BST<T>::~BST() {
    clear(root);
}

template<typename T>
void BST<T>::clear(Node<T> *node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
bool BST<T>::insert(const T &val) {
    if (root == nullptr) {
        root = new Node<T>(val);
        return true;
    }

    Node<T> *current = root;
    while (true) {
        if (val == current->key) {
            ++current->count;
            break;
        }

        if (val < current->key) {
            if (current->left == nullptr) {
                current->left = new Node<T>(val);
                break;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                current->right = new Node<T>(val);
                break;
            } else {
                current = current->right;
            }
        }
    }
    return true;
}

template<typename T>
bool BST<T>::search(const T &val) {
    Node<T> *current = root;
    while (current != nullptr && current->key != val) {
        if (val < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current != nullptr;
}

template<typename T>
size_t BST<T>::depth() const {
    return depthHelper(root);
}

template<typename T>
size_t BST<T>::depthHelper(Node<T> *node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
}

template<typename T>
void BST<T>::inorder(std::vector<Node<T> *> &vec) const {
    inorderHelper(vec, root);
}

template<typename T>
void BST<T>::inorderHelper(std::vector<Node<T> *> &vec, Node<T> *node) const {
    if (node != nullptr) {
        inorderHelper(vec, node->left);
        vec.push_back(node);
        inorderHelper(vec, node->right);
    }
}

template<typename T>
void BST<T>::printFrequency() const {
    std::vector<Node<T> *> nodes;
    inorder(nodes);
    std::sort(nodes.begin(), nodes.end(), [](const Node<T> *a, const Node<T> *b) {
        return a->count > b->count || (a->count == b->count && a->key < b->key);
    });

    for (auto n : nodes) {
        std::cout << n->key << ": " << n->count << "\n";
    }
}

#endif  // INCLUDE_BST_H_
