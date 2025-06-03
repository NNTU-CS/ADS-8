// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;


    Node* insertHelper(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }


    Node* removeHelper(Node* node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = removeHelper(node->left, value);
        } else if (value > node->data) {
            node->right = removeHelper(node->right, value);
        } else {
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
            node->data = temp->data;
            node->right = removeHelper(node->right, temp->data);
        }
        return node;
    }


    bool searchHelper(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) {
            return searchHelper(node->left, value);
        }
        return searchHelper(node->right, value);
    }


    int depthHelper(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
    }

    Node* copyTree(Node* node) const {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }


    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
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
    
    void insert(const T& value) {
        root = insertHelper(root, value);
    }
    
    void remove(const T& value) {
        root = removeHelper(root, value);
    }
    
    bool search(const T& value) const {
        return searchHelper(root, value);
    }
    
    int depth() const {
        return depthHelper(root);
    }
};

#endif  // INCLUDE_BST_H_
