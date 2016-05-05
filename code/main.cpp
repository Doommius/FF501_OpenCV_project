#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/photo.hpp"

using namespace std;
using namespace cv;

namespace main
{
	const char* winName = "canny";
	int maxThres = 30;

	void on_trackbar(int, void *)
	{

	}

	int main(int argc, char** argv) {
		VideoCapture cap;

		namedWindow(winName, WINDOW_AUTOSIZE);
		createTrackbar("Threshold 2", winName, &maxThres, 150);

		if (!cap.open(0)) return 0;
		for (;;) {
			Mat frame, gray, edges, dst;
			cap >> frame;

			frame.copyTo(gray);
			//cvtColor(gray, gray, CV_BGR2GRAY);

			//blur(gray, gray, Size(15, 15));
			GaussianBlur(gray, gray, Size(7, 7), 1.5);

			Canny(gray, edges, maxThres, maxThres * 2, 3);

			dst = Scalar::all(0);

			frame.copyTo(dst, edges);

			if (frame.empty()) break;
			imshow(winName, edges);
			if (waitKey(1) == 27) break;
		}
	}
}