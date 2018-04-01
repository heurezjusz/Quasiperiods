#ifndef __COMBINE
#define __COMBINE

#include "../structs/structs.hpp"
#include <vector>
#include <string>

void combine(std::string& word, std::vector<std::vector<Pack>>& packs, std::vector<Pack>& res);

void combine(int suf_tree, std::vector<int>& depths, std::vector<std::vector<Pack>>& packs, std::vector<Pack>& res);

#endif