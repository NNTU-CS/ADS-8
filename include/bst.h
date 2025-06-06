// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>  // Для отладки

template <typename T>
class BinarySearchTree {
private:
    struct TreeNode {
        T value;
        int counter;
        TreeNode* left_child;
        TreeNode* right_child;
        
        explicit TreeNode(const T& val)
            : value(val), counter(1), 
              left_child(nullptr), right_child(nullptr) {}
    };

    TreeNode* root_node;

    TreeNode* insert_node(TreeNode* node, const T& val) {
        if (!node) return new TreeNode(val);
        
        if (val < node->value) {
            node->left_child = insert_node(node->left_child, val);
        } 
        else if (val > node->value) {
            node->right_child = insert_node(node->right_child, val);
        } 
        else {
            node->counter++;
        }
        return node;
    }

    TreeNode* remove_node(TreeNode* node, const T& val) {
        if (!node) return nullptr;

        if (val < node->value) {
            node->left_child = remove_node(node->left_child, val);
        } 
        else if (val > node->value) {
            node->right_child = remove_node(node->right_child, val);
        } 
        else {
            if (node->counter > 1) {
                node->counter--;
                return node;
            }

            if (!node->left_child) {
                TreeNode* right = node->right_child;
                delete node;
                return right;
            }
            if (!node->right_child) {
                TreeNode* left = node->left_child;
                delete node;
                return left;
            }

            TreeNode* successor = node->right_child;
            TreeNode* parent = node;
            while (successor->left_child) {
                parent = successor;
                successor = successor->left_child;
            }

            node->value = successor->value;
            node->counter = successor->counter;

            if (parent == node) {
                parent->right_child = successor->right_child;
            } else {
                parent->left_child = successor->right_child;
            }
            delete successor;
        }
        return node;
    }

    void delete_tree(TreeNode* node) {
        if (!node) return;
        delete_tree(node->left_child);
        delete_tree(node->right_child);
        delete node;
    }

    int find_value(TreeNode* node, const T& val) const {
        if (!node) return 0;
        
        if (val < node->value) {
            return find_value(node->left_child, val);
        } 
        else if (val > node->value) {
            return find_value(node->right_child, val);
        } 
        else {
            return node->counter;
        }
    }

    void print_inorder(TreeNode* node) const {
        if (!node) return;
        
        print_inorder(node->left_child);
        for (int i = 0; i < node->counter; ++i) {
            std::cout << node->value << ' ';
        }
        print_inorder(node->right_child);
    }

    int calculate_depth(TreeNode* node) const {
        if (!node) return -1;
        if (!node->left_child && !node->right_child) return 0;
        
        int left = calculate_depth(node->left_child);
        int right = calculate_depth(node->right_child);
        return std::max(left, right) + 1;
    }

    void collect_frequencies(TreeNode* node, 
                           std::vector<std::pair<T, int>>& freq) const {
        if (!node) return;
        
        collect_frequencies(node->left_child, freq);
        freq.emplace_back(node->value, node->counter);
        collect_frequencies(node->right_child, freq);
    }

public:
    BinarySearchTree() : root_node(nullptr) {}
    
    ~BinarySearchTree() {
        delete_tree(root_node);
    }

    void insert(const T& val) {
        root_node = insert_node(root_node, val);
    }

    void remove(const T& val) {
        root_node = remove_node(root_node, val);
    }

    void clear() {
        delete_tree(root_node);
        root_node = nullptr;
    }

    int count(const T& val) const {
        return find_value(root_node, val);
    }

    void print() const {
        print_inorder(root_node);
        std::cout << '\n';
    }

    int depth() const {
        return calculate_depth(root_node);
    }

    std::vector<std::pair<T, int>> get_frequencies() const {
        std::vector<std::pair<T, int>> freq;
        collect_frequencies(root_node, freq);
        return freq;
    }
};
#endif  // INCLUDE_BST_H_
