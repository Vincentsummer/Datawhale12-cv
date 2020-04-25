//
// Created by vincent on 20-4-25.
//

#include "tColor.h"

void vincent::tColor(cv::Mat &src, cv::Mat &tar, int code)
{
    switch (code)
    {
        case CV_RGB2GREY : tar = RGB2Grey(src); break;
        case CV_RGB2HSV : tar = RGB2HSV(src); break;
        case CV_HSV2RGB : tar = HSV2RGB(src); break;
        default: break;
    }
}

cv::Mat vincent::RGB2Grey(cv::Mat src, bool accelerate)
{
    CV_Assert(src.channels() == 3);
    cv::Mat tar = cv::Mat::zeros(src.size(), CV_8UC1);
    cv::Vec3b rgb;

    for (int i = 0; i < tar.rows; ++i){
        for (int j = 0; j < tar.cols; ++j){
            rgb = src.at<cv::Vec3b>(i,j);
            uchar B = rgb[0], G = rgb[1], R = rgb[2];

            if (accelerate)
                tar.at<uchar>(i,j) = (uchar) ((B * 1868 + G * 9618 + R * 4898) >> 14);
            else
                tar.at<uchar>(i,j) = (uchar) (B * 0.114 + G * 0.587 + R * 0.299);
        }
    }
    return tar;
}

cv::Mat vincent::RGB2HSV(cv::Mat src)
{
    cv::Mat tar = cv::Mat::zeros(src.size(), CV_32FC3);
    cv::Vec3b rgb;
    float H = 0, S = 0, V = 0;
    for (int i = 0; i < tar.rows; ++i){
        for (int j = 0; j < tar.cols; ++j){
            rgb = src.at<cv::Vec3b>(i,j);
            float b = rgb[0] / 255.0, g = rgb[1] / 255.0, r = rgb[2] / 255.0;
            float Cmax = max(r, max(g, b)), Cmin = min(r, min(g, b)), delta = Cmax - Cmin;
            V = Cmax;
            S = Cmax == 0 ? 0 : delta / Cmax;
            if (Cmax == r) H = (g - b) / delta;
            else if (Cmax == g) H = (b - r) / delta + 2;
            else if (Cmax == b) H = (r - g) / delta + 4;
            H *= 60;
            if (H < 0) H += 360;

            tar.at<cv::Vec3f>(i,j)[0] = H;
            tar.at<cv::Vec3f>(i,j)[1] = S;
            tar.at<cv::Vec3f>(i,j)[2] = V;
        }
    }
    return tar;
}

cv::Mat vincent::HSV2RGB(cv::Mat src)
{
    cv::Mat tar = cv::Mat::zeros(src.size(), CV_8UC3);
    cv::Vec3f hsv;
    float r = 0, g = 0, b = 0;
    for (int i = 0; i < tar.rows; ++i){
        for (int j = 0; j < tar.cols; ++j){
            hsv = src.at<cv::Vec3f>(i,j);
            float h = hsv[0] / 60, s = hsv[1], v = hsv[2];
            int offset = (int) floor(h);
            float f = h - offset, p = v * (1 - s), q = v * (1 - f*s), t = v * (1-(1-f)*s);
            switch (offset){
                case 0: r = v; g = t; b = p; break;
                case 1: r = q; g = v; b = p; break;
                case 2: r = p; g = v; b = t; break;
                case 3: r = p; g = q; b = v; break;
                case 4: r = t; g = p; b = v; break;
                case 5: r = v; g = p; b = q; break;
                default: break;
            }

            tar.at<cv::Vec3b>(i,j)[0] = (uchar) (b * 255);
            tar.at<cv::Vec3b>(i,j)[1] = (uchar) (g * 255);
            tar.at<cv::Vec3b>(i,j)[2] = (uchar) (r * 255);
        }
    }
    return tar;
}