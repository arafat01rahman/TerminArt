#pragma once
#include <opencv2/opencv.hpp>
#include <string>

namespace termart {

std::string fgColor(int r, int g, int b);
std::string reset();

// Render an image as 24-bit ANSI colored ASCII text.
std::string renderAnsiTrueColor(const cv::Mat& bgr, const std::string& palette);

}