#include "cli.hpp"
#include <iostream>
#include <stdexcept>

namespace termart {

static std::string nextArg(int& i, int argc, char** argv, const char* flag) {
    if (i + 1 >= argc) {
        throw std::runtime_error(std::string(flag) + ": missing value");
    }
    return argv[++i];
}

Config parseArgs(int argc, char** argv) {
    Config cfg;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            cfg.showHelp = true;
            continue;
        }

        if (arg == "--width") {
            std::string val = nextArg(i, argc, argv, "--width");
            try {
                cfg.width = std::stoi(val);
            } catch (const std::exception&) {
                throw std::runtime_error("--width: invalid number '" + val + "'");
            }
            if (cfg.width < 1 || cfg.width > 500) {
                throw std::runtime_error("--width: must be 1..500");
            }
            continue;
        }

        if (arg == "--color") {
            std::string val = nextArg(i, argc, argv, "--color");
            if      (val == "truecolor") cfg.color = ColorMode::TrueColor;
            else if (val == "none")      cfg.color = ColorMode::None;
            else throw std::runtime_error("--color: expected truecolor|none, got '" + val + "'");
            continue;
        }

        if (arg == "--html") {
            cfg.toHtml = true;
            continue;
        }

        if (arg == "--output") {
            cfg.outputPath = nextArg(i, argc, argv, "--output");
            continue;
        }

        if (arg.rfind("--", 0) == 0) {
            throw std::runtime_error("unknown flag: " + arg);
        }

        cfg.inputPath = arg;
    }

    if (!cfg.showHelp && cfg.inputPath.empty()) {
        throw std::runtime_error("no input image");
    }
    if (cfg.toHtml && cfg.outputPath.empty()) {
        throw std::runtime_error("--html requires --output FILE");
    }

    return cfg;
}

void printUsage(const char* progName) {
    std::cout
        << "Usage: " << progName << " <image> [options]\n\n"
        << "Options:\n"
        << "  --width N            character columns (default 100)\n"
        << "  --color truecolor|none\n"
        << "  --html               write HTML instead of ANSI to stdout\n"
        << "  --output FILE        output file (required with --html)\n"
        << "  -h, --help           show this help\n";
}

}