//
// Created by vincent on 20-4-25.
//

#ifndef CV_TCOLOR_H
#define CV_TCOLOR_H

#include "mycv.h"

using namespace std;

namespace vincent
{
    enum ColorConversionCodes {
        CV_RGB2GRAY         = 0,
        CV_RGB2GRAY_ACC     = 1,
        CV_RGB2HSV          = 2,
        CV_HSV2RGB          = 3,
    };

    void tColor(cv::Mat& src, cv::Mat& tar, int code);

    cv::Mat RGB2Gray(cv::Mat src, bool accelerate = false);
    cv::Mat RGB2HSV(cv::Mat src);
    cv::Mat HSV2RGB(cv::Mat src);

} // namespace vincent

#endif //CV_TCOLOR_H
