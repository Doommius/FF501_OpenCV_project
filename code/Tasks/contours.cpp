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

const char* winName = "contour";
RNG rng(12345);

int main(int argc, char** argv ) {
    VideoCapture cap;

    namedWindow(winName, WINDOW_AUTOSIZE);

    if (!cap.open(0)) return 0;
    for (;;) {
        Mat frame, dst;
        cap >> frame;
        if (frame.empty()) break;

        dst = Mat::zeros(frame.rows, frame.cols, CV_8UC1);

        cvtColor(frame, frame, CV_BGR2GRAY);
        GaussianBlur(frame, frame, Size(7, 7), 1.5);
        Canny(frame, frame, 30, 60);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours( frame, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        Mat draw = Mat::zeros(frame.size(), CV_8UC3);
        for(int i = 0 ; i < contours.size(); i++)
        {
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
            drawContours( draw, contours, i, color, CV_FILLED, 8, hierarchy );
        }

        imshow(winName, draw);
        if (waitKey(1) == 27) break;
    }
}