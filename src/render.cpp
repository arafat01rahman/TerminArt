#include "render.hpp"
#include "cli.hpp"

namespace termart {

const std::string kPalette = " .:-=+*#%@";

char pixelToChar(const cv::Vec3b& bgr, const std::string& palette) {
    int b = bgr[0];
    int g = bgr[1];
    int r = bgr[2];

    double lum = 0.2126 * r + 0.7152 * g + 0.0722 * b;

    int idx = (int)(lum / 255.0 * (palette.size() - 1));

    if (idx < 0) idx = 0;
    if (idx >= (int)palette.size()) idx = (int)palette.size() - 1;

    return palette[idx];
}

std::string renderAscii(const cv::Mat& bgr, const std::string& palette) {
    std::string out;
    out.reserve(bgr.rows * (bgr.cols + 1));

    for (int y = 0; y < bgr.rows; ++y) {
        for (int x = 0; x < bgr.cols; ++x) {
            out += pixelToChar(bgr.at<cv::Vec3b>(y, x), palette);
        }
        out += '\n';
    }

    return out;
}

}