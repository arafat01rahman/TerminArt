#pragma once
#include <opencv2/opencv.hpp>
#include <string>

namespace termart {
    cv::Mat loadImage(const std::string& path);
    cv::Mat resizeForAscii(const cv::Mat &src,int cols,double rowScale = 0.45);
}