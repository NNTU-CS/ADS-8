// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_ 
#define INCLUDE_BST_H_ 

#include <vector>
#include <utility>
#include <string>

template <typename T>
class BinarySearchTree {
    struct TreeNode {
        T data;
        int frequency;
        TreeNode* left_child;
        TreeNode* right_child;
        explicit TreeNode(const T& val) : data(val), frequency(1),
                                        left_child(nullptr), right_child(nullptr) {}
    };

    TreeNode* root_node;

    void add_node(TreeNode*& node, const T& value) {
        if (!node) {
            node = new TreeNode(value);
            return;
        }
        if (value == node->data) {
            node->frequency++;
        } else if (value < node->data) {
            add_node(node->left_child, value);
        } else {
            add_node(node->right_child, value);
        }
    }

    int find_count(TreeNode* node, const T& value) const {
        if (!node) return 0;
        if (value == node->data) return node->frequency;
        return find_count(value < node->data ? node->left_child : node->right_child, value);
    }

    int calculate_depth(TreeNode* node) const {
        if (!node) return 0;
        int left_depth = calculate_depth(node->left_child);
        int right_depth = calculate_depth(node->right_child);
        return 1 + (left_depth > right_depth ? left_depth : right_depth);
    }

    void traverse_inorder(TreeNode* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        traverse_inorder(node->left_child, result);
        result.emplace_back(node->data, node->frequency);
        traverse_inorder(node->right_child, result);
    }

    void delete_tree(TreeNode* node) {
        if (!node) return;
        delete_tree(node->left_child);
        delete_tree(node->right_child);
        delete node;
    }

 public:
    BinarySearchTree() : root_node(nullptr) {}
    ~BinarySearchTree() { delete_tree(root_node); }

    void insert(const T& value) { add_node(root_node, value); }
    int search(const T& value) const { return find_count(root_node, value); }
    int depth() const { return calculate_depth(root_node); }
    std::vector<std::pair<T, int>> get_all_elements() const {
        std::vector<std::pair<T, int>> elements;
        traverse_inorder(root_node, elements);
        return elements;
    }
};

#endif //INCLUDE_BST_H_ 
