// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template<typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* right;
    Node* left;
  };
  Node* root;

  Node* addNode(Node* root, T value) {
    if (root == nullptr) return new Node{value, 1, nullptr, nullptr};

    if (value > root->data) {
      root->right = addNode(root->right, value);
    } else if (value < root->data) {
      root->left = addNode(root->left, value);
    } else {
      root->count++;
    }
    return root;
  }

  Node* rmNode(Node* root, T value) {
    if (root == nullptr) return nullptr;
    Node* buff,buff2;
    if (value > root->data) {
      root->right = rmNode(root->right, value);
    } else if (value < root->data) {
      root->left = rmNode(root->left, value);
    } else {
      buff = root;
      if (root->right == nullptr) {
        root = root->left;
      } else if (root->left == nullptr) {
        root = root->right;
      } else {
        buff2 = root->right;
        if (buff2->left != nullptr) {
          while (buff2->left->left != nullptr) {
            buff2 = buff2->left;
          }
          root->data = buff2->left->data;
          root->count = buff2->left->count;
          buff = buff2->left;
          buff2 = buff2->left->right;
        } else {
          root->data = buff2->data;
          root->count = buff2->count;
          buff = buff2;
          root->right = root->right->right;
        }
      }
      delete buff;
    }
    return root;
  }

  void rmTree(Node* root) {
    if (root == nullptr) return;

    rmTree(root->right);
    rmTree(root->left);
    delete root;
    root = nullptr;
  }

  int searchNode(Node* root, T value) {
    if (root == nullptr) return 0;

    if (value > root->data) {
      return searchNode(root->right, value);
    } else if (value < root->data) {
      return searchNode(root->left, value);
    } else {
      return root->count;
    }
  }

  void printTree(Node* root) {
    if (root == nullptr) return;

    printTree(root->left);
    for (int i = 0; i < root->count; ++i) {
      std::cout << root->data << ' ';
    }
    printTree(root->right);
  }

  int getDepth(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 0;
    
    int left = getDepth(root->left);
    int right = getDepth(root->right);
    return std::max(left, right) + 1;
  }

  void getFreqs(Node* root, std::vector<std::pair<T, int>& freqs>) const {
    if (root == nullptr) return;

    getFreqs(root->left, freqs);
    freqs.push_back(std::make_pair(root->data, root->count));
    getFreqs(root->right, freqs);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    rmTree(root);
  }

  void add(T value) {
    root = addNode(root, value);
  }

  Node* del(T value) {
    return rmNode(root, value);
  }

  void clear() {
    rmTree(root);
  }

  int search(T value) {
    return searchNode(root, value);
  }

  void print() {
    printTree(root);
  }

  int depth() {
    return getDepth(root);
  }

  Node* getRoot() {
    return root;
  }

  std::vetor<std::pair<T, int>> getFreqs() const {
    std::vector<std::pair<T, int>> freqs;
    getFreqs(root, freqs);
    return freqs;
  }
};

#endif  // INCLUDE_BST_H_
