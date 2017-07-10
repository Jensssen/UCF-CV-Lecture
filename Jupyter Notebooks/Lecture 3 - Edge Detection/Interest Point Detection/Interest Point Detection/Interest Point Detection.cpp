// Interest Point Detection.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	Mat image;
	Mat img_gray;
	image = imread("C:/Users/nur20/Documents/GitHub/UCF-CV-Lecture/Jupyter Notebooks/Lecture 4 - Interest Point Detection/images/Lecture 4/Hiro1.jpg");   // Read the file

	// Print original image
	imshow("Original", image);                 
	// Apply Gaussian Blur on the image
	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// Convert it to gray
	cvtColor(image, img_gray, CV_BGR2GRAY);

	// Generate grad_x and grad_y
	Mat grad_x, grad_y, grad;
	Mat abs_grad_x, abs_grad_y;

	// Gradient X
	int ddepth = CV_16S;
	int scale = 1;
	int delta = 0;
	Scharr( img_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );

	// Gradient Y
	Scharr(img_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

	// output of Scharr is in a range of round about -100 to 1000. with convertScaleAbs we convert it to 0-255
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	imshow("Grad_x", abs_grad_x);
	imshow("Grad_y", abs_grad_y);

	// bring both images together
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	// Apply threshold to the image
	for (int i = 0; i < grad.rows; i++) {
		for (int j = 0; j < grad.cols; j++) {
			if (grad.at<uchar>(i, j) <= 125) {
				grad.at<uchar>(i, j) = 0;
			}
			else {
				grad.at<uchar>(i, j) = 255;

			}
		}
	}
	imshow("Grad", grad);

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}

