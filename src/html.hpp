#pragma once
#include <opencv2/opencv.hpp>
#include <string>

namespace termart {

std::string renderHtml(const cv::Mat& bgr, const std::string& palette);

}