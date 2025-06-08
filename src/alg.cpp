// Copyright 2021 NNTU-CS
#include "bst.h"

#include <cctype>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

static void EnsureParentDirectoryExists(const std::string& out_path) {
  std::size_t pos = out_path.find_last_of("/\\");
  if (pos == std::string::npos) return;
  std::string dir = out_path.substr(0, pos);
#ifdef _WIN32
  if (_mkdir(dir.c_str()) != 0 && errno != EEXIST) {
    std::perror("mkdir");
  }
#else
  if (mkdir(dir.c_str(), 0755) != 0 && errno != EEXIST) {
    std::perror("mkdir");
  }
#endif
}

static void WriteFreqToFile(
    const std::vector<std::pair<std::string, int>>& data,
    const std::string& out_path) {
  EnsureParentDirectoryExists(out_path);
  std::ofstream out(out_path);
  if (!out) {
    std::cerr << "Failed to open '" << out_path << "' for writing.\n";
    return;
  }
  for (const auto& p : data) {
    out << p.first << ": " << p.second << '\n';
  }
}

void makeTree(BST<std::string>& tree, const char* filename) {
  if (!filename) {
    std::cerr << "Filename is null.\n";
    return;
  }
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error: cannot open '" << filename << "'.\n";
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word.push_back(
          static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  words.reserve(32768);

  tree.inOrder([&words](const std::string& k, int c) {
    words.emplace_back(k, c);
  });

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              if (a.second != b.second) return a.second > b.second;
              return a.first < b.first;
            });

  for (const auto& p : words) {
    std::cout << p.first << ": " << p.second << '\n';
  }

  WriteFreqToFile(words, "src/freq.txt");
}
