#include <iostream>
#include "image.hpp"

int main() {
    cv::Mat img = termart::loadImage("examples/phodo.jpg");

    std::cout << "loaded "  << img.cols << "x" << img.rows << "\n";

    cv::Mat small = termart::resizeForAscii(img, 80);

    std::cout << "resized " << small.cols << "x" << small.rows << "\n";
}