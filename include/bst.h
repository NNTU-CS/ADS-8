// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <utility>
#include <vector>

template <typename Key>
class BST {
private:
    struct Node {
        Key key;
        int count;
        Node* left;
        Node* right;
        Node(const Key& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Рекурсивная вставка
    Node* insertHelper(Node* node, const Key& key) {
        if (!node) return new Node(key);
        if (key < node->key) {
            node->left = insertHelper(node->left, key);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key);
        } else {
            node->count++;
        }
        return node;
    }

    // Поиск минимального узла
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Рекурсивное удаление
    Node* removeHelper(Node* node, const Key& key) {
        if (!node) return nullptr;
        
        if (key < node->key) {
            node->left = removeHelper(node->left, key);
        } else if (key > node->key) {
            node->right = removeHelper(node->right, key);
        } else {
            if (node->count > 1) {
                node->count--;
                return node;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->count = temp->count;
            node->right = removeHelper(node->right, temp->key);
        }
        return node;
    }

    // Рекурсивный поиск
    bool searchHelper(Node* node, const Key& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }

    // Рекурсивное вычисление глубины
    int depthHelper(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
    }

    // Рекурсивное копирование
    Node* copyTree(Node* node) const {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key);
        newNode->count = node->count;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    // Рекурсивное удаление всех узлов
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Вспомогательный метод для in-order обхода
    void inOrderHelper(Node* node, std::vector<std::pair<Key, int>>& vec) const {
        if (!node) return;
        inOrderHelper(node->left, vec);
        vec.push_back(std::make_pair(node->key, node->count));
        inOrderHelper(node->right, vec);
    }

public:
    BST() : root(nullptr) {}
    
    BST(const BST& other) {
        root = copyTree(other.root);
    }
    
    BST(BST&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    
    ~BST() {
        clear(root);
    }
    
    BST& operator=(const BST& other) {
        if (this != &other) {
            clear(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    BST& operator=(BST&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    
    void insert(const Key& value) {
        root = insertHelper(root, value);
    }
    
    void remove(const Key& value) {
        root = removeHelper(root, value);
    }
    
    bool search(const Key& value) const {
        return searchHelper(root, value);
    }
    
    int depth() const {
        return depthHelper(root);
    }
    
    // Метод для сбора данных в порядке in-order
    std::vector<std::pair<Key, int>> inOrder() const {
        std::vector<std::pair<Key, int>> result;
        inOrderHelper(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
