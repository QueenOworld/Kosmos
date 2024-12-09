#include "tui.hpp"
#include <cstdint>
#include <string>

inline std::string repeat(uint32_t num, const std::string &input) {
    std::string ret;
    ret.reserve(input.size() * num);
    for (int8_t index = 31; index >= 0; index--)
        if (num >> index) {
            ret += ret;
            if ((num >> index) % 2) {
                ret += input;
            }
        }
    return ret;
}
