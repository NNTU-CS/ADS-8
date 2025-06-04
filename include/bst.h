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
		node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
	};

	node* root;

	node* addNode(node* root, T value) {
		if (root == nullptr) {
			return new node(value);
		}
		if (value < root->key) {
			root->left = addNode(root->left, value);
		} else if (value > root->key) {
			root->right = addNode(root->right, value);
		} else {
			root->count++;
		}
		return root;
	}

	int depth(node* root) const {
		if (root == nullptr) {
			return 0;
		}
		int leftdepth = depth(root->left);
		int rightdepth = depth(root->right);
		return std::max(leftdepth, rightdepth) + 1;
	}

	node* search(node* root, const T& value) const {
		if (root == nullptr) {
			return 0;
		} else if (value < root->key) {
			return search(root->left, value);
		} else if (value > root->key) {
			return search(root->right, value);
		} else {
			return root;
		}
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
		return depth(root);
	}
	int depth() const {
		return depth(root);
	}
	bool search(const T& value) const {
		return search(root, value) != nullptr;
	}
	std::vector<std::pair<T, int>> Order() const {
		std::vector<std::pair<T, int>> result;
		inOrder(root, result);
		return result;
	}
};
