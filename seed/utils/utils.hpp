#ifndef __UTILS
#define __UTILS

#include <vector>
#include <string>
#include <sdsl/suffix_trees.hpp>

void get_sa(std::string& word, std::vector<int>& res);

void get_lcp(std::string& word, std::vector<int>& sa, std::vector<int>& res);

void get_depths(std::string& word, sdsl::cst_sada<>& cst, std::vector<int>& res);

#endif