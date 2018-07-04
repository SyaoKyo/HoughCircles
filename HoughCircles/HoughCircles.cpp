#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;

/** @function main */
int main()
{
	Mat src, src_gray;

	// 读取原图
	src = imread("earth.jpg", 1);
	if (!src.data)
	{
		return -1;
	}
	imshow("", src);
	// 灰度处理
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// 高斯降噪
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	// 找圆
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 210, 50, 0, 0);

	// 画出找到的圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// 圆心
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// 圆
		circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
	}

	// 展示结果
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	waitKey(0);
	return 0;
}