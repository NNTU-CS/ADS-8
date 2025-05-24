// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
struct Node {
    T key;
    int freq;
    Node<T>* left;
    Node<T>* right;

    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    Node<T>* root;  // Приватный член класса

    // Разрешаем доступ классу Helper ко всему, что доступно внутри BST
    friend class Helper;

public:
    BST() : root(nullptr) {}  // Конструктор
    ~BST() { clear(root); }   // Деструктор

    bool search(const T&);
    void insert(const T&);
    int depth(Node<T>* node);
    void inorderTraversal(Node<T>* node);
    void clear(Node<T>* node);

private:
    void clear(Node<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

template<typename T>
BST<T>::BST() : root(nullptr) {}

template<typename T>
BST<T>::~BST() { clear(root); }

template<typename T>
void BST<T>::clear(Node<T>* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
void BST<T>::insert(const T& word) {
    auto* newNode = new Node<T>(word);
    if (root == nullptr) {
        root = newNode;
    } else {
        Node<T>* current = root;
        while (true) {
            if (word == current->key) {
                ++current->freq;
                break;
            } else if (word < current->key && current->left == nullptr) {
                current->left = newNode;
                break;
            } else if (word > current->key && current->right == nullptr) {
                current->right = newNode;
                break;
            } else if (word < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
}

template<typename T>
bool BST<T>::search(const T& word) {
    Node<T>* current = root;
    while (current != nullptr) {
        if (word == current->key) {
            return true;
        } else if (word < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

template<typename T>
int BST<T>::depth(Node<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(depth(node->left), depth(node->right));
}

#endif  // INCLUDE_BST_H_
