// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>
#include <vector>
#include <stack>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
	int count;
	Node* left;
	Node* right;
	Node(const T& value): count(1), left(nullptr), right(nullptr), value(value){}
    };
    Node* root;
    Node* addNode(Node*, T);
    void delTree(Node*);
    void collectNodes(Node*, std::vector<std::pair<T, int>>&) const;
 public:
    BST();
    ~BST();
    void add(const T&);
    int depth(TreeNode* node) const;
    bool search(const T& value) const;
    std::vector<std::pair<T, int>> getWordsWithCounts() const;
};

template<typename T>
BST<T>::BST() :root(nullptr) {}

template<typename T>
BST<T>::~BST() {
    if (root)
        delTree(root);
}

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
    if (root == nullptr) {
	return new Node(value);
    } else if (value == root->value) {
	root->count++;
    } else if (value < root->value) {
	root->left = addNode(root->left, value);
    } else {
	root->right = addNode(root->right, value);
    }
    return root;
}

template<typename T>
void BST<T>::add(const T& value) {
    root = addNode(root, value);
}

template<typename T>
void BST<T>::delTree(Node* root) {
    if (root == nullptr) {
	return;
    } else {
	delTree(root->left);
	delTree(root->right);
	delete root;
    }
}
template<typename T>
void BST<T>::clear() {
    if (root) {
	delTree(root);
	root = nullptr;
    }
}

template<typename T>
int BST<T>::depth(Node* root) const {
    if (root == nullptr) {
	return 0;
    }
    return 1 + max(depth(root->left), depth(root->right));
}

template<typename T>
bool BST<T>::search(const T& value) const {
    Node* current = root;
    while (current != nullptr) {
        if (value == current->value) {
	    return true;
	} else if (value < current->value) {
	    current = current->left;
	} else {
	    current = current->right;
	}
    }
    return false;
}

template<typename T>
std::vector<std::pair<T, int>> BST<T>::getWordsWithCounts() const {
    std::vector<std::pair<T, int>> result;
    collectNodes(root, result);
    return result;
}

template<typename T>
void BST<T>::collectNodes(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node == nullptr) return;
    collectNodes(node->left, result);
    result.emplace_back(node->value, node->count);
    collectNodes(node->right, result);
}

#endif  // INCLUDE_BST_H_

