#pragma once
#include <opencv2/opencv.hpp>
#include <string>

namespace termart {

extern const std::string kPalette;

char pixelToChar(const cv::Vec3b& bgr, const std::string& palette);
std::string renderAscii(const cv::Mat& bgr, const std::string& palette);

}