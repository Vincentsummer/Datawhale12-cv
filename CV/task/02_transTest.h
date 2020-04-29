//
// Created by vincent on 20-4-22.
//

/**
 * OpenCV 几何变换
 * **/

#ifndef CV_TRANSTEST_H
#define CV_TRANSTEST_H

#include "../myCV/translation.h"

using namespace cv;
using namespace std;

const static string lena2 = "../image/lena2.jpg";

void myTransTest()
{
    Mat src = imread(lena2);
    Mat tar;
    Size tar_sz = src.size();
    // 指定旋转中心（图像中点）
    Point2f center(src.cols / 2., src.rows / 2.);

    // 旋转角度
    double angle = 120;
    // 平移量
    float mx = 40, my = 30;
    // 偏移量
    float mh = -0.3, mv = 0.3;

    // 获取3×3变换矩阵
    Mat rot_mat = vincent::getRotationMat(center, angle, 1.0);
    Mat trans_mat = vincent::getTransMat(mx, my);
    Mat offset_h_mat = vincent::getOffsetMat(center, mh, vincent::HORIZONTAL);
    Mat offset_v_mat = vincent::getOffsetMat(center, mv, vincent::VERTICAL);
    // 根据旋转矩阵进行仿射变换
    vincent::warpAffine(src, tar, offset_v_mat, tar_sz);

    // 显示旋转效果
    imshow("source", src);
    imshow("target", tar);

    waitKey(0);
}

void rotateTest()
{
    Mat src = imread(lena);
    Mat tar;

    // 旋转角度
    double angle = 45;

    Size tar_sz = src.size();

    // 指定旋转中心（图像中点）
    Point2f center(src.cols / 2., src.rows / 2.);
    // 获取旋转矩阵(2×3矩阵)
    Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
    // 根据旋转矩阵进行仿射变换
    warpAffine(src, tar, rot_mat, tar_sz);

//    imwrite("../image/lena2_rotate45.jpg", tar);

    // 显示旋转效果
    imshow("source", src);
    imshow("target", tar);

    waitKey(0);
}

void translationTest()
{
    Mat src = imread(lena);
    Mat tar;

    Size tar_sz = src.size();

    // 定义平移矩阵
    Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
    t_mat.at<float>(0, 0) = 1;
    t_mat.at<float>(0, 2) = 40; //水平平移量
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 30; //竖直平移量

    // 根据平移矩阵进行仿射变换
    warpAffine(src, tar, t_mat, tar_sz);

//    imwrite("../image/lena2_trans.jpg", tar);

    // 显示平移效果
    imshow("source", src);
    imshow("target", tar);

    waitKey(0);
}

void offsetTest()
{
    Mat src = imread(lena);
    Mat tar;

    Size tar_sz = src.size();

    // 定义偏移矩阵
    Mat off_mat = Mat::zeros(2, 3, CV_32FC1);
    off_mat.at<float>(0, 0) = 1;
    off_mat.at<float>(1, 1) = 1;
//    off_mat.at<float>(0, 1) = -0.3; // 水平偏移
    off_mat.at<float>(1, 0) = 0.3;  // 垂直偏移

    // 根据平移矩阵进行仿射变换
    warpAffine(src, tar, off_mat, tar_sz);

//    imwrite("../image/lena2_offset_v.jpg", tar);

    // 显示平移效果
    imshow("source", src);
    imshow("target", tar);

    waitKey(0);
}

#endif //CV_TRANSTEST_H
