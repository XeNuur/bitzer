#include <iostream>
#include "util.h"
#include "parser.h"
#define VERSION "v0.0.1"

uint32_t value = 0;
uint32_t pref_base = 10;

bool handle_inst(parser::instr _inst) {
   //std::cout << "INST: " << _inst.first << " ARG: " << _inst.second <<std::endl;
   const auto instr = _inst.first;
   uint32_t arg = 0;
   decoding_with_ending(arg, _inst.second);

   bool retsig = true;
   switch(instr) {
      case parser::SET:
         value = arg;
         break;
      case parser::SHIFT_LEFT:
         value = value << arg;
         break;
      case parser::SHIFT_RIGHT:
         value = value >> arg;
         break;
      case parser::ARITHMETIC_SHIFT_RIGHT:
         value = (int32_t)value >> (int32_t)arg;
         break;
      case parser::NOT:
         value = ~value;
         break;
      case parser::OR:
         value |= arg;
         break;
      case parser::AND:
         value &= arg;
         break;
      case parser::XOR:
         value ^= arg;
         break;
      case parser::QUIT: exit(0);
      case parser::ZERO:
         value = 0;
         break;
      case parser::PREF_BASE:
         pref_base = arg;
         break;
      case parser::ADD:
         value += arg; break;
      case parser::SUB:
         value -= arg; break;
      case parser::MUL:
         value *= arg; break;
      case parser::DIV:
         value /= arg; break;
      default:
         retsig = false;
   }
   return retsig;
}

int main() {
   std::cout << "Bitzer " VERSION " - bitwise operation for human-beings!\n";

   std::string input;
   for(;;) {
      std::cout << i2strnbase(value, pref_base) << " : ";
      std::getline(std::cin, input);

      auto instr_list = parser::parse(input);
      auto status = false;

      auto instr_idx = 0;
      for(auto& it: instr_list) {
         status = handle_inst(it);
         if (!status) {
            std::cout << "invalid command at index: " << instr_idx << std::endl;
            break;
         }
         instr_idx++;
      }
      if(!status) 
         continue;

      for(auto& it: g_bases) {
         std::cout << it << " - " << i2strnbase(value, it) << std::endl;
      }
      std::cout << std::endl;
   }
   return 0;
}

