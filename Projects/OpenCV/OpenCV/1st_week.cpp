//#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>

using namespace cv;
using namespace std;
//int main(){
int submain(){
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened()){
		cout << "ERROR: Cannot open the video file" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
												//
//  double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
//  double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
//
//  cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	string dir = "C:\\Users\\zlyza\\Desktop\\Biggest Project\\WebCamRecordings\\MyVideo.avi";
	cout << CV_CAP_PROP_FRAME_COUNT << endl;
	VideoWriter oVideoWriter(dir, CV_FOURCC('D', 'I', 'V', 'X'), CV_CAP_PROP_FRAME_COUNT, cvSize(640, 480), false); //initialize the VideoWriter object

	if (!oVideoWriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video" << endl;
		return -1;
	}
	Mat edges;

	while (1) {
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video
		if (!bSuccess){
			cout << "ERROR: Cannot read a frame from video file" << endl;
			break;
		}

		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 40, 40, 3);
		oVideoWriter.write(edges);
		imshow("MyVideo", edges);
//        imshow("MyVideoOG", frame);
		if (waitKey(10) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}