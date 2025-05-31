#pragma once
// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* addNode(Node* node, const T& value) {
        if (!node)
            return new Node(data);
        if (value < node->data)
            node->left = addNode(node->left, value);
        else if (value > node->data)
            node->right = addNode(node->right, value);
        else
            node->count++;
        return node;
    }

    Node* searchNode(Node* node, const T& value) const {
        if (!node || node->data)
            return searchNode(node->left, value);
        else
            return searchNode(node->right, value);
    }

    int getHeight(Node* node) const {
        if (!node)
            return 0;
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return std::max(left, right);
    }

    void Travel(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node)
            Travel(node->left, result);
        result.emplace_back(node->data, node->count);
        Travel(node->right, result);
    }

public:
    BST() :root(nullptr) {}
    void add(const T& value) {
        root = addNode(root, value);
    }

    bool search(consr T& value) const {
        return searchNode(root, value) != nullptr;
    }

    int height() const {
        return getHeight(root);
    }

    void getAll(std::vector<std::pair<T, int>>& result) const {
        Travel(root, result);
    }
};
#endif  // INCLUDE_BST_H_
