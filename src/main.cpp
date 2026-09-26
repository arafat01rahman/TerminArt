#include <iostream>
#include "cli.hpp"
#include "image.hpp"
#include "render.hpp"

int main(int argc, char** argv) {
    try {
        termart::Config cfg = termart::parseArgs(argc, argv);
        if (cfg.showHelp) {
            termart::printUsage(argv[0]);
            return 0;
        }

        cv::Mat img   = termart::loadImage(cfg.inputPath);
        cv::Mat small = termart::resizeForAscii(img, cfg.width);

        std::string art = termart::renderAscii(small, termart::kPalette);
        std::cout << art;
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
}