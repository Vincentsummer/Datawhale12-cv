//
// Created by vincent on 20-4-24.
//

#ifndef CV_COLORTEST_H
#define CV_COLORTEST_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../myCV/tColor.h"

using namespace std;
using namespace cv;

const static string lena = "../image/lena.jpg";

void colorTest()
{
    // Load image
    Mat src = imread(lena), img_rgb2hsv, img_hsv2rgb, img_rgb2grey;

//    cvtColor(src, img_rgb2hsv, COLOR_BGR2HSV);          // RGB2HSV
//    cvtColor(img_rgb2hsv, img_hsv2rgb, COLOR_HSV2BGR);  // HSV2RGB
//    cvtColor(src, img_rgb2grey, COLOR_BGR2GRAY);        // RGB2GREY

    vincent::tColor(src, img_rgb2hsv, vincent::CV_RGB2HSV); // RGB2HSV
    vincent::tColor(img_rgb2hsv, img_hsv2rgb, vincent::CV_HSV2RGB); // HSV2RGB
    vincent::tColor(src, img_rgb2grey, vincent::CV_RGB2GREY); // RGB2Grey

//    imwrite("../image/lena_rgb2hsv.jpg", img_rgb2hsv);
//    imwrite("../image/lena_rgb2grey.jpg", img_rgb2grey);

    imshow("RGB2HSV Space", img_rgb2hsv);
    imshow("HSV2RGB Space", img_hsv2rgb);
    imshow("RGB2Gray Scale", img_rgb2grey);

    waitKey();
}

#endif //CV_COLORTEST_H
