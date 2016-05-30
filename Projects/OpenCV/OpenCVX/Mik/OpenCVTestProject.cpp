////most frequent C++ header files: not all are used here
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <thread>
//#include <functional>
//#include <mutex>
//#include <atomic>
//
////most frequent C header files: not all are used here if
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//
////OpenCV batch header files
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>
//
//#include <Mort.h>
//#include <ANPR.h>
//#include <MySVM.h>
//#include <ImageLocations.h>
//
////namespace in C++ is like package name in Java
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//
//
//void runVideo()
//{
//	//Mort m;
//	//m.OWN();
//
//	/*Mat image = imread(testImages[0]);
//	ANPR a;
//
//	for (Mat segment : a.segment(image))
//	{
//	imshow("segment", segment);
//	waitKey(0);
//	}*/
//
//	const int divFactor = 2;
//
//	VideoCapture capture("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\Video_2.mp4");
//	Mat frame;
//
//	if (!capture.isOpened())
//		throw "Error opening file!";
//
//	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH) / divFactor;
//	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT) / divFactor;
//	//VideoWriter videoOut("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\video_2_canny.avi", CV_FOURCC('M','J','P','G'), 30, Size(frameWidth, frameHeight));
//
//	namedWindow("video", CV_WINDOW_AUTOSIZE);
//
//	ANPR a;
//
//	while (true)
//	{
//		capture >> frame;
//
//		if (frame.empty()) break;
//
//		//resize the input frame a bit
//		resize(frame, frame, Size(1920 / divFactor, 1080 / divFactor));
//
//		Mat img; //the 'working' matrix, the frame should preferrably be left untouched
//		frame.copyTo(img);
//
//
//		//segment the image using our own procedure
//		vector<Rect> rects = a.segment(frame);
//
//		//go through each segment
//		for (Rect rect : rects)
//		{
//			//draw each rectangle
//			rectangle(img, rect.tl(), rect.br(), Scalar(0, 255, 0));
//
//			//get 12 features from each segment
//			vector<KeyPoint> kp = a.getKeypoints(frame(rect), 12);
//
//			//we need to offset all keypoints for drawing
//			for (KeyPoint& p : kp)
//			{
//				p.pt = Point2f(p.pt.x + rect.tl().x, p.pt.y + rect.tl().y);
//			}
//
//			//draw the keypoints
//			drawKeypoints(img, kp, img, Scalar(0, 0, 255));
//		}
//
//		imshow("video", img);
//		//videoOut << frame;
//		if (waitKey(1) == 27) break;
//	}
//}
//
//int main(int argc, const char * argv[])
//{
//	ANPR a;
//	Mat imgg = imread(baseImagesPath[0], IMREAD_GRAYSCALE);
//	imshow("hi", imgg);
//	MySVM m;
//	m.create();
//
//	Mat samples;
//	Mat labels(1, positiveImagesAmount + negativeImagesAmount, CV_32SC1);
//
//	for (int i = 0; i < positiveImagesAmount; i++)
//	{
//		Mat img = imread(positiveImagesPath[i], IMREAD_GRAYSCALE);
//		vector<KeyPoint> kp = a.getKeypoints(img, 12);
//		Mat des = a.getDescriptors(img, kp);
//		des = des.reshape(0, 1); //reshape to single row
//		samples.push_back(des); //add to results
//		labels.at<int>(i) = 1; //is a numberplate
//	}
//
//	for (int i = 0; i < negativeImagesAmount; i++)
//	{
//		Mat img = imread(negativeImagesPath[i], IMREAD_GRAYSCALE);
//		vector<KeyPoint> kp = a.getKeypoints(img, 12);
//		Mat des = a.getDescriptors(img, kp);
//		des = des.reshape(0, 1); //reshape to single row
//		samples.push_back(des); //add to results
//		labels.at<int>(positiveImagesAmount + i) = 0; //is not a numberplate
//	}
//
//	Ptr<TrainData> t = TrainData::create(samples, ROW_SAMPLE, labels);
//	cout << "trainAuto: " << m.machine->trainAuto(t, 10, SVM::getDefaultGrid(SVM::C),
//		SVM::getDefaultGrid(SVM::GAMMA),
//		SVM::getDefaultGrid(SVM::P),
//		SVM::getDefaultGrid(SVM::NU),
//		SVM::getDefaultGrid(SVM::COEF),
//		SVM::getDefaultGrid(SVM::DEGREE), false) << endl;
//
//	//now test the SVM
//	for (int i = 0; i < segmentImagesAmount; i++)
//	{
//		Mat img = imread(segmentImagesPath[i], IMREAD_GRAYSCALE);
//		vector<KeyPoint> kp = a.getKeypoints(img, 12);
//		Mat des = a.getDescriptors(img, kp);
//		des = des.reshape(0, 1); //reshape to single row
//		cout << segmentImagesPath[i] << ": " << m.machine->predict(des) << endl;
//	}
//
//	//VideoCapture capture("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\Video_2.mp4");
//	//Mat frame;
//	//const int divFactor = 3;
//	//while (true)
//	//{
//	//	capture >> frame;
//	//	if (frame.empty()) break;
//	//	//resize the input frame a bit
//	//	resize(frame, frame, Size(1920 / divFactor, 1080 / divFactor));
//	//	Mat img; //the 'working' matrix, the frame should preferrably be left untouched
//	//	frame.copyTo(img);
//	//	vector<Rect> rects = a.segment(frame);
//	//	for (Rect rect : rects)
//	//	{
//	//		//draw each rectangle
//	//		vector<KeyPoint> kp = a.getKeypoints(frame(rect), 12);
//	//		Mat des = a.getDescriptors(img, kp);
//	//		des = des.reshape(0, 1); //reshape to single row
//	//		if (m.machine->predict(des) == 1)
//	//		{
//	//			rectangle(img, rect.tl(), rect.br(), Scalar(0, 255, 0));
//	//		}
//	//		else
//	//		{
//	//			rectangle(img, rect.tl(), rect.br(), Scalar(0, 0, 255));
//	//		}
//	//	}
//	//	imshow("video", img);
//	//	if (waitKey(1) == 27) break;
//	//}
//
//	return 0;
//}