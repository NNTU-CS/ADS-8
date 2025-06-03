// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <utility>

template <typename Key, typename Value = void>
class BST {
private:
    struct Node {
        Key key;
        Node* left;
        Node* right;
        Node(const Key& k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertHelper(Node* node, const Key& key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertHelper(node->left, key);
        else if (key > node->key) node->right = insertHelper(node->right, key);
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, const Key& key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = removeHelper(node->left, key);
        else if (key > node->key) node->right = removeHelper(node->right, key);
        else {
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
            node->right = removeHelper(node->right, temp->key);
        }
        return node;
    }

    bool searchHelper(Node* node, const Key& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return key < node->key ? searchHelper(node->left, key) : searchHelper(node->right, key);
    }

    int depthHelper(Node* node) const {
        return node ? 1 + std::max(depthHelper(node->left), depthHelper(node->right)) : 0;
    }

    Node* copyTree(Node* node) const {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key);
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
    BST(const BST& other) : root(copyTree(other.root)) {}
    BST(BST&& other) noexcept : root(other.root) { other.root = nullptr; }
    ~BST() { clear(root); }

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

    void insert(const Key& key) { root = insertHelper(root, key); }
    void remove(const Key& key) { root = removeHelper(root, key); }
    bool search(const Key& key) const { return searchHelper(root, key); }
    int depth() const { return depthHelper(root); }
};

template <typename Key>
class BST<Key, int> {
private:
    struct Node {
        Key key;
        int count;
        Node* left;
        Node* right;
        Node(const Key& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertHelper(Node* node, const Key& key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertHelper(node->left, key);
        else if (key > node->key) node->right = insertHelper(node->right, key);
        else node->count++;
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, const Key& key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = removeHelper(node->left, key);
        else if (key > node->key) node->right = removeHelper(node->right, key);
        else {
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

    bool searchHelper(Node* node, const Key& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return key < node->key ? searchHelper(node->left, key) : searchHelper(node->right, key);
    }

    int depthHelper(Node* node) const {
        return node ? 1 + std::max(depthHelper(node->left), depthHelper(node->right)) : 0;
    }

    Node* copyTree(Node* node) const {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key);
        newNode->count = node->count;
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
    BST(const BST& other) : root(copyTree(other.root)) {}
    BST(BST&& other) noexcept : root(other.root) { other.root = nullptr; }
    ~BST() { clear(root); }

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

    void insert(const Key& key) { root = insertHelper(root, key); }
    void remove(const Key& key) { root = removeHelper(root, key); }
    bool search(const Key& key) const { return searchHelper(root, key); }
    int depth() const { return depthHelper(root); }
};

#endif  // INCLUDE_BST_H_
