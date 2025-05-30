// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

template <typename T>
class BST {
private:
    // Узел дерева
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        Node(T value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value);
    void inOrder(Node* node, std::vector<std::pair<T, int>>& freqList);
    int depth(Node* node);
    Node* search(Node* node, const T& value);

public:
    BST() : root(nullptr) {}
    void insert(const T& value);
    void inOrder(std::vector<std::pair<T, int>>& freqList);
    int depth();
    Node* search(const T& value);
    Node* getRoot() { return root; } // Метод для получения корня дерева
};

// Вставка в дерево
template <typename T>
void BST<T>::insert(const T& value) {
    insert(root, value);
}

template <typename T>
void BST<T>::insert(Node*& node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (value == node->data) {
        node->count++; // Увеличиваем счетчик, если слово уже существует
    } else if (value < node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

// Обход дерева в порядке возрастания
template <typename T>
void BST<T>::inOrder(std::vector<std::pair<T, int>>& freqList) {
    inOrder(root, freqList);
}

template <typename T>
void BST<T>::inOrder(Node* node, std::vector<std::pair<T, int>>& freqList) {
    if (node) {
        inOrder(node->left, freqList);
        freqList.emplace_back(node->data, node->count);
        inOrder(node->right, freqList);
    }
}

// Измерение глубины дерева
template <typename T>
int BST<T>::depth() {
    return depth(root);
}

template <typename T>
int BST<T>::depth(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return std::max(leftDepth, rightDepth) + 1;
    }
}

// Поиск в дереве
template <typename T>
typename BST<T>::Node* BST<T>::search(const T& value) {
    return search(root, value);
}

template <typename T>
typename BST<T>::Node* BST<T>::search(Node* node, const T& value) {
    if (node == nullptr || node->data == value) {
        return node;
    }
    if (value < node->data) {
        return search(node->left, value);
    }
    return search(node->right, value);
}
#endif  // INCLUDE_BST_H_
