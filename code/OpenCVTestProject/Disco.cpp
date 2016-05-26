#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

namespace Disco
{
	static void run()
	{
		VideoCapture cap(0);
		namedWindow("window1", 1);

		while (1)
		{
			Mat frame;
			cap >> frame;

			//do some operations
			Mat gray;
			cvtColor(frame, gray, CV_BGR2GRAY);
			Canny(gray, gray, 100, 200, 3);
			/// Find contours   
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			RNG rng(12345);
			findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
			/// Draw contours
			Mat drawing = Mat::zeros(gray.size(), CV_8UC3);
			for (int i = 0; i < contours.size(); i++)
			{
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
				drawContours(drawing, contours, i, color, CV_FILLED, 8, hierarchy, 0, Point());
			}

			imshow("window1", drawing);
			// Press ESC to escape
			if (waitKey(1) == 27) break;
		}
	}
}