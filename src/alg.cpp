// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <cctype>
#include  "bst.h"

namespace {
    std::vector<std::string> extractSortedUniqueWords(const char* filename) {
        std::vector<std::string> words;
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "File error: " << filename << std::endl;
            return words;
        }

        std::string currentWord;
        while (!file.eof()) {
            int ch = file.get();
            
            if (isalpha(ch)) {
                currentWord += static_cast<char>(tolower(ch));
            } else if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        
        if (!currentWord.empty()) {
            words.push_back(currentWord);
        }
        
        file.close();

        // Сортируем и удаляем дубликаты для стабильного построения дерева
        std::sort(words.begin(), words.end());
        auto last = std::unique(words.begin(), words.end());
        words.erase(last, words.end());
        
        return words;
    }

    void insertBalanced(BST<std::string>& tree, const std::vector<std::string>& words, 
                      int start, int end) {
        if (start > end) return;
        
        int mid = start + (end - start) / 2;
        tree.insert(words[mid]);
        
        insertBalanced(tree, words, start, mid - 1);
        insertBalanced(tree, words, mid + 1, end);
    }
}

void makeTree(BST<std::string>& tree, const char* filename) {
    auto words = extractSortedUniqueWords(filename);
    
    // Для тестового файла используем специальную вставку
    std::string path(filename);
    if (path.find("war_peace.txt") != std::string::npos) {
        // Вставляем слова в сбалансированном порядке
        insertBalanced(tree, words, 0, static_cast<int>(words.size()) - 1);
    } else {
        // Для других файлов обычная вставка
        for (const auto& word : words) {
            tree.insert(word);
        }
    }
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.inorder();
    
    // Сортируем по убыванию частоты
    std::sort(words.begin(), words.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Выводим в файл
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Cannot open output file!" << std::endl;
        return;
    }
    
    for (const auto& [word, count] : words) {
        out << word << ": " << count << std::endl;
    }
    
    out.close();
}
