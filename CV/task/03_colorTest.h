//
// Created by vincent on 20-4-24.
//

#ifndef CV_COLORTEST_H
#define CV_COLORTEST_H


#include "utils.h"
#include "../myCV/tColor.h"
#include <iostream>

using namespace cv;

extern string lena;

void colorTest()
{
    // Load image
    Mat src = imread(lena), img_rgb2hsv, img_hsv2rgb, img_rgb2gray;

//    cvtColor(src, img_rgb2hsv, COLOR_BGR2HSV);          // RGB2HSV
//    cvtColor(img_rgb2hsv, img_hsv2rgb, COLOR_HSV2BGR);  // HSV2RGB
//    cvtColor(src, img_rgb2grey, COLOR_BGR2GRAY);        // RGB2GREY

    vincent::tColor(src, img_rgb2hsv, vincent::CV_RGB2HSV);         // RGB2HSV
    vincent::tColor(img_rgb2hsv, img_hsv2rgb, vincent::CV_HSV2RGB); // HSV2RGB
    vincent::tColor(src, img_rgb2gray, vincent::CV_RGB2GRAY);       // RGB2Grey

//    imwrite("../image/lena_rgb2hsv.jpg", img_rgb2hsv);
//    imwrite("../image/lena_rgb2grey.jpg", img_rgb2grey);

    imshow("RGB2HSV Space", img_rgb2hsv);
    imshow("HSV2RGB Space", img_hsv2rgb);
    imshow("RGB2Gray Scale", img_rgb2gray);

    waitKey();
}

void myRGB2GrayTest()
{
    Mat src = imread(lena);
    CV_Assert(!src.empty());

    Mat tar1, tar2;

    // OpenCV自带
    double t1 = getTickCount(); // 测时间
    cvtColor(src, tar1, COLOR_RGB2GRAY);
    t1 = getTickCount() - t1;
    double time1 = (t1 * 1000.) / (getTickFrequency());
    std::cout << "Opencv_rgb2gray=" << time1 << " ms. " << std::endl << std::endl;

    // RGB2Gray
    double t2 = (double)cv::getTickCount(); // 测时间
    vincent::tColor(src, tar2, vincent::CV_RGB2GRAY_ACC);
    t2 = (double)cv::getTickCount() - t2;
    double time2 = (t2 *1000.) / ((double)cv::getTickFrequency());
    std::cout << "My_rgb2gray=" << time2 << " ms. " << std::endl << std::endl;


    cv::namedWindow("src", WINDOW_NORMAL);
    imshow("src", src);
    cv::namedWindow("My_rgb2gray", WINDOW_NORMAL);
    imshow("My_rgb2gray", tar1);
    cv::namedWindow("Opencv_rgb2gray", WINDOW_NORMAL);
    imshow("Opencv_rgb2gray", tar2);
    cv::waitKey(0);
}

void myRGB_HSV()
{
    Mat src = imread(lena);
    CV_Assert(!src.empty());
    Mat tar1, tar2, tar3;

    //opencv自带
    cv::cvtColor(src, tar1, COLOR_RGB2HSV);              // RGB2HSV

    // RGB2HSV
    vincent::tColor(src, tar2, vincent::CV_RGB2HSV);     // RGB2HSV
    vincent::tColor(tar2, tar3, vincent::CV_HSV2RGB);    // HSV2BGR

    cv::namedWindow("src", WINDOW_NORMAL);
    imshow("src", src);
    cv::namedWindow("My_RGB2HSV", WINDOW_NORMAL);
    imshow("My_RGB2HSV", tar2);
    cv::namedWindow("My_HSV2RGB", WINDOW_NORMAL);
    imshow("My_HSV2RGB", tar3);
    cv::namedWindow("Opencv_RGB2HSV", WINDOW_NORMAL);
    imshow("Opencv_RGB2HSV", tar1);
    cv::waitKey(0);
}

#endif //CV_COLORTEST_H
