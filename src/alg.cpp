// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  // поместите сюда свой код
}
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>

void makeTree(BST<std::string>& tree, const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "File error!" << std::endl;
		return;
	}

	std::string current;
	while (!file.eof()) {
		char ch = file.get();
		if (ch >= 'A' && ch <= 'Z')
			ch += 'a' - 'A';
		if (ch >= 'a' && ch <= 'z') {
			current += ch;
		} else {
			if (!current.empty()) {
				tree.insert(current);
			}
			current.clear();
		}
	}
	file.close();
}

void printFreq(const BST<std::string>& tree) {
	std::vector<std::pair<std::string, int>> word = tree.Order();
	std::sort(word.begin(), word.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; });
	std::ofstream file("result/freq.txt");
	if (!file.is_open()) {
		std::cerr << "File is not open" << std::endl;
		return;
	}
	for (const auto& pair : word) {
		std::cout << pair.first << "-" << pair.second << '\n';
		file << pair.first << '-' << pair.second << '\n';
	}
	file.close();
}
