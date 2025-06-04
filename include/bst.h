// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
using namespace std;
template <typename T>
class BST {
private:
	struct node
	{
		T key;
		int count;
		node* left;
		node* right;
		explicit node(const T& value) : key(value), count(1), left(nullptr), right(nullptr) {}
	};

	node* root;

	node* addNode(node* root, const T& value) {
		if (root == nullptr) {
			return new node(value);
		}
		if (value == root->key) {
			++root->count;
			return root;
		}
		if (value < root->key) {
			root->left = addNode(root->left, value);
		} else {
			root->right = addNode(root->right, value);
		}
		return root;
	}

	int depthGet(node* root) const {
		if (root == nullptr) {
			return 0;
		}
		int leftdepth = depthGet(root->left);
		int rightdepth = depthGet(root->right);
		return (leftdepth >= rightdepth ? leftdepth : rightdepth) + 1;
	}

	const node* searchNode(const node* root, const T& value) const {
		if (root == nullptr) {
			return 0;
		} else if (value < root->key) {
			return searchNode(root->left, value);
		} else if (value > root->key) {
			return searchNode(root->right, value);
		} 
		return root;
	}
	
	void inOrder(node* root, std::vector<std::pair<T, int>>& result) const {
		if (root == nullptr)
			return;
		inOrder(root->left, result);
		result.push_back({ root->key, root->count });
		inOrder(root->right, result);
	}

	void clear(node* root) {
		if (root == nullptr)
			return;
		clear(root->left);
		clear(root->right);
		delete root;
	}
	
public:
	BST() : root(nullptr) {}
	~BST() { clear(root); }

	void insert(T value) {
		root = addNode(root, value);
	}
	int depth() const {
		return depthGet(root);
	}
	bool search(const T& value) const {
		return searchNode(root, value) != nullptr;
	}
	std::vector<std::pair<T, int>> Order() const {
		std::vector<std::pair<T, int>> result;
		inOrder(root, result);
		return result;
	}
};
#endif  // INCLUDE_BST_H_
