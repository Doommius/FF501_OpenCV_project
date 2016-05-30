//most frequent C++ header files: not all are used here
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <functional>
#include <mutex>
#include <atomic>

//for sleep
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>

//most frequent C header files: not all are used here if
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//OpenCV batch header files
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <Mort.h>
#include <ANPR.h>
#include <MySVM.h>
#include <ImageLocations.h>

//namespace in C++ is like package name in Java
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

ofstream myFile;
/* Number of letter pictures */
const int numberOfLetterPics = 95;

/* Temporary classification */
int eight[] = { 3, 5, 21, 74, 84, 85 };

int main(int argc, const char * argv[]){
	myFile.open("train.txt");
	ANPR a;
	MySVM m;
	m.create();
	int fileName = 0;
	Mat trainingLetters;
	Mat labels(0, 1, CV_32SC1);

	/* Number plate images path */
	String path = "C:\\Users\\zlyza\\Source\\Repos\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\Projects\\OpenCV\\OpenCVX\\imagesMM\\1 (";
	for (int i = 0; i < 11; i++){
		String p = path + to_string(i) + ").png";
		cout << p << endl;
		Mat img = imread(p, IMREAD_GRAYSCALE);
		if (img.empty()) {
			cout << "Could not open or find the image " << img << endl;
			Sleep(1000);
			//continue;
			return -1;
		}
		vector<Mat> mats = a.segmentLetters(img);
		
		for (Mat mat : mats) {
			//myFile << mat.size() << endl;
			resize(mat, mat, Size(20, 30), 0, 0, INTER_NEAREST);
			imwrite("Letters\\1 (" + to_string(fileName) + ").png", mat);
			Mat singleRow = mat.clone().reshape(0, 1);
			/* Train file Morteza wanted */
			myFile << singleRow << endl;
			trainingLetters.push_back(singleRow);

			/* Create Labels */
			if (find(begin(eight), end(eight), fileName) != end(eight)) {
				labels.push_back(1);
				//labels.at<int>(fileName) = 1;
			} else {
				labels.push_back(0);
				//labels.at<int>(fileName) = 0;
			}
			fileName++;
		}
	}
	/* Change Mat type to what SVM wants */
	trainingLetters.convertTo(trainingLetters, CV_32FC1);

	Ptr<TrainData> t = TrainData::create(trainingLetters, ROW_SAMPLE, labels);
	cout << "trainAuto: " << m.machine->trainAuto(t, 10, SVM::getDefaultGrid(SVM::C),
		SVM::getDefaultGrid(SVM::GAMMA),
		SVM::getDefaultGrid(SVM::P),
		SVM::getDefaultGrid(SVM::NU),
		SVM::getDefaultGrid(SVM::COEF),
		SVM::getDefaultGrid(SVM::DEGREE), false) << endl;

	//m.machine->save("trainedLettersSVM.xml");

	/* test the SVM */	// a lot easier to compare 'labels' and 'results' Mats in Image Watch
	/*for (int i = 0; i < numberOfLetterPics; i++)
	{
		String p = path + to_string(i) + ").png";
		cout << p << ": " << m.machine->predict(trainingLetters.row(i)) << endl;
	}*/

	/* calc error rate */ //don't think this works
	Mat results;
	//cout << "Error: " << m.machine->calcError(t, true, results) << endl;
	/* or */
	m.machine->predict(trainingLetters, results);

	/* Test numbers i edited so it is not the same as training data */
	//String path1 = "C:\\Users\\zlyza\\Source\\Repos\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\Projects\\OpenCV\\OpenCVX\\Letters\\Edited_8\\1 (";
	//Mat trainingL;
	//for (int i = 0; i <= 5; i++) {
	//	String p = path1 + to_string(i) + ").png";
	//	cout << p << endl;
	//	Mat img = imread(p, IMREAD_GRAYSCALE);
	//	if (img.empty()) {
	//		cout << "Could not open or find the image " << img << endl;
	//		Sleep(1000);
	//		//continue;
	//		//return -1;
	//	}
	//	Mat singleRow = img.clone().reshape(0, 1);
	//	trainingL.push_back(singleRow);
	//}
	//trainingL.convertTo(trainingL, CV_32FC1);
	//Mat resultsEdited;
	//m.machine->predict(trainingL, resultsEdited);

	myFile.close();
}