#ifndef __COMBINE
#define __COMBINE

#include "../structs/structs.hpp"
#include <vector>
#include <string>
#include <sdsl/suffix_trees.hpp>

void combine(std::string& word, std::vector<std::vector<Pack>>& packs, std::vector<Pack>& res);

void combine(sdsl::cst_sada<>& suf_tree, std::vector<int>& depths, std::vector<std::vector<Pack>>& packs, std::vector<Pack>& res);

#endif