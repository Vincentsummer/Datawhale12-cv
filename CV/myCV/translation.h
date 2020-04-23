//
// Created by vincent on 20-4-22.
//

#ifndef CV_TRANSLATION_H
#define CV_TRANSLATION_H

#include <opencv2/opencv.hpp>

#include "interpolation.h"

using namespace cv;

namespace vincent
{
    enum OFFSET
    {
        HORIZONTAL  = 0,
        VERTICAL    = 1,
    };

    // 仿射变换
    void warpAffine(Mat& src, Mat& tar, Mat& M, Size dsize, int flags = LINEAR);

    Mat getRotationMat(Point2f center, double angle, double scale = 1.0);   // 旋转矩阵
    Mat getTransMat(float mx, float my);                                    // 平移矩阵
    Mat getOffsetMat(Point2f center, float m, int flags);                   // 偏移矩阵
    /**
     * 坐标变换矩阵
     * flag = 1 : 正变换， 图像坐标 -> 笛卡尔坐标
     * flag = -1 : 逆变换， 笛卡尔坐标 -> 图像坐标
     * **/
    Mat getCoordinateTransMat(Point2f center, int flag);

} // namesapace vincent

#endif //CV_TRANSLATION_H
