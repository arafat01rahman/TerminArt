#include "ansi.hpp"
#include "render.hpp"

namespace termart {

std::string fgColor(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" +
           std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string reset() {
    return "\033[0m";
}

std::string renderAnsiTrueColor(const cv::Mat& bgr, const std::string& palette) {
    std::string out;
    out.reserve(bgr.rows * (bgr.cols * 20 + 5));

    for (int y = 0; y < bgr.rows; ++y) {
        int x = 0;
        while (x < bgr.cols) {
            cv::Vec3b p = bgr.at<cv::Vec3b>(y, x);
            char ch = pixelToChar(p, palette);
            std::string color = fgColor(p[2], p[1], p[0]);
            int x2 = x + 1;
            while (x2 < bgr.cols) {
                cv::Vec3b p2 = bgr.at<cv::Vec3b>(y, x2);
                if (pixelToChar(p2, palette) != ch ||
                    !(p2[2] == p[2] && p2[1] == p[1] && p2[0] == p[0]))
                    break;
                ++x2;
            }
            out += color;
            for (int xi = x; xi < x2; ++xi)
                out += ch;
            out += reset();
            x = x2;
        }
        out += '\n';
    }

    return out;
}

}