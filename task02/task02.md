# 几何变换

 几何空间变换是图像处理中的最基础的算法，主要包括图像的旋转，平移，缩放，偏移，组合变换等。最常用的空间坐标变换之一就是仿射变换。仿射变换是一种二维坐标到二维坐标之间的线性变换，并保持二维图形的“平直性”。转换前平行的线，在转换后依然平行。

## 仿射变换

### 变换形式

根据冈萨雷斯书《数字图像处理_第三版》的变换矩阵方式，仿射变换的一般形式如下：
$$
\begin{bmatrix}
x & y & 1
\end{bmatrix} = 
\begin{bmatrix}
v & w & 1
\end{bmatrix}* T =
\begin{bmatrix}
v & w & 1
\end{bmatrix}
\begin{bmatrix}
t_{11} & t_{12} & 0 \\
t_{21} & t_{22} & 0 \\
t_{31} & t_{32} & 1
\end{bmatrix}
$$
其中 $T$ 即为变换矩阵。$(v,w)$ 为原坐标，$(x,y)$ 为变换后的坐标，不同的变换对应不同的矩阵。一些常见的变换矩阵及其作用如下表：

|       变换名称       |                       仿射变换矩阵 $T$                       |                           坐标公式                           |
| :------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|       恒等变换       | $\begin{bmatrix}1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$ |           $\begin{cases}x = v \\ y = w\end{cases}$           |
|    尺度变换(缩放)    | $\begin{bmatrix}c_x & 0 & 0 \\ 0 & c_y & 0 \\ 0 & 0 & 1 \end{bmatrix}$ |        $\begin{cases}x = vc_x \\ y = wc_y\end{cases}$        |
| 旋转变换(逆时针为正) | $\begin{bmatrix}\cos\theta & \sin\theta & 0 \\ -\sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix}$ | $\begin{cases}x = v\cos\theta-w\sin\theta \\ y = v\sin\theta+w\cos\theta\end{cases}$ |
| 旋转变换(顺时针为正) | $\begin{bmatrix}\cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix}$ | $\begin{cases}x = v\cos\theta+w\sin\theta \\ y = -v\sin\theta+w\cos\theta\end{cases}$ |
|       平移变换       | $\begin{bmatrix}1 & 0 & 0 \\ 0 & 1 & 0 \\ t_x & t_y & 1 \end{bmatrix}$ |    $\begin{cases}x = v + t_x \\ y = w + t_y \end{cases}$     |
|    偏移变换(水平)    | $\begin{bmatrix}1 & 0 & 0 \\ s_h & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$ |       $\begin{cases}x = v + ws_h \\ y = w\end{cases}$        |
|    偏移变换(垂直)    | $\begin{bmatrix}1 & s_v & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$ |       $\begin{cases}x = v \\ y = vs_v + w\end{cases}$        |

### 坐标系变换

对于缩放、平移变换，可以以图像坐标原点（图像左上角）为中心进行变换操作。而对于旋转和偏移，通常以图像中心作为原点，其中涉及坐标系变换。

<img src="task02.assets/%E5%9D%90%E6%A0%87%E7%B3%BB%E5%8F%98%E6%8D%A2.jpg" alt="坐标系变换" style="zoom: 67%;" />

对于旋转和偏移操作，有：

- 将输入原图图像坐标转换为笛卡尔坐标系；
- 进行旋转/偏移变换；
- 将旋转/偏移后的图像转换为图像坐标系。

假设图像可表示为 $M \times N$ 的矩阵，那么对于图像坐标系与笛卡尔坐标系，其原点坐标分别为 $(0,0)$ 和 $(-\frac{N}{2},\frac{M}{2})$ ，则图像某像素点 $(x^\prime,y^\prime)$ 与其在笛卡尔坐标系中的对应点 $(x, y)$ 的转换关系为：
$$
\begin{cases}
x = x^\prime - \frac{N}{2} \\ 
y = -y^\prime + \frac{M}{2}
\end{cases} 	\Longrightarrow
\begin{bmatrix}
x & y & 1
\end{bmatrix} = 
\begin{bmatrix}
x^\prime & y^\prime & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\ 0 & -1 & 0 \\ -\frac{N}{2} & \frac{M}{2} & 1 
\end{bmatrix}
$$
其逆变换为：
$$
\begin{cases}
x^\prime = x + \frac{N}{2} \\
y^\prime = -y + \frac{M}{2}
\end{cases} 	\Longrightarrow
\begin{bmatrix}
x^\prime & y^\prime & 1
\end{bmatrix} = 
\begin{bmatrix}
x & y & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\ 0 & -1 & 0 \\ \frac{N}{2} & \frac{M}{2} & 1 
\end{bmatrix}
$$

### 反向映射

前向映射根据原图用变换公式直接算出输出图像相应像素的空间位置，该映射方法会导致可能有多个像素坐标映射到输出图像的同一位置，或者输出图像的某些位置完全没有相应的输入图像像素与它匹配，即没有被映射，造成有规律的空洞（黑色的蜂窝状）。一种更好的方式是采用反向映射（Inverse Mapping）：扫描输出图像的位置$(x,y)$，通过 $\begin{bmatrix}v & w & 1\end{bmatrix}=\begin{bmatrix}x & y & 1 \end{bmatrix}* T^{-1}$ 计算输入图像对应的位置 $(v,w)$ ，通过插值方法决定输出图像中该位置的灰度值。

## 基于OpenCV的C++实现

### OpenCV相关函数

OpenCV仿射变换相关的函数一般涉及到warpAffine和getRotationMatrix2D这两个：

- 使用OpenCV函数warpAffine 来实现一些简单的重映射；
- OpenCV函数getRotationMatrix2D 来获得旋转矩阵。

#### warpAffined函数

```c++
 void cv::warpAffine	(InputArray 	src,
					 OutputArray 	dst,
					 InputArray 	M,
					 Size 			dsize,
					 int 			flags = INTER_LINEAR,
					 int 			borderMode = BORDER_CONSTANT,
					 const Scalar& 	borderValue = Scalar() 
)
/**
Parameters:
	src : 输入图像;
	dst : 输出图像，需和源图片有一样的尺寸和类型;
	M	: 2×3的变换矩阵;
	dsize : 输出图像的尺寸;
	flags : 插值方法的标识符;
		可选的插值方式如下： 
		INTER_NEAREST - 最近邻插值 
		INTER_LINEAR - 线性插值（默认值） 
		INTER_AREA - 区域插值 
		INTER_CUBIC – 三次样条插值 
		INTER_LANCZOS4 - Lanczos插值 
		CV_WARP_FILL_OUTLIERS - 填充所有输出图像的象素。如果部分象素落在输入图像的边界外，那么它	们的值设定为fillval。
		CV_WARP_INVERSE_MAP – 表示M为输出图像到输入图像的反变换，因此可以直接用来做象素插值。否则, warpAffine函数从M矩阵得到反变换。
	borderMode : 边界像素模式，默认值为BORDER_CONSTANT。
	borderValue : 在恒定的边界情况下取的值，默认值为Scalar()，即0。
**/
```

OpenCV中使用的变换矩阵为一个 $2\times 3$ 的矩阵，其变换形式如下：
$$
\begin{bmatrix}
x \\ y
\end{bmatrix} =
M * \begin{bmatrix}
v \\ w \\ 1
\end{bmatrix} = 
\begin{bmatrix}
m_{11} & m_{12} & m_{13} \\ m_{21} & m_{22} & m_{23}
\end{bmatrix}
\begin{bmatrix}
v \\ w \\ 1
\end{bmatrix}
$$
例如 $2 \times 3$ 的平移矩阵 $M$ 如下，其中 $m_x, m_y$ 分别表示在 $x, y$ 方向上的平移：
$$
M = 
\begin{bmatrix}
1 & 0 & m_x \\ 0 & 1 & m_y
\end{bmatrix}
$$
同理偏移矩阵 $M_h$ （水平方向）及 $M_v$ （垂直方向）如下：
$$
M_h = \begin{bmatrix}1 & m_h & 0 \\ 0 & 1 & 0\end{bmatrix}, \quad 
M_v = \begin{bmatrix}1 & 0 & 0 \\ m_v & 1 & 0\end{bmatrix}
$$

