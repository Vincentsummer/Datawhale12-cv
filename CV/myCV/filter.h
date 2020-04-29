//
// Created by vincent on 20-4-27.
//

#ifndef CV_FILTER_H
#define CV_FILTER_H

#include "mycv.h"

namespace vincent
{

    void boxU(cv::Mat& src, cv::Mat& tar, cv::Size ksize);
    void box3b(cv::Mat& src, cv::Mat& tar, cv::Size ksize);
    void boxFilter(cv::Mat& src, cv::Mat& tar, cv::Size ksize, bool normalize = true);

    void blur();
    void guassBlur();
} // namespace vincent

#endif //CV_FILTER_H
