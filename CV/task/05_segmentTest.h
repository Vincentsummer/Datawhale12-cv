//
// Created by vincent on 20-4-29.
//

#ifndef CV_05_SEGMENT_H
#define CV_05_SEGMENT_H

#include "utils.h"

using namespace cv;
using namespace std;

extern string lena;

void otsuTest()
{
    Mat src = imread(lena), gray, dst;
    CV_Assert(!src.empty());
    cvtColor(src, gray, COLOR_BGR2GRAY);

    threshold(gray, dst, 0, 255, THRESH_OTSU);

    imshow("src", src);
    imshow("gray", gray);
    imshow("dst", dst);
    waitKey(0);
}

void adaptiveThresholdTest()
{
    Mat src = imread(lena), gray, dst;
    CV_Assert(!src.empty());
    cvtColor(src, gray, COLOR_BGR2GRAY);

    cv::adaptiveThreshold(gray, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 10);

    imshow("src", src);
    imshow("gray", gray);
    imshow("dst", dst);
    waitKey(0);
}

#endif //CV_05_SEGMENT_H
