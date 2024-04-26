#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace parser {
enum tok {
   NOP = 0,
   SET,
   SHIFT_LEFT,
   SHIFT_RIGHT,
   ARITHMETIC_SHIFT_RIGHT,
   NOT,
   OR,
   AND,
   XOR,
   QUIT,
   ZERO,
   PREF_BASE,
   ADD,
   SUB,
   MUL,
   DIV,
};

static std::unordered_map<std::string, tok> str2tok_lookup = {
   {"set",SET},
   {"<<", SHIFT_LEFT},
   {">>", SHIFT_RIGHT},
   {">>>",ARITHMETIC_SHIFT_RIGHT},
   {"n",  NOT},
   {"|",  OR},
   {"&",  AND},
   {"^",  XOR},
   {"q",  QUIT},
   {"quit",QUIT},
   {"zero",ZERO},
   {"base",PREF_BASE},
   {"+", ADD},
   {"-", SUB},
   {"*", MUL},
   {"/", DIV},
};

static std::unordered_map<tok, bool> tok_onearg_lookup = {
   {NOP, true},
   {NOT, true},
   {QUIT, true},
   {ZERO, true},
};

using instr = std::pair<tok, std::string>;
std::vector<instr> parse(const std::string& list);
}
