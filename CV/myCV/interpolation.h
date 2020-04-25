//
// Created by vincent on 20-4-20.
//

#ifndef CV_INTERPOLATION_H
#define CV_INTERPOLATION_H

#include <iostream>
#include "utils.h"

using namespace std;

namespace vincent
{
    enum Interpolation {
        NEAREST = 0,
        LINEAR = 1,
    };

    // 图像缩放
    void resize(cv::Mat& src, cv::Mat& tar, float fx, float fy, int inter = LINEAR);

    template <typename T>
    class Impl
    {
    public:
        typedef T (*Fun)(cv::Mat&, float, float);

        Impl()
        {
            funs.emplace_back(inter_nearest);
            funs.emplace_back(inter_linear);
        }

        Fun operator [] (int i)
        {
            if (i < funs.size()) return funs[i];
            else throw "out of Interpolation!";
        }

    private:
        vector<Fun> funs;

        Impl& operator = (const Impl& i);
        Impl(const Impl&);

        // 最近邻插值法
        static T inter_nearest(cv::Mat& src, float x, float y);

        // 双线性插值法
        static T inter_linear(cv::Mat& src, float x, float y);
    };

    static Impl<uchar> interpolationCh1;
    static Impl<cv::Vec3b> interpolationCh3;
} // namespace vincent

#endif //CV_INTERPOLATION_H
