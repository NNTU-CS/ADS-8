// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& value)
        : key(value), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
 private:
    Node<T>* root;

    void insert(Node<T>*& node, const T& value) {
        if (!node) {
            node = new Node<T>(value);
        } else if (value < node->key) {
            insert(node->left, value);
        } else if (value > node->key) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }

    int depth(Node<T>* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    bool search(Node<T>* node, const T& value) const {
        if (!node) return false;
        if (node->key == value) return true;
        return value < node->key
            ? search(node->left, value)
            : search(node->right, value);
    }

    void collect(Node<T>* node, std::vector<Node<T>*>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.push_back(node);
        collect(node->right, out);
    }

 public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    std::vector<Node<T>*> getNodes() const {
        std::vector<Node<T>*> v;
        collect(root, v);
        return v;
    }

    void print(std::ostream& out = std::cout) const {
        std::vector<Node<T>*> v;
        collect(root, v);
        std::sort(v.begin(), v.end(),
            [](Node<T>* a, Node<T>* b){ return a->key < b->key; });
        for (auto n : v) {
            out << n->key << " : " << n->count << "\n";
        }
    }
};

#endif  // INCLUDE_BST_H_