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
        int x = 0;
        while (x < bgr.cols) {
            cv::Vec3b p = bgr.at<cv::Vec3b>(y, x);
            char ch = pixelToChar(p, palette);
            int r = (int)p[2], g = (int)p[1], b = (int)p[0];
            int x2 = x + 1;
            while (x2 < bgr.cols) {
                cv::Vec3b p2 = bgr.at<cv::Vec3b>(y, x2);
                if (pixelToChar(p2, palette) != ch ||
                    !(p2[2] == p[2] && p2[1] == p[1] && p2[0] == p[0]))
                    break;
                ++x2;
            }
            out += "<span style=\"color:rgb(";
            out += std::to_string(r);
            out += ",";
            out += std::to_string(g);
            out += ",";
            out += std::to_string(b);
            out += ")\">";
            for (int xi = x; xi < x2; ++xi)
                out += escapeChar(ch);
            out += "</span>";
            x = x2;
        }
        out += "\n";
    }

    out += kHtmlFoot;
    return out;
}

}