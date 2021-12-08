#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
using namespace std;
using namespace cv;



Mat HOGbr(Mat& trainingData) {
	Mat bx(trainingData.size() / 8, CV_8U, Scalar(0));
	Mat by(trainingData.size() / 8, CV_8U, Scalar(0));
	Mat b(trainingData.size() / 8, CV_8U, Scalar(0));
	Mat bt(trainingData.size() / 8, CV_8U, Scalar(0));
	Mat br(trainingData.size(), CV_8U, Scalar(0));//HOG
	int dx, dy;

	for (int y = 0; y < trainingData.rows; y += 8) {
		for (int x = 0; x < trainingData.cols - 8; x += 8) {
			dx = trainingData.at<uchar>(y, x) - trainingData.at<uchar>(y, x + 8); // -255~255
			//cout << "src2 : " << "(" << x << ", " << y << ") = " << (int)src2.at<uchar>(y, x) << endl;
			bx.at<uchar>(y / 8, x / 8) = (dx + 255) / 2;
			//cout << "bx : " << "(" << x/8 << ", " << y/8 << ") = " << (int)bx.at<uchar>(y/8, x/8) << endl;
		}
	}
	for (int y = 0; y < trainingData.rows - 8; y += 8) {
		for (int x = 0; x < trainingData.cols; x += 8) {
			dy = trainingData.at<uchar>(y, x) - trainingData.at<uchar>(y + 8, x); // -255~255
			by.at<uchar>(y / 8, x / 8) = (dy + 255) / 2;
			//cout << a << endl;
		}
	}
	for (int y = 0; y < by.rows; y++) {
		for (int x = 0; x < bx.cols; x++) {
			double a1 = abs((double)by.at<uchar>(y, x) * 2 - 255);
			double a2 = abs((double)bx.at<uchar>(y, x) * 2 - 255);
			b.at<uchar>(y, x) = sqrt(pow(a1, 2) + pow(a2, 2)) / sqrt(2);
			// b -> sqrt(2)*255-> 0~255
			//cout << (int)b.at<uchar>(y, x) << endl;
			//cout << y << ", " << src2.rows << " : " << (y * 100 / src2.rows) << "%" << endl;
		}
	}
	for (int y = 0; y < by.rows; y++) {
		for (int x = 0; x < bx.cols; x++) {
			bt.at<uchar>(y, x) = atan((double)by.at<uchar>(y, x) / (double)bx.at<uchar>(y, x)) / CV_PI * 2 * 255;
			// b -> sqrt(2)*255-> 0~255
			//cout << (int)bt.at<uchar>(y, x) << endl;
		}
	}

	//result
	for (int y = 0; y < b.rows - 1; y++) {
		for (int x = 0; x < b.cols - 1; x++) {
			Point2i p1;
			p1 = Point2i(x * 8 + 4, y * 8 + 4);
			double angle = bt.at<uchar>(y, x) * 360 / 255;
			//cout << angle << endl;
			int co = b.at<uchar>(y, x);
			ellipse(br, p1, Size(0.5, 4), angle, 0, 360, Scalar(co), 2);
		}
	}
	return br;
}

//Mat tmp[8];
//for(int i =0;i<8;i++
//	tmp[i] = HOGbr(trainingData)
