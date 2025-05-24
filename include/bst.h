// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template<typename T>
class BST {
 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    bool search(const T&);
    void insert(const T&);
    int depth(Node<T>* node);
    void inorderTraversal(Node<T>* node);

    Node<T>* getRoot() const { return root; }

    class Helper {
     public:
        static void traverse(Node<T>* node, std::vector<WordFrequencyPair>& list) {
            if (node == nullptr) return;
            traverse(node->left, list);
            list.emplace_back(node->key, node->freq);
            traverse(node->right, list);
        }
    };

 private:

    Node<T>* root;

    void clear(Node<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#endif  // INCLUDE_BST_H_
