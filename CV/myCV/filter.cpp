//
// Created by vincent on 20-4-27.
//

#include "filter.h"
#include "../task/utils.h"
#include <vector>

using namespace std;

void vincent::boxFilter(cv::Mat &src, cv::Mat &tar, cv::Size ksize, bool normalize)
{
    if (src.channels() == 1) boxU(src, tar, ksize);
    else if (src.channels() == 3) box3b(src, tar, ksize);

    if (normalize) tar /= (ksize.width * ksize.height);
}

void vincent::boxU(cv::Mat &src, cv::Mat &tar, cv::Size ksize)
{

    // 初始化
    cv::Size src_size = src.size();
    int kw = ksize.width, kh = ksize.height;    // 核大小
    CV_Assert(kw < src_size.width && kh < src_size.height);
    int box_w = src_size.width - kw, box_h = src_size.height - kh;
    tar = cv::Mat(src);

    vector<int> sum(box_w * box_h, 0);
    vector<int> buff(src_size.width, 0);

    // 设置buff
    for (int i = 0; i < src_size.width; ++i){
        for (int j = 0; j < kh; ++j){
            buff[i] += src.at<uchar>(i,j);
        }
    }

    for (int y = 0; y < src_size.height - kh; ++y){
        int Xsum = 0;
        for (int j = 0; j < kw; j++)
            Xsum += buff[j];

        // sum求和
        for (int x = 0; x < box_w; ++x) {
            if (x != 0)
                Xsum = Xsum - buff[x-1] + buff[kw+x-1];

            sum[y * box_w + x] = Xsum;
        }

        // 更新buff
        for (int x = 0; x < src_size.width; ++x)
            buff[x] = buff[x] - src.at<uchar>(y, x) + src.at<uchar>(y+kh, x);
    }

    // 遍历，得到每个点的和，传给矩阵tar
    for (int i = 0; i < src_size.height; ++i){
        for (int j = 0; j < src_size.width; ++j){
            if (i > kh/2 && i < src_size.height - kh/2 && j > kw/2 && j < src_size.width - kw/2)
                tar.at<uchar>(i,j) = (uchar) (sum[(i - kh / 2) * box_w + (j - kw / 2)] / (kh * kw));
        }
    }
}

void vincent::box3b(cv::Mat &src, cv::Mat &tar, cv::Size ksize)
{

    // 初始化
    cv::Size src_size = src.size();
    int kw = ksize.width, kh = ksize.height;    // 核大小
    CV_Assert(kw < src_size.width && kh < src_size.height);
    int box_w = src_size.width - kw, box_h = src_size.height - kh;
    tar = cv::Mat(src_size.width, src_size.height, 0, CV_32FC3);

    vector<cv::Vec3i> sum(box_w * box_h, 0);
    vector<cv::Vec3i> buff(src_size.width, 0);

    // 设置buff
    for (int i = 0; i < src_size.width; ++i){
        for (int j = 0; j < kh; ++j){
            buff[i] += src.at<cv::Vec3b>(i,j);
        }

//        std::cout << buff[i] << std::endl;
    }

    for (int y = 0; y < src_size.height - kh; ++y){
        cv::Vec3i Xsum = 0;
        for (int j = 0; j < kw; j++)
            Xsum += buff[j];

        // sum求和
        for (int x = 0; x < box_w; ++x) {
            if (x != 0){
                Xsum[0] = Xsum[0] - buff[x-1][0] + buff[kw+x-1][0];
                Xsum[1] = Xsum[1] - buff[x-1][1] + buff[kw+x-1][1];
                Xsum[2] = Xsum[2] - buff[x-1][2] + buff[kw+x-1][2];
            }

            sum[y * box_w + x] = Xsum;
        }

        // 更新buff
        for (int x = 0; x < src_size.width; ++x){
            buff[x][0] -= src.at<cv::Vec3b>(y, x)[0] + src.at<cv::Vec3b>(y+kh, x)[0];
            buff[x][1] -= src.at<cv::Vec3b>(y, x)[1] + src.at<cv::Vec3b>(y+kh, x)[1];
            buff[x][2] -= src.at<cv::Vec3b>(y, x)[2] + src.at<cv::Vec3b>(y+kh, x)[2];
        }
    }

    // 遍历，得到每个点的和，传给矩阵tar
    for (int i = 0; i < src_size.height; ++i){
        for (int j = 0; j < src_size.width; ++j){
            if (i > kh/2 && i < src_size.height - kh/2 && j > kw/2 && j < src_size.width - kw/2)
                tar.at<cv::Vec3b>(i,j) = sum[(i - kh / 2) * box_w + (j - kw / 2)];
//            std::cout << tar.at<cv::Vec3b>(i,j) << std::endl;
        }
    }
}