// Copyright 2025 NNTU-CS
#include <gtest/gtest.h>
#include <string>

#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename);

TEST(lab8, test1_1) {
    const char* filename = "/home/runner/work/ADS-8/ADS-8/build/test/war_peace.txt";
    BST<std::string> tree;
    makeTree(tree, filename);

    int height = tree.height();
    EXPECT_EQ(height, 36);
}
TEST(lab8, test1_2) {
    const char* filename = "/home/runner/work/ADS-8/ADS-8/build/test/war_peace.txt";
    BST<std::string> tree;
    makeTree(tree, filename);
    int count = tree.search("pierre");
    EXPECT_EQ(count, 1955);
}
TEST(lab8, test1_3) {
    const char* filename = "/home/runner/work/ADS-8/ADS-8/build/test/war_peace.txt";
    BST<std::string> tree;
    makeTree(tree, filename);
    int count = tree.search("natasha");
    EXPECT_EQ(count, 1201);
}
TEST(lab8, test1_4) {
    const char* filename = "/home/runner/work/ADS-8/ADS-8/build/test/war_peace.txt";
    BST<std::string> tree;
    makeTree(tree, filename);
    int count = tree.search("andrew");
    EXPECT_EQ(count, 1142);
}
