#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>
#include <string>
#include <stdio.h>
#include "opencv2/videoio.hpp"
#include "opencv2/photo.hpp"

using namespace std;
using namespace cv;

namespace contour
{
	const char* winName = "contour";
	RNG rng(12345);

	int main(int argc, char** argv) {
		VideoCapture cap;

		//create a window which auto sizes
		namedWindow(winName, WINDOW_AUTOSIZE);

		if (!cap.open(0)) //open the first capture device, usually the webcam, returns whether successful
			return 0; //if not successful, quit the program
		for (;;) //infinite loop
		{
			Mat frame, dst; //Matrices to store data
			cap >> frame; //take a frame from the capture device and put it in 'frame'
			if (frame.empty()) break; //if the frame was empty for some reason, quit the program

			//make 'dst' a 'frame.rows' by 'frame.cols' matrix. Choose the color space to be binary
			dst = Mat::zeros(frame.rows, frame.cols, CV_8UC1);

			//do operations to the captured frame
			cvtColor(frame, frame, CV_BGR2GRAY); //convert the color space to gray
			GaussianBlur(frame, frame, Size(7, 7), 1.5); //do some blurring
			Canny(frame, frame, 30, 60); //and then some edge detection

			vector<vector<Point> > contours; //variables to store the contour points
			vector<Vec4i> hierarchy; //the hierarchy of the contours

			//find the contours and fill in their hierarchy
			findContours(frame, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

			// iterate through all the top-level contours,
			// draw each connected component with its own random color
			Mat draw = Mat::zeros(frame.size(), CV_8UC3); //draw to this matrix
			for (int i = 0; i < contours.size(); i++)
			{

				//choose a random color
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				drawContours(draw, contours, i, color, 8, 8, hierarchy);
			}

			imshow(winName, draw); //show the drawing
			if (waitKey(1) == 27) break; //quit the program if the 'Esc' key is pressed (int code 27)
		}
	}
}