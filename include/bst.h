#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <string>

template <typename T>
class BST {
 private:
  struct TreeNode {
    T dataValue;
    int occurrenceCount;
    TreeNode* leftChild;
    TreeNode* rightChild;
    explicit TreeNode(const T& val)
        : dataValue(val), occurrenceCount(1),
          leftChild(nullptr), rightChild(nullptr) {}
  };

  TreeNode* rootNode = nullptr;

  TreeNode* addNode(TreeNode* currentNode, const T& keyData) {
    if (!currentNode) {
      return new TreeNode(keyData);
    }
    if (keyData == currentNode->dataValue) {
      currentNode->occurrenceCount++;
      return currentNode;
    }
    if (keyData < currentNode->dataValue) {
      currentNode->leftChild = addNode(currentNode->leftChild, keyData);
    } else {
      currentNode->rightChild = addNode(currentNode->rightChild, keyData);
    }
    return currentNode;
  }

  int computeDepth(TreeNode* nodePtr) const {
    if (!nodePtr) {
      return -1;
    }
    int leftDepth = computeDepth(nodePtr->leftChild);
    int rightDepth = computeDepth(nodePtr->rightChild);
    return std::max(leftDepth, rightDepth) + 1;
  }

  TreeNode* findNode(TreeNode* nodePtr, const T& keyData) const {
    if (!nodePtr || nodePtr->dataValue == keyData) {
      return nodePtr;
    }
    if (keyData < nodePtr->dataValue) {
      return findNode(nodePtr->leftChild, keyData);
    }
    return findNode(nodePtr->rightChild, keyData);
  }

  void traverseInOrder(TreeNode* nodePtr, std::vector<std::pair<T, int>>& result) const {
    if (!nodePtr) return;
    traverseInOrder(nodePtr->leftChild, result);
    result.push_back({nodePtr->dataValue, nodePtr->occurrenceCount});
    traverseInOrder(nodePtr->rightChild, result);
  }

  void deleteTree(TreeNode* nodePtr) {
    if (!nodePtr) return;
    deleteTree(nodePtr->leftChild);
    deleteTree(nodePtr->rightChild);
    delete nodePtr;
  }

 public:
  BST() = default;
  ~BST() { deleteTree(rootNode); }

  void insert(const T& keyData) {
    rootNode = addNode(rootNode, keyData);
  }

  int depth() const {
    return computeDepth(rootNode);
  }

  int search(const T& keyData) const {
    TreeNode* found = findNode(rootNode, keyData);
    return found ? found->occurrenceCount : 0;
  }

  void printSortedByFrequency(std::ostream& output = std::cout) const {
    std::vector<std::pair<T, int>> result;
    traverseInOrder(rootNode, result);
    
    std::sort(result.begin(), result.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
      return a.second > b.second;
    });

    for (const auto& pair : result) {
      output << pair.first << ": " << pair.second << std::endl;
    }
  }
};

#endif  // INCLUDE_BST_H_
