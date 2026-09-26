#include "image.hpp"
#include <stdexcept>
#include <cmath>

namespace termart
{

    cv::Mat loadImage(const std::string &path)
    {
        cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
        if (img.empty())
        {
            throw std::runtime_error("Failed to load " + path);
        }
        return img;
    }

    cv::Mat resizeForAscii(const cv::Mat &src, int cols, double rowScale)
    {
        if (cols <= 0)
        {
            throw std::runtime_error("Failed resizing");
        }

        int rows = std::round(cols * (src.rows / (double)src.cols) * rowScale);

        if (rows <= 0)
        {
            throw std::runtime_error("Failed resizing rows(<=0)");
        }

        cv::Mat dst;
        cv::resize(src, dst, cv::Size(cols, rows), 0, 0, cv::INTER_LINEAR);
        return dst;
    }

}