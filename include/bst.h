// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <vector>
#include <utility>

template <typename T>
struct Node {
    T value;
    int count;
    Node<T>* left;
    Node<T>* right;

    Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
};
template <typename T>
class BST {
public:
    BST() : root_(nullptr) {}
    void getWordsAndFrequencies(std::vector<std::pair<T, int>>& freqVec) const {
        getWordsAndFrequenciesRec(root_, freqVec);
    }
    void insert(const T& value) {
        root_ = insertRec(root_, value);
    }
    int depth() const {
        return depthRec(root_);
    }
    bool search(const T& value) const {
        return searchRec(root_, value);
    }
    void printFreq(std::ostream& os) const {
        printFreqRec(root_, os);
    }

private:
    Node<T>* root_;
    Node<T>* insertRec(Node<T>* node, const T& value) {
        if (node == nullptr) {
            return new Node<T>(value);
        }
        if (value < node->value) {
            node->left = insertRec(node->left, value);
        } else if (value > node->value) {
            node->right = insertRec(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }
    int depthRec(const Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = depthRec(node->left);
        int rightDepth = depthRec(node->right);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }
    bool searchRec(const Node<T>* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (value < node->value) {
            return searchRec(node->left, value);
        } else if (value > node->value) {
            return searchRec(node->right, value);
        } else {
            return true;
        }
    }
    void printFreqRec(const Node<T>* node, std::ostream& os) const {
        if (node == nullptr) {
            return;
        }
        printFreqRec(node->left, os);
        os << node->value << ": " << node->count << std::endl;
        printFreqRec(node->right, os);
    }
    void getWordsAndFrequenciesRec(const Node<T>* node, std::vector<std::pair<T, int>>& freqVec) const {
        if (node == nullptr) {
            return;
        }
        getWordsAndFrequenciesRec(node->left, freqVec);
        freqVec.push_back({node->value, node->count});
        getWordsAndFrequenciesRec(node->right, freqVec);
    }
};

#endif // INCLUDE_BST_H_
