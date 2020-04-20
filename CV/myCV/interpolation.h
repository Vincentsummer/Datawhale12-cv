//
// Created by vincent on 20-4-20.
//

#ifndef CV_INTERPOLATION_H
#define CV_INTERPOLATION_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

namespace vincent
{
    // 最近邻插值法
    void inter_nearest(cv::Mat& src, cv::Mat& tar, float fx, float fy);

    // 双线性插值法
    template <typename T>
    T get_scale_value(cv::Mat& src, float x, float y);
    void inter_linear(cv::Mat& src, cv::Mat& tar, float fx, float fy);

} // namespace vincent

#endif //CV_INTERPOLATION_H
