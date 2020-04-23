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

//string lena = "image/lena.jpg";

void test()
{
    Mat image = imread(lena);
    Mat target = Mat::zeros(image.rows * 2, image.cols * 2, image.type());

    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            target.at<Vec3b>(i + image.rows / 2, j + image.cols / 2) = image.at<Vec3b>(i,j);
        }
    }
    imwrite("image/lena2.jpg", target);

    imshow("target", target);
    waitKey(0);
}

#endif //CV_TEST_H
