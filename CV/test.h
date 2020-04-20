//
// Created by vincent on 20-4-19.
//

#ifndef CV_TEST_H
#define CV_TEST_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

string lena = "../image/lena.jpg";

void test()
{
    Mat image = imread(lena);
    imshow("image", image);
    waitKey(0);
}

#endif //CV_TEST_H
