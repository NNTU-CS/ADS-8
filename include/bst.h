// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(const T& value) : key(value), count(1), left(nullptr), right(nullptr) {}
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

    void printInOrder(Node<T>* node, std::ostream& out) const {
        if (node) {
            printInOrder(node->left, out);
            out << node->key << " : " << node->count << std::endl;
            printInOrder(node->right, out);
        }
    }

    int depth(Node<T>* node) const {
        if (!node) return 0;
        int left = depth(node->left);
        int right = depth(node->right);
        return 1 + std::max(left, right);
    }

    bool search(Node<T>* node, const T& value) const {
        if (!node) return false;
        if (node->key == value) return true;
        return value < node->key ? search(node->left, value) : search(node->right, value);
    }

    void collect(Node<T>* node, std::vector<Node<T>*>& nodes) const {
        if (!node) return;
        collect(node->left, nodes);
        nodes.push_back(node);
        collect(node->right, nodes);
    }

 public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        insert(root, value);
    }

    void print(std::ostream& out = std::cout) const {
        printInOrder(root, out);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    std::vector<Node<T>*> getNodes() const {
        std::vector<Node<T>*> result;
        collect(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
