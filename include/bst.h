// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>  // Для отладки

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

template <typename KeyType>
class BST {
private:
    struct Node {
        KeyType value;
        int frequency;
        Node* left_child;
        Node* right_child;

        explicit Node(const KeyType& val)
            : value(val), frequency(1), left_child(nullptr), right_child(nullptr) {}
    };
    Node* root_node;
    Node* insertNode(Node* current_node, const KeyType& new_value) {
        if (!current_node) return new Node(new_value);

        if (new_value == current_node->value) {
            current_node->frequency++;
        } else if (new_value < current_node->value) {
            current_node->left_child = insertNode(current_node->left_child, new_value);
        } else {
            current_node->right_child = insertNode(current_node->right_child, new_value);
        }
        return current_node;
    }
    int calculateHeight(Node* node) const {
        if (!node) return -1;
        int left_height = calculateHeight(node->left_child);
        int right_height = calculateHeight(node->right_child);
        return 1 + std::max(left_height, right_height);
    }
    int findFrequency(Node* node, const KeyType& search_value) const {
        if (!node) return 0;
        if (search_value == node->value) return node->frequency;
        return search_value < node->value 
            ? findFrequency(node->left_child, search_value) 
            : findFrequency(node->right_child, search_value);
    }
    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left_child);
        deleteTree(node->right_child);
        delete node;
    }
    void traverseInOrder(Node* node, std::vector<std::pair<KeyType, int>>& result) const {
        if (!node) return;
        traverseInOrder(node->left_child, result);
        result.emplace_back(node->value, node->frequency);
        traverseInOrder(node->right_child, result);
    }

    Node* copySubtree(Node* node) const {
        if (!node) return nullptr;
        Node* new_node = new Node(node->value);
        new_node->frequency = node->frequency;
        new_node->left_child = copySubtree(node->left_child);
        new_node->right_child = copySubtree(node->right_child);
        return new_node;
    }
public:
    BST() : root_node(nullptr) {}
    BST(const BST& other) {
        root_node = copySubtree(other.root_node);
    }
    
    BST(BST&& other) noexcept : root_node(other.root_node) {
        other.root_node = nullptr;
    }
    
    ~BST() {
        deleteTree(root_node);
    }
    
    BST& operator=(const BST& other) {
        if (this != &other) {
            deleteTree(root_node);
            root_node = copySubtree(other.root_node);
        }
        return *this;
    }
    
    BST& operator=(BST&& other) noexcept {
        if (this != &other) {
            deleteTree(root_node);
            root_node = other.root_node;
            other.root_node = nullptr;
        }
        return *this;
    }

    void insert(const KeyType& value) {
        root_node = insertNode(root_node, value);
    }

    bool contains(const KeyType& value) const {
        Node* current = root_node;
        while (current) {
            if (value == current->value) return true;
            if (value < current->value) current = current->left_child;
            else current = current->right_child;
        }
        return false;
    }

    int depth() const {
        return calculateHeight(root_node);
    }

    int getFrequency(const KeyType& value) const {
        return findFrequency(root_node, value);
    }

    std::vector<std::pair<KeyType, int>> getAllEntries() const {
        std::vector<std::pair<KeyType, int>> result;
        traverseInOrder(root_node, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
