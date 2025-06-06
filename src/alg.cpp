// Copyright 2022 NNTU-CS
#include <algorithm>
#include <iostream>
#include <vector>

#include "tree.h"

static void Backtrack(const std::vector<char>& elems,
                      std::vector<bool>& used,
                      std::vector<char>& current,
                      std::vector<std::vector<char>>& output) {
  if (current.size() == elems.size()) {
    output.push_back(current);
    return;
  }
  for (size_t i = 0; i < elems.size(); ++i) {
    if (used[i]) {
      continue;
    }
    used[i] = true;
    current.push_back(elems[i]);
    Backtrack(elems, used, current, output);
    current.pop_back();
    used[i] = false;
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> output;
  std::vector<char> current;
  std::vector<bool> used(tree.input.size(), false);
  Backtrack(tree.input, used, current, output);
  return output;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) {
    return {};
  }
  return all[num - 1];
}

size_t factorial(int n) {
  size_t result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  int n = static_cast<int>(tree.input.size());
  size_t total = factorial(n);
  if (num < 1 || num > static_cast<int>(total)) {
    return {};
  }
  std::vector<char> elems = tree.input;
  std::vector<char> result;
  int index = num - 1;
  size_t fact = factorial(n - 1);

  for (int i = n; i > 0; --i) {
    size_t pos = index / fact;
    result.push_back(elems[pos]);
    elems.erase(elems.begin() + pos);
    if (i - 1 > 0) {
      index %= fact;
      fact /= static_cast<size_t>(i - 1);
    }
  }

  return result;
}

PMTree::PMTree(const std::vector<char>& in) : input(in), root(nullptr) {}

PMTree::~PMTree() {}
