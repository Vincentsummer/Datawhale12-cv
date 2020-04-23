//
// Created by vincent on 20-4-22.
//

#include "translation.h"

void vincent::warpAffine(Mat &src, Mat &tar, Mat &M, Size dsize, int flags)
{
    tar = Mat::zeros(dsize.height, dsize.width, src.type());
    Mat T = Mat::ones(1, 3, CV_32FC1);
    // 灰度图处理
    if (src.channels() == 1){
        for (int i = 0; i < tar.rows; ++i){
            for (int j = 0; j < tar.cols; ++j){
                T.at<float>(0,0) = j;
                T.at<float>(0,1) = i;
                // 反向映射, 求目标图像当前点(i,j)在源图像的对应点。
                Mat S = T * M.inv();
                // 插值计算
                float x = S.at<float>(0,0), y = S.at<float>(0,1);
                if (x < src.cols && y < src.rows)
                    tar.at<uchar>(i, j) = interpolationCh1[flags](src, x, y);
            }
        }
    }
    // 彩色图处理
    else {
        for (int i = 0; i < tar.rows; ++i){
            for (int j = 0; j < tar.cols; ++j){
                T.at<float>(0,0) = j;
                T.at<float>(0,1) = i;
                // 反向映射, 求目标图像当前点(j,i)在源图像的对应点。
                Mat S = T * M.inv();
                // 插值计算
                float x = S.at<float>(0,0), y = S.at<float>(0,1);
                if (x < src.cols && y < src.rows)
                    tar.at<Vec3b>(i, j) = interpolationCh3[flags](src, x, y);
            }
        }
    }
}

Mat vincent::getCoordinateTransMat(Point2f center, int flag)
{
    Mat T = Mat::eye(3, 3, CV_32FC1);

    T.at<float>(1,1) = -1;
    T.at<float>(2,0) = - flag * center.x;
    T.at<float>(2,1) = center.y;

    return T;
}

Mat vincent::getRotationMat(Point2f center, double angle, double scale)
{
    Mat T = getCoordinateTransMat(center, 1);
    Mat t = getCoordinateTransMat(center, -1);
    Mat M = Mat::eye(3, 3, CV_32FC1);

    angle = angle * CV_PI / 180.0;

    M.at<float>(0,0) = (float)cos(angle);
    M.at<float>(0,1) = -(float)sin(angle);
    M.at<float>(1,0) = (float)sin(angle);
    M.at<float>(1,1) = (float)cos(angle);

    M = T * M * t;
    return M;
}

Mat vincent::getTransMat(float mx, float my)
{
    Mat M = Mat::eye(3, 3, CV_32FC1);

    M.at<float>(2,0) = mx;
    M.at<float>(2,1) = my;
    return M;
}

Mat vincent::getOffsetMat(Point2f center, float m, int flags)
{
    Mat T = getCoordinateTransMat(center, 1);
    Mat t = getCoordinateTransMat(center, -1);
    Mat M = Mat::eye(3, 3, CV_32FC1);

    if (flags == 0) M.at<float>(1,0) = m;   // 水平偏移
    else M.at<float>(0,1) = m;              // 垂直偏移

    M = T * M * t;
    return M;
}


