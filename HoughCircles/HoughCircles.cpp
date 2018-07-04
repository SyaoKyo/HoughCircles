#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;

/** @function main */
int main()
{
	Mat src, src_gray;

	// ��ȡԭͼ
	src = imread("earth.jpg", 1);
	if (!src.data)
	{
		return -1;
	}
	imshow("", src);
	// �Ҷȴ���
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// ��˹����
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	// ��Բ
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 210, 50, 0, 0);

	// �����ҵ���Բ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// Բ��
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// Բ
		circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
	}

	// չʾ���
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	waitKey(0);
	return 0;
}