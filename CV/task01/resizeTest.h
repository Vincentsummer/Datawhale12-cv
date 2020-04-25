//
// Created by vincent on 20-4-20.
//

/**
 * OpenCV 图像缩放
 * **/

#ifndef CV_VRESIZE_H
#define CV_VRESIZE_H

#include <opencv2/opencv.hpp>
#include <iostream>

#include "../myCV/interpolation.h"

using namespace cv;
using namespace std;

const static string yuner = "../image/yuner.jpg";

int resizeTest()
{
    Mat img = imread(yuner);
    if (img.empty()){
        cout << "无法读取图像" << endl;
        return 0;
    }

    int height = img.rows;
    int wight = img.cols;

    // 缩小图像，比例为(0.2, 0.2)
    float alpha = 0.4;
    Size dsize = Size(round(alpha * wight), round(alpha * height));
    Mat shrink;
    // 使用双线性插值
    resize(img, shrink, dsize, 0, 0, InterpolationFlags::INTER_LINEAR);

    // 在缩小图像的基础上，放大图像，比例为(1.5， 1.5)
    float fx = 1.5;
    float fy = 1.5;
    Mat enlarge1, enlarge2;
//    resize(shrink, enlarge1, Size(), fx, fy, InterpolationFlags::INTER_NEAREST);
    vincent::resize(shrink, enlarge1, fx, fy, vincent::Interpolation::NEAREST);
//    resize(shrink, enlarge2, Size(), fx, fy, InterpolationFlags::INTER_LINEAR);
    vincent::resize(shrink, enlarge2, fx, fy, vincent::Interpolation::LINEAR);

//    imwrite("../image/yuner_shrink.jpg", shrink);
//    imwrite("../image/yuner_INTER_NEAREST.jpg", enlarge1);
//    imwrite("../image/yuner_INTER_LINEAR.jpg", enlarge2);

    // 显示
//    imshow("src", img);
    imshow("shrink", shrink);
    imshow("INTER_NEAREST", enlarge1);
    imshow("INTER_LINEAR", enlarge2);
    waitKey(0);
    return 0;
}

#endif //CV_VRESIZE_H
