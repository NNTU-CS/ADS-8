// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* addNode(Node* node, const T& value) {
        if (!node)
            return new Node(value);
        if (value < node->data)
            node->left = addNode(node->left, value);
        else if (value > node->data)
            node->right = addNode(node->right, value);
        else
            node->count++;
        return node;
    }
    Node* search(Node* node, const T& value) const {
        if (!node)
            return nullptr;
        if (value == node->data)
            return node;
        else if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }
    int depth(Node* node) const {
        if (!node)
            return 0;
        int left = depth(node->left);
        int right = depth(node->right);
        return 1 + std::max(left, right);
    }
    void Travel(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node) {
            Travel(node->left, result);
            result.emplace_back(node->data, node->count);
            Travel(node->right, result);
        }
    }
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }
    void add(const T& value) {
        root = addNode(root, value);
    }
    int search(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }
    int depth() const {
        return depth(root);
    }
    void getAll(std::vector<std::pair<T, int>>& result) const {
        Travel(root, result);
    }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);
#endif  // INCLUDE_BST_H_
