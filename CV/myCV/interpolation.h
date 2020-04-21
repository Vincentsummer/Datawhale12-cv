//
// Created by vincent on 20-4-20.
//

#ifndef CV_INTERPOLATION_H
#define CV_INTERPOLATION_H

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

namespace vincent
{
    enum Interpolation {
        INTER_NEAREST = 0,
        INTER_LINEAR = 1,
        SIZE = 2,
    };

    void test();

    // 图像缩放
    void resize(cv::Mat& src, cv::Mat& tar, float fx, float fy, int inter = INTER_LINEAR);

    template <typename T>
    class Impl
    {
    public:
        typedef T (*Fun)(cv::Mat&, float, float);

        Impl()
        {
            this->funs.emplace_back(inter_nearest);
            this->funs.emplace_back(inter_linear);
        }

        vector<Fun> getFuns() {return funs;}
    private:
        vector<Fun> funs;
        // 最近邻插值法
        static T inter_nearest(cv::Mat& src, float x, float y);

        // 双线性插值法
        static T inter_linear(cv::Mat& src, float x, float y);
    };

} // namespace vincent

#endif //CV_INTERPOLATION_H
