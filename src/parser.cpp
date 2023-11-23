#include "parser.h"
#include <sstream>

using output = std::vector<std::string>;

output _div_ch(const std::string& input, char div) {
   output out;
   auto marker = std::make_pair(0u, 0u);
   bool lockdown = false;

   for (size_t i=0; i<input.size(); ++i) {
      auto ch = input[i];
      if (ch == div) {
         if (lockdown) continue;
         out.push_back(input.substr(marker.first, marker.second - marker.first));
         lockdown = true;
         continue;
      }
      if (lockdown)
         marker = std::make_pair(i, i);
      lockdown = false;
      marker.second++;
   }

   out.push_back(input.substr(marker.first, marker.second - marker.first));
   return out;
}

namespace parser {

std::vector<instr> parse(const std::string& list) {
   std::vector<instr> out;
   const auto inst_list = _div_ch(list, ' ');

   instr current;
   bool sec_phase = false;
   for(auto& it: inst_list) {
      if (sec_phase) {
         current.second = it;
         sec_phase = false;

         out.push_back(current);
         continue;
      }
      current.first = str2tok_lookup[it];
      sec_phase = !tok_onearg_lookup[current.first];
      if(!sec_phase) out.push_back(current);
   }
   return out;
}

}

