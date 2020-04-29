//
// Created by vincent on 20-4-26.
//

#ifndef CV_04_FILTERTEST_H
#define CV_04_FILTERTEST_H

#include "../myCV/filter.h"

using namespace cv;

std::string lena = "../image/lena.jpg";

void filterTest()
{
    //载入图像
    Mat image = imread(lena);
    Mat dst1, dst2, dst3;
    //均值滤波
    blur(image, dst1, Size(7, 7));
    //方框滤波
    boxFilter(image, dst2, -1, Size(7, 7), Point(-1, -1), true, BORDER_CONSTANT);
    //高斯滤波
    GaussianBlur(image, dst3, Size(7, 7), 0.8);

    //创建窗口并显示
    namedWindow("均值滤波效果图");
    namedWindow("方框滤波效果图");
    namedWindow("高斯滤波效果图");
    imshow("均值滤波效果图", dst1);
    imshow("方框滤波效果图", dst2);
    imshow("高斯滤波效果图", dst3);
    waitKey(0);
}

void myBoxFilterTest()
{
    Mat image = imread(lena), tar;
    vincent::boxFilter(image, tar, Size(7,7), true);
    imshow("boxFilter", tar);
    waitKey(0);
}

#endif //CV_04_FILTERTEST_H
