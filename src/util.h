#pragma once
#include <cstdint>
#include <string>
#include <vector>

const std::vector<uint32_t> g_bases = { 2, 8, 10, 16 };

const std::vector<std::pair<char, uint32_t>> g_decoding_scheme = {
   std::make_pair('b', 2),
   std::make_pair('o', 8),
   std::make_pair(' ', 10),
   std::make_pair('x', 16),
};

std::string i2strnbase(uint32_t value, uint32_t base);
int strnbase2i(std::string value, uint32_t base);

bool decoding_with_ending(uint64_t& num, std::string input);

