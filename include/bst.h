// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T word;
        int count;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root = nullptr;

    Node* addNodeTree(Node* node, const T& word) {
        if (node == nullptr) {
            node = new Node {word, 1};
        } else if (node->word > word) {
            node->left = addNodeTree(node->left, word);
        } else if (node->word < word) {
            node->right = addNodeTree(node->right, word);
        } else {
            node->count++;
        }
        return node;
    }

    int searchNodeTree(Node* node, const T& word) {
        if (node == nullptr) {
            return 0;
        } else if (node->word > word) {
            return searchNodeTree(node->left, word);
        } else if (node->word < word) {
            return searchNodeTree(node->right, word);
        } else {
            return node->count;
        }
    }

    int getDepthTree(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = getDepthTree(node->left);
        int rightDepth = getDepthTree(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

 public:
    void addNode(const T& word) {
        root = addNodeTree(root, word);
    }

    int search(const T& word) {
        return searchNodeTree(root, word);
    }

    int depth() {
        return getDepthTree(root) - 1;
    }
};

#endif  // INCLUDE_BST_H_
