// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <fstream>


// Объявление дружественных функций
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    // 1. Создаем дерево
    BST<std::string> wordTree;

    // 2. Загружаем данные из файла
    const char* filename = "input.txt";
    makeTree(wordTree, filename);

    // 3. Выводим информацию о дереве
    std::cout << "Binary Search Tree Statistics:\n";
    std::cout << "----------------------------\n";
    std::cout << "Tree depth: " << wordTree.depth() << std::endl;

    // 4. Выводим частоту слов
    std::cout << "\nWord Frequencies (sorted by count):\n";
    std::cout << "---------------------------------\n";
    printFreq(wordTree);

    // 5. Дополнительная проверка (опционально)
    std::cout << "\nSpecific Word Checks:\n";
    std::cout << "the: " << wordTree.getCount("the") << " occurrences\n";
    std::cout << "war: " << wordTree.getCount("war") << " occurrences\n";
    std::cout << "peace: " << wordTree.getCount("peace") << " occurrences\n";

    return 0;
}
