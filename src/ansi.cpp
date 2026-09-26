#include "ansi.hpp"

namespace termart {

std::string fgColor(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" +
           std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string reset() {
    return "\033[0m";
}

}