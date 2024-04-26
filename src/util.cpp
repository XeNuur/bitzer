#include "util.h"
#include <string>
#include <cctype>

char i2c(uint32_t num) {
   if (num >= 0 && num <= 9)
      return (char)(num + '0');
   return std::toupper((char)(num - 10 + 'A'));
}

uint32_t c2i(char c) {
   c = std::toupper(c);
   if (c >= '0' && c <= '9')
      return (int)c - '0';
   return (int)c - 'A' + 10;
}

std::string i2strnbase(uint32_t value, uint32_t base) {
   std::string out;
   for(;;) {
      auto val = value % base;
      out = i2c(val) + out;

      value /= base;
      if (value == 0)
         break;
   }
   return out;
}

int strnbase2i(std::string value, uint32_t base) {
   int out = 0;
   for(char& c: value) {
      auto val = c2i(c);
      if (!out) { 
         out = val; 
         continue;
      }
      out = out * base + val;
   }
   return out;
}

bool decoding_with_ending(uint64_t& num, std::string input) { 
   if(input.empty())
      return false;
   
   bool status = false;
   if (input.front() == '0' && input.size() > 1)
      input.erase(input.begin());

   for(auto& it: g_decoding_scheme) {
      if (input.front() != it.first)
         continue;

      input.erase(input.begin());
      num = strnbase2i(input, it.second);

      status = true;
      break;
   }
   
   if(!status) 
      num = std::stoi(input);
   return status;
}

