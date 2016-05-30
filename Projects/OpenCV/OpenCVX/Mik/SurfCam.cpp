#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/ml.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using namespace cv::ml;

namespace SurfCam
{
	static void run()
	{
		VideoCapture cap(0);
		namedWindow("window1", 1);

		Ptr<SURF> surf = SURF::create(4000);
		surf->setUpright(true);

		cout << "Des. size = " << surf->descriptorSize() << endl;

		while (1)
		{
			Mat frame;
			cap >> frame;

			vector<KeyPoint> kp;
			Mat des;

			surf->detect(frame, kp);
			surf->compute(frame, kp, des);

			drawKeypoints(frame, kp, frame, cv::Scalar_<double>::all(-1), 4);

			imshow("window1", frame);
			// Press ESC to escape
			if (waitKey(1) == 27) break;
		}
	}
}