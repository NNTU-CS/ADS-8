// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
class BST {
private:
    struct TreeNode {
        T dataValue;
        int occurrenceCount;
        TreeNode* leftChild;
        TreeNode* rightChild;
        TreeNode(T val) : dataValue(val), occurrenceCount(1), 
                          leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* rootNode;

    TreeNode* addNode(TreeNode* currentNode, T keyData) {
        if (!currentNode) 
            return new TreeNode(keyData);
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

    int computeDepth(TreeNode* nodePtr) {
        if (!nodePtr) 
            return 0;
        int leftSubtreeDepth = computeDepth(nodePtr->leftChild);
        int rightSubtreeDepth = computeDepth(nodePtr->rightChild);
        return std::max(leftSubtreeDepth, rightSubtreeDepth) + 1;
    }

    TreeNode* findNode(TreeNode* nodePtr, T keyData) {
        if (!nodePtr || nodePtr->dataValue == keyData) 
            return nodePtr;
        if (keyData < nodePtr->dataValue) 
            return findNode(nodePtr->leftChild, keyData);
        return findNode(nodePtr->rightChild, keyData);
    }

    void traverseInOrder(TreeNode* nodePtr, std::ostream& outputStream) {
        if (!nodePtr) 
            return;
        traverseInOrder(nodePtr->leftChild, outputStream);
        outputStream << nodePtr->dataValue << ": " 
                     << nodePtr->occurrenceCount << std::endl;
        traverseInOrder(nodePtr->rightChild, outputStream);
    }

    void traverseReverseOrder(TreeNode* nodePtr, std::ostream& outputStream) {
        if (!nodePtr) 
            return;
        traverseReverseOrder(nodePtr->rightChild, outputStream);
        outputStream << nodePtr->dataValue << ": " 
                     << nodePtr->occurrenceCount << std::endl;
        traverseReverseOrder(nodePtr->leftChild, outputStream);
    }

    void deleteTree(TreeNode* nodePtr) {
        if (!nodePtr) 
            return;
        deleteTree(nodePtr->leftChild);
        deleteTree(nodePtr->rightChild);
        delete nodePtr;
    }

public:
    BST() : rootNode(nullptr) {}
    ~BST() { deleteTree(rootNode); }

    void insert(T keyData) {
        rootNode = addNode(rootNode, keyData);
    }

    int depth() {
        return computeDepth(rootNode);
    }

    bool search(T keyData) {
        return findNode(rootNode, keyData) != nullptr;
    }

    void printInOrder(std::ostream& outputStream = std::cout) {
        traverseInOrder(rootNode, outputStream);
    }

    void printReverseInOrder(std::ostream& outputStream = std::cout) {
        traverseReverseOrder(rootNode, outputStream);
    }
};

#endif  // INCLUDE_BST_H_
