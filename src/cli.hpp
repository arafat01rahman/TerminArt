#pragma once
#include <string>

namespace termart {

enum class ColorMode { None, TrueColor };

struct Config {
    std::string inputPath;
    int         width    = 100;
    ColorMode   color    = ColorMode::TrueColor;
    bool        toHtml   = false;
    std::string outputPath;
    bool        showHelp = false;
};

Config parseArgs(int argc, char** argv);
void   printUsage(const char* progName);

}