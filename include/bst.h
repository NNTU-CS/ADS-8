// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
template<typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(const T& key) : key(key), count(1), left(nullptr), right(nullptr) {}
};
template<typename T>
class BST {
private:
    Node<T>* root;
    void insert(Node<T>*& node, const T& key) {
      if (!node) {
        node = new Node<T>(key);
      } else if (key < node->key) {
        insert(node->left, key);
      } else if (key > node->key) {
        insert(node->right, key);
      } else {
        node->count++;
      }
    }
    int depth(Node<T>* node) const {
      if (!node) return 0;
      int left = depth(node->left);
      int right = depth(node->right);
      int maxDepth = (left > right) ? left : right;
      return maxDepth + 1;
    }
    Node<T>* search(Node<T>* node, const T& key) const {
      if (!node || node->key == key) return node;
      Node* nextNode = (key < node->key) ? node->left : node->right;
      return search(nextNode, key);
    }
    void inorder(Node<T>* node, void(*process)(const T&, int)) const {
      if (!node) return;
      inorder(node->left, process);
      process(node->key, node->count);
      inorder(node->right, process);
    }
    void destroy(Node<T>* node) {
      if (!node) return;
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }
    void insert(const T& key) { insert(root, key); }
    int depth() const { return depth(root); }
    bool search(const T& key) const { return search(root, key) != nullptr; }
    void traverse(void(*p)(const T&, int)) const {
      inorder(root, p);
    }
};
#endif  // INCLUDE_BST_H_
