////  main.cpp
////  ANPR
////  Created by Morteza Chalabi on 16/04/16.
////  Copyright © 2016 Southern Unoversity of Denmark. All rights reserved.
////
//
////most frequent C++ header files: not all are used here
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <thread>
//#include <functional>
//#include <mutex>
//#include <atomic>
//
////most frequent C header files: not all are used here
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//
////OpenCV batch header files
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>
//
////namespace in C++ is like package name in Java
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//
////Enter the alpha value [1.0-3.0]
////Enter the beta value [0-100]
//void myContrastBrightness(Mat&, double, int);
//
//int main()
//{
//	//STEP 1: loading image
//	for (int iii = 1; iii <= 101; iii++){
//		cout << iii << endl;
//		Mat org_img = imread("C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\2\\1 (" + to_string(iii) + ").jpg", IMREAD_COLOR);         //reading in image as a 3 channel (3 bytes) BGR one
//
//		if (org_img.empty())                                         //making sure image contains data
//		{
//			cout << "Could not open or find the image" << endl;
//			//return -1;
//		}
//
//		//imshow("Original image, press any key to continue!", org_img);
//		//waitKey(0);
//		//cvDestroyWindow("Original image, press any key to continue!");
//
//		//STEP 2: fltering/smoothing image to reduce noise
//
//		Mat img;
//		bilateralFilter(org_img, img, 21, 21 * 2, 21 / 2);                 //setting diameter, sigma color and sigma space to their recommended values
//
//		//imshow("Bilateral filter, press any key to continue!", img);
//		//waitKey(0);
//		//cvDestroyWindow("Bilateral filter, press any key to continue!");
//
//		//STEP 3: converting BGR to gray scale
//
//		cvtColor(img, img, CV_BGR2GRAY, 1);                             //converting BGR 3 channel iamge to single gray channel one
//
//		//imshow("Gray image, press any key to continue!", img);
//		//waitKey(0);
//		//cvDestroyWindow("Gray image, press any key to continue!");
//
//		//STEP 4: converting gray image to binary (black & white) one
//
//		threshold(img, img, 128, 255, THRESH_BINARY);
//		//imshow("Binary image, press any key to continue!", img);
//		//waitKey(0);
//		//cvDestroyWindow("Binary image, press any key to continue!");
//
//		//STEP 5: transforming iamge to remove holes
//
//		Mat elm = getStructuringElement(MORPH_RECT, Size(4, 4));         //setting kernel size to these values is by trial and error
//		morphologyEx(img, img, MORPH_CLOSE, elm);                      //tends to remove black holes;
//																	   //this is because digits in number plate are black and we are looking for plate
//		//imshow("Morphology close operation, press any key to continue!", img);
//		//waitKey(0);
//		//cvDestroyWindow("Morphology close operation, press any key to continue!");
//
//		//STEP 6: finding contours
//
//		vector<vector<Point>> contours;
//		vector<Vec4i> hierarchy;
//		findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//		//STEP 7: draw contours
//
//		Mat contour_img = org_img.clone();
//		drawContours(contour_img, contours, -1, Scalar(0, 0, 255), 2);
//
//		//imshow("Contours, press any key to continue", contour_img);
//		//waitKey(0);
//		//cvDestroyWindow("Contours, press any key to continue");
//
//		//STEP 8: fiting a rectangle around a contour
//
//		vector<Rect> boundRects;
//		for (short i = 0; i < contours.size(); i++)
//			if (contours[i].size() >= 20)                                      //setting this cutoff for contour area is by trial and error. You could also set an upper bound like <= 50!
//				boundRects.push_back(boundingRect(Mat(contours[i])));
//
//		//STEP 9: drawing rectangles around contours
//
//		short i = 0;
//		for (Rect rect : boundRects)
//		{
//			Mat rect_img = org_img.clone();
//			rectangle(rect_img, rect.tl(), rect.br(), Scalar(255, 0, 0), 2);
//
//			imwrite(string("imagesMM\\object") + to_string(iii) + "_" + to_string(i) + string(".png"), org_img(rect));
//
//			//imshow("Rectangles, press any key to continue", rect_img);
//			//waitKey(0);
//
//			i++;
//		}
//		//cvDestroyWindow("Rectangles, press any key to continue");
//
//		////STEP 10: increasing contrast and brightness of image is a goodidea for finding key points at least in number plate area!
//
//		//myContrastBrightness(org_img, 2, 0);
//
//		//imshow("Increased contrast and brightness, press any key to continue", org_img);
//		////waitKey(0);
//		//cvDestroyWindow("Increased contrast and brightness, press any key to continue");
//
//
//		////STEP 11: finding keypoints
//
//		//Ptr<SURF> detector = SURF::create(400, 4, 3, false, false);           //setting Hessian threshold to 300-500 is recommended, 64-bit descriptor is requested!
//		//vector<vector<KeyPoint>> vect_keypoints(boundRects.size());
//		//i = 0;
//		//for (Rect& rect : boundRects)
//		//{
//		//	detector->detect(org_img(rect), vect_keypoints[i]);
//		//	i++;
//		//}
//
//		////STEP 12: for each rectangle image: filtering out bad key points keeping only 15 good key points
//
//		//for (short i = 0; i < vect_keypoints.size();)
//		//{
//		//	if (vect_keypoints[i].size() >= 15)                               //this cutoff value is by error and trial
//		//	{
//		//		vect_keypoints[i].erase(vect_keypoints[i].begin() + 15, vect_keypoints[i].end());
//		//		i++;
//		//	}
//		//	else
//		//	{
//		//		vect_keypoints.erase(vect_keypoints.begin() + i);
//		//		boundRects.erase(boundRects.begin() + i);
//		//	}
//		//}
//
//		////STEP 13: Draw keypoints
//
//		//vector<Mat> keypoint_imgs(vect_keypoints.size());
//		//for (short i = 0; i < vect_keypoints.size(); i++)
//		//	drawKeypoints(org_img(boundRects[i]), vect_keypoints[i], keypoint_imgs[i], Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);
//
//		//for (Mat& kyp_img : keypoint_imgs)
//		//{
//		//	imshow("Keypoints, press a key to continue!", kyp_img);
//		//	//waitKey(0);
//		//}
//		//cvDestroyWindow("Keypoints, press a key to continue!");
//
//		////STEP 14: finding keypoint descriptors
//
//		//vector<Mat> vect_descriptors;
//		//detector->compute(keypoint_imgs, vect_keypoints, vect_descriptors);
//
//		////STEP 15: for each rectangle image: writing key point descriptors into a file
//
//		//ofstream w;
//		//i = 0;
//		//for (Mat& descs : vect_descriptors)
//		//{
//		//	w.open(string("descriptors") + to_string(i) + string(".txt"));
//
//		//	for (unsigned row = 0; row < descs.rows; row++)
//		//	{
//		//		for (unsigned col = 0; col < descs.cols; col++)
//		//			w << descs.at<float>(row, col) << "\t";
//
//		//		w << endl;
//		//	}
//		//	i++;
//		//	w.close();
//		//}
//	}
//	return 0;                                                      //conventionally 0 means successfull exit, 1 otherwise
//}
//
//
////Enter the alpha value [1.0-3.0]
////Enter the beta value [0-100]
////read more on http://goo.gl/8sjB3d
//void myContrastBrightness(Mat& image, double alpha, int beta)
//{
//	for (int y = 0; y < image.rows; y++)
//		for (int x = 0; x < image.cols; x++)
//			for (int c = 0; c < 3; c++)
//				image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//}