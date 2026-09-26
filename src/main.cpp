#include <iostream>
#include <fstream>
#include <stdexcept>

#include "cli.hpp"
#include "image.hpp"
#include "render.hpp"
#include "ansi.hpp"
#include "html.hpp"

int main(int argc, char** argv) {
    try {
        termart::Config cfg = termart::parseArgs(argc, argv);

        if (cfg.showHelp) {
            termart::printUsage(argv[0]);
            return 0;
        }

        cv::Mat img   = termart::loadImage(cfg.inputPath);
        cv::Mat small = termart::resizeForAscii(img, cfg.width);

        if (cfg.toHtml) {
            std::string html = termart::renderHtml(small, termart::kPalette);
            std::ofstream out(cfg.outputPath, std::ios::binary);
            if (!out) {
                throw std::runtime_error("cannot write: " + cfg.outputPath);
            }
            out << html;
        } else if (cfg.color == termart::ColorMode::TrueColor) {
            std::cout << termart::renderAnsiTrueColor(small, termart::kPalette);
        } else {
            std::cout << termart::renderAscii(small, termart::kPalette);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}