// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include "bst.h"
#include "alg.cpp"

int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";

    // Создаем дерево с словами из файла
    makeTree(tree, filename);

    // Выводим частотный анализ
    std::cout << "Word frequency analysis:\n";
    tree.printFreq();

    // Печатаем результаты в файл
    printFreq(tree);

    // Выводим глубину дерева
    std::cout << "\nTree depth: " << tree.depth() << std::endl;

    return 0;
}
