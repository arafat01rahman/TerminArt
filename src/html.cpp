#include "html.hpp"
#include "render.hpp"

namespace termart {

static const char* kHtmlHead = R"HTML(<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>termart</title>
<style>
  html, body {
    margin: 0; padding: 0;
    background: #000;
    min-height: 100vh;
    display: flex; align-items: center; justify-content: center;
  }
  pre {
    font-family: "DejaVu Sans Mono", "Courier New", monospace;
    font-size: 8px;
    line-height: 1.0;
    letter-spacing: 0;
    margin: 0;
    white-space: pre;
  }
</style>
</head>
<body><pre>
)HTML";

static const char* kHtmlFoot = "</pre></body></html>\n";

static std::string escapeChar(char c) {
    if (c == '<')  return "&lt;";
    if (c == '>')  return "&gt;";
    if (c == '&')  return "&amp;";
    return std::string(1, c);
}

std::string renderHtml(const cv::Mat& bgr, const std::string& palette) {
    std::string out;
    out.reserve(bgr.rows * bgr.cols * 60);
    out += kHtmlHead;

    for (int y = 0; y < bgr.rows; ++y) {
        for (int x = 0; x < bgr.cols; ++x) {
            cv::Vec3b p = bgr.at<cv::Vec3b>(y, x);
            char ch = pixelToChar(p, palette);

            out += "<span style=\"color:rgb(";
            out += std::to_string((int)p[2]);  // R
            out += ",";
            out += std::to_string((int)p[1]);  // G
            out += ",";
            out += std::to_string((int)p[0]);  // B
            out += ")\">";
            out += escapeChar(ch);
            out += "</span>";
        }
        out += "\n";
    }

    out += kHtmlFoot;
    return out;
}

}