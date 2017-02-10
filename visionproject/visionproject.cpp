// visionproject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	

	Mat imageColor1;
	imageColor1 = imread("1.tif", CV_LOAD_IMAGE_COLOR); // Read the file
	cout << imageColor1.channels();

	if (!imageColor1.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -2;
	}

	Mat imageColor2(imageColor1.size(), CV_8UC3);
	Mat imageColor3(imageColor1.size(), CV_8UC3);
	Mat imageColor4(imageColor1.size(), CV_8UC3);
	Mat imageColor5(imageColor1.size(), CV_8UC3);
	Mat imageColor6(imageColor1.size(), CV_8UC3);
	Mat imageColor7(imageColor1.size(), CV_8UC3);
	Mat imageColor8(imageColor1.size(), CV_8UC3);

	Mat b, g, r;
	vector<Mat> ch(3);
	vector<Mat> g1(2);
	split(imageColor1, ch);//splitting image

	b = ch[0];
	g = ch[1];
	r = ch[2];

	g1[0] = (2 * g) - r - b;
	g1[1] = (1.2*r) - g;

	//merge(ch, imageColor2);
	//GaussianBlur(imageColor2,imageColor3, Size(3,3), 0, 0 );
	Mat gray_image1(imageColor1.size(), CV_8UC1);
	gray_image1 = g1[0];

	namedWindow("Display window one", WINDOW_KEEPRATIO); // Create a window for display.
	imshow("Display window one", gray_image1); // Show our grayscale1 img

	Mat gray_image2(imageColor1.size(), CV_8UC1);
	gray_image2 = g1[1];

	namedWindow("Display window two", WINDOW_KEEPRATIO); // Create a window for display.
	imshow("Display window two", gray_image2); // Show our grayscale2 img

	Mat diff_image = gray_image1 - gray_image2;
	namedWindow("Display window three", WINDOW_KEEPRATIO); // Create a window for display.
	imshow("Display window three", diff_image); // Show our diff img
	imwrite("binaryimg.png", diff_image);

	/*
	Mat imageColor(imageColor1.size(), CV_8UC3);
	bitwise_and(imageColor1, Scalar(0, 255, 0),imageColor,noArray());
	

	Mat grayscale(imageColor1.size(), CV_8UC1);//color to grayscale
	cvtColor(imageColor1, grayscale, CV_RGB2GRAY);
	*/

	Mat binaryMat(diff_image.size(), diff_image.type());//grayscale to binary
	threshold(diff_image, binaryMat, 0, 255,CV_THRESH_OTSU);

	namedWindow("Display window four", WINDOW_KEEPRATIO); // Create a window for display.
	imshow("Display window four", binaryMat); // Show our image inside it.

	cvtColor(binaryMat, imageColor6, CV_GRAY2BGR);//binary to color
	bitwise_and(imageColor6, imageColor1, imageColor7, noArray());// bitwise and of original vs thresholded binary
	
	namedWindow("Display window five", WINDOW_KEEPRATIO); // Create a window for display.
	imshow("Display window five", imageColor7); // Show our image inside it.

	merge(ch, imageColor8);
	imwrite("1png.png", imageColor8);


	waitKey(0); // Wait for a keystroke in the window
	return 0;
	
}

