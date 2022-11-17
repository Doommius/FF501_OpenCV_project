/*
* File:   Week1.cpp
* Author: Mark Jervelund <Mark@jervelund.com>
*
* Created on 22 may 2016 1:58 pm
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
	string dirsource = "C:\\testfolder\\videos.avi";
	string diredges = "C:\\testfolder\\videoedge.avi";
	
	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
	VideoWriter edgewriter(diredges, CV_FOURCC('D', 'I', 'V', 'X'), CV_CAP_PROP_FRAME_COUNT, cvSize(640, 480), false);
	VideoWriter sourcewriter(dirsource, CV_FOURCC('D', 'I', 'V', 'X'), CV_CAP_PROP_FRAME_COUNT, cvSize(640, 480), true);

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera";
	}
	if (!sourcewriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video for source" << endl;
		return -1;
	}
	if (!edgewriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video for edge" << endl;
		return -1;
	}

	//unconditional loop
	Mat Greyscalleframe;
	while (true) {
		Mat cameraFrame;
		stream1.read(cameraFrame);
		imshow("cam", cameraFrame);
		cvtColor(cameraFrame, Greyscalleframe, COLOR_BGR2GRAY);
		GaussianBlur(Greyscalleframe, Greyscalleframe, Size(7, 7), 1.5, 1.5);
		Canny(Greyscalleframe, Greyscalleframe, 40, 40, 3);
		edgewriter.write(Greyscalleframe);
		sourcewriter.write(cameraFrame);
		imshow("Greyscale", Greyscalleframe);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