#### getRotationMatrix2D函数

```C++
Mat getRotationMatrix2D(Point2f center, double angle, double scale)
    
/**
Parameters:
	center : 表示源图像的旋转中心。
	angle : 旋转角度。角度为正值表示向逆时针旋转（坐标原点是左上角）。
	scale : 缩放系数。
**/
```

### 使用OpenCV函数实现几何变换：

```c++
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const static string lena = "../image/lena2.jpg";

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
    t_mat.at<float>(0, 2) = 20; //水平平移量
    t_mat.at<float>(1, 1) = 1;
    t_mat.at<float>(1, 2) = 10; //竖直平移量

    // 根据平移矩阵进行仿射变换
    warpAffine(src, tar, t_mat, tar_sz);

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
    off_mat.at<float>(0, 1) = -0.3; // 水平偏移
//    off_mat.at<float>(1, 0) = 0.3;  // 垂直偏移

    // 根据平移矩阵进行仿射变换
    warpAffine(src, tar, off_mat, tar_sz);

    // 显示平移效果
    imshow("source", src);
    imshow("target", tar);

    waitKey(0);
}

int main()
{
    rotateTest();
//    translationTest();
//    offsetTest();
    return 0;
}
```

原图：

<img src="task02.assets/lena2.jpg" alt="lena2" style="zoom: 50%;" />

旋转45°：

<img src="task02.assets/lena2_rotate45-1587536826301.jpg" alt="lena2_rotate45" style="zoom:50%;" />

平移：

<img src="task02.assets/lena2_trans.jpg" alt="lena2_trans" style="zoom:50%;" />

水平偏移：

<img src="task02.assets/lena2_offset_h.jpg" alt="lena2_offset_h" style="zoom:50%;" />

垂直偏移：

<img src="task02.assets/lena2_offset_v.jpg" alt="lena2_offset_v" style="zoom:50%;" />

### 几何变换的C++实现

translation.h头文件如下：

```C++
#ifndef CV_TRANSLATION_H
#define CV_TRANSLATION_H

#include <opencv2/opencv.hpp>

#include "interpolation.h"

using namespace cv;

namespace vincent
{
    enum OFFSET
    {
        HORIZONTAL  = 0,	// 水平
        VERTICAL    = 1,	// 垂直
    };

    // 仿射变换
    void warpAffine(Mat& src, Mat& tar, Mat& M, Size dsize, int flags = LINEAR);

    Mat getRotationMat(Point2f center, double angle, double scale = 1.0);   // 旋转矩阵
    Mat getTransMat(float mx, float my);                                    // 平移矩阵
    Mat getOffsetMat(Point2f center, float m, int flags);                   // 偏移矩阵
    /**
     * 坐标变换矩阵
     * flag = 1 : 正变换， 图像坐标 -> 笛卡尔坐标
     * flag = -1 : 逆变换， 笛卡尔坐标 -> 图像坐标
     * **/
    Mat getCoordinateTransMat(Point2f center, int flag);

} // namesapace vincent

#endif //CV_TRANSLATION_H

```

translation.cpp源文件如下：

```c++
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
                // 反向映射, 求目标图像当前点(i,j)在源图像的对应点。
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
```

main.cpp测试代码如下：

```c++
#include "task01/resizeTest.h"
#include "task02/transTest.h"

using namespace std;

const static string lena = "../image/lena2.jpg";

int main()
{
    Mat src = imread(lena);
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
    return 0;
}
```

