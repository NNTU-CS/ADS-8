// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <iostream>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        Node(T value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Вспомогательные методы для рекурсивного добавления и поиска
    void insert(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (value == node->data) {
            node->count++;
        } else if (value < node->data) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    bool search(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        } else if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void printFreq(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printFreq(node->left);
        std::cout << node->data << ": " << node->count << std::endl;
        printFreq(node->right);
    }

    void depth(Node* node, int& max_depth, int current_depth) const {
        if (node == nullptr) {
            return;
        }
        if (current_depth > max_depth) {
            max_depth = current_depth;
        }
        depth(node->left, max_depth, current_depth + 1);
        depth(node->right, max_depth, current_depth + 1);
    }

public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        insert(root, value);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    void printFreq() const {
        printFreq(root);
    }

    int depth() const {
        int max_depth = 0;
        depth(root, max_depth, 1);
        return max_depth;
    }

    ~BST() {
        // Очистка памяти
        delete root;
    }
};
#endif  // INCLUDE_BST_H_
