// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
private:
    struct Node {
        T word;
        int count;
        Node* left;
        Node* right;

        Node(const T& w) : word(w), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void insert(Node*& node, const T& w) {
        if (!node) {
            node = new Node(w);
            return;
        }
        if (w < node->word) {
            insert(node->left, w);
        } else if (w > node->word) {
            insert(node->right, w);
        } else {
            node->count++;
        }
    }
    void collect(Node* node, std::vector<std::pair<T, int>>& freqList) const {
        if (!node) return;
        collect(node->left, freqList);
        freqList.emplace_back(node->word, node->count);
        collect(node->right, freqList);
    }
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    int search(Node* node, const T& w) const {
        if (!node) return 0;
        if (w < node->word) {
            return search(node->left, w);
        } else if (w > node->word) {
            return search(node->right, w);
        } else {
            return node->count;
        }
    }
public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void add(const T& w) { insert(root, w); }
    std::vector<std::pair<T, int>> getFrequencies() const {
        std::vector<std::pair<T, int>> freqList;
        collect(root, freqList);
        return freqList;
    }
    int depth() const {
        return depth(root);
    }
    int search(const T& w) const {
        return search(root, w);
    }
private:
    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }
};

#endif // INCLUDE_BST_H_
