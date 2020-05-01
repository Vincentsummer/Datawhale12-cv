//
// Created by vincent on 20-5-1.
//

#ifndef CV_EDGEDETECTIONTEST_H
#define CV_EDGEDETECTIONTEST_H

#include "utils.h"

using namespace cv;
using namespace std;

extern string lena;

void sobelTest()
{
    Mat src = imread(lena), sobelx, sobely;

    Sobel(src, sobelx, CV_64F, 1, 0, 5);
    Sobel(src, sobely, CV_64F, 0, 1, 5);

    imshow("src", src);
    imshow("sobelx", sobelx);
    imshow("sobely", sobely);
    waitKey();
}

void cannyTest()
{
    Mat src = imread(lena), gauss_img, canny_img;

    GaussianBlur(src, gauss_img, Size(3,3), 0);
    Canny(gauss_img, canny_img, 50, 150);

    imshow("src", src);
    imshow("canny", canny_img);
    waitKey();
}

#endif //CV_EDGEDETECTIONTEST_H
