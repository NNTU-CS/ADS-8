// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

template <typename T>
class BST {
 private:
    struct TreeNode {
        T value;
        int frequency;
        TreeNode* left;
        TreeNode* right;
        explicit TreeNode(const T& val)
            : value(val), frequency(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* insert(TreeNode* node, const T& val) {
        if (!node) return new TreeNode(val);
        if (val < node->value) {
            node->left = insert(node->left, val);
        } else if (val > node->value) {
            node->right = insert(node->right, val);
        } else {
            node->frequency++;
        }
        return node;
    }
    int calculate_depth(const TreeNode* node) const {
        if (!node) return -1;
        if (!node->left && !node->right) return 0;
        int left = calculate_depth(node->left);
        int right = calculate_depth(node->right);
        return std::max(left, right) + 1;
    }
    void collect_frequencies(const TreeNode* node,
                           std::vector<std::pair<T, int>>& freq) const {
        if (!node) return;
        collect_frequencies(node->left, freq);
        freq.emplace_back(node->value, node->frequency);
        collect_frequencies(node->right, freq);
    }
    void delete_tree(TreeNode* node) {
        if (!node) return;
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
    int find_frequency(const TreeNode* node, const T& val) const {
        if (!node)
            return 0;
        if (val < node->value)
            return find_frequency(node->left, val);
        else if (val > node->value)
            return find_frequency(node->right, val);
        else
            return node->frequency;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        delete_tree(root);
    }
    void add(const T& val) {
        root = insert(root, val);
    }
    int depth() const {
        return calculate_depth(root);
    }
    std::vector<std::pair<T, int>> getFrequencies() const {
        std::vector<std::pair<T, int>> freq;
        collect_frequencies(root, freq);
        return freq;
    }
    int search(const T& val) const {
        return find_frequency(root, val);
    }
};

#endif  // INCLUDE_BST_H_
