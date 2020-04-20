//
// Created by vincent on 20-4-20.
//

#include "interpolation.h"

void vincent::inter_nearest(cv::Mat &src, cv::Mat &tar, float fx, float fy)
{
    // 计算输出图像的尺寸(四舍五入)
    int tar_cols = round(src.cols * fx);
    int tar_rows = round(src.rows * fy);
    // 创建输出图像
    tar = cv::Mat(tar_rows, tar_cols, src.type());

    for (int i = 0; i < tar_rows; i++){
        for (int j = 0; j < tar_cols; j++){
            // 插值计算
            int x = round(i / fy);
            int y = round(j / fx);
            // 越界判断
            if (x > src.rows - 1) x = src.rows - 1;
            if (y > src.cols - 1) y = src.cols - 1;

            // 灰度图处理
            if (src.channels() == 1)
                tar.at<uchar>(i, j) = src.at<uchar>(x, y);
            // 彩色图处理
            else
                tar.at<cv::Vec3b>(i, j) = src.at<cv::Vec3b>(x, y);
        }
    }
}

template <typename T>
T vincent::get_scale_value(cv::Mat &src, float x, float y)
{
    int i = (int) x, j = (int) y;
    float u = x - i, v = y - j;

    // 边界处理
    if (i >= src.rows - 1 || j >= src.cols - 1)
        return src.at<T>(i, j);

    T Q11 = src.at<T>(i, j);
    T Q12 = src.at<T>(i, j+1);
    T Q21 = src.at<T>(i+1, j);
    T Q22 = src.at<T>(i+1, j+1);

    return ((1-v)*(1-u)*Q11 + (1-v)*u*Q21 + v*(1-u)*Q12 + v*u*Q22);
}

void vincent::inter_linear(cv::Mat &src, cv::Mat &tar, float fx, float fy)
{
    {
        // 计算输出图像的尺寸(四舍五入)
        int tar_cols = round(src.cols * fx);
        int tar_rows = round(src.rows * fy);
        // 创建输出图像
        tar = cv::Mat(tar_rows, tar_cols, src.type());

        for (int i = 0; i < tar_rows; i++){
            for (int j = 0; j < tar_cols; j++){
                // 坐标计算
                float x = i / fy;
                float y = j / fx;

                // 灰度图处理
                if (src.channels() == 1)
                    tar.at<uchar>(i, j) = get_scale_value<uchar>(src, x, y);
                // 彩色图处理
                else
                    tar.at<cv::Vec3b>(i, j) = get_scale_value<cv::Vec3b>(src, x, y);
            }
        }
    }
}