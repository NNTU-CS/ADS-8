// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
struct Node {
    T key;
    int freq;
    Node<T>* left;
    Node<T>* right;

    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    Node<T>* root;
    friend class Helper;

    void clear(Node<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    bool search(const T&);
    void insert(const T&);
    int depth(Node<T>* node);
    void inorderTraversal(Node<T>* node);
};

#endif  // INCLUDE_BST_H_
