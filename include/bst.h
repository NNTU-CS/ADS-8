// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template <typename T>
class BST {
 public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void insert(const T& value) {
        root = insertNode(root, value);
    }
    int depth() const {
        return getDepth(root);
    }
    Node* search(const T& value) const {
        return searchNode(root, value);
    }
    Node* getRoot() const {
        return root;
    }
 private:
    Node* root;
    Node* insertNode(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->key) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->key) {
            node->right = insertNode(node->right, value);
        }
        else {
            node->count++;
        }
        return node;
    }
    int getDepth(Node* node) const {
        if (!node) return 0;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return std::max(leftDepth, rightDepth) + 1;
    }
    Node* searchNode(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->key) return node;
        if (value < node->key) return searchNode(node->left, value);
        else return searchNode(node->right, value);
    }
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};
struct WordFreq {
    std::string word;
    int freq;
    WordFreq(const std::string& w, int f) : word(w), freq(f) {}
};
void makeTree(BST<std::string>&, const char*);
void inorderCollect(BST<std::string>::Node*, std::vector<WordFreq>&);
void printFreq(BST<std::string>&);
#endif  // INCLUDE_BST_H_
