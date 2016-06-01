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
//int zero[] = { 23, 94 };
//int one[] = { 12, 30, 66 };
//int two[] = { 14, 22, 39, 48, 62, 92, 93 };
//int three[] = { 24, 31, 40, 49, 51 };
//int four[] = { 6, 26, 59, 60 };
//int five[] = { 11, 29, 58, 61, 65, 76, 86 };
//int six[] = { 37, 38, 91 };
//int seven[] = { 13, 50, 70 };
//int eight[] = { 3, 5, 21, 74, 84, 85 };
//int nine[] = { 4, 73, 75, 87 };


int main(int argc, const char * argv[]){
	myFile.open("train.txt");
	ANPR a;
	MySVM m;
	m.create();
	int fileName = 0;
	Mat trainingLetters;
	Mat labels(0, 1, CV_32SC1);

	/* Number plate images path */
	//String path = "C:\\Users\\zlyza\\Source\\Repos\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\Projects\\OpenCV\\OpenCVX\\imagesMM\\1 (";
	//String path = "C:\\Users\\zlyza\\Source\\Repos\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\Projects\\OpenCV\\OpenCVX\\segments2\\positive\\1 (";
	String trainingLettersPath = "C:\\Users\\zlyza\\Source\\Repos\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\Projects\\OpenCV\\OpenCVX\\LettersDK\\";
	//for (int i = 0; i < 90; i++) {
	//	//String p = path + to_string(i) + ").png";
	//	String p = path + to_string(i * 10) + ").jpg";
	//	cout << p << endl;
	//	Mat img = imread(p, IMREAD_GRAYSCALE);
	//	if (img.empty()) {
	//		cout << "Could not open or find the image " << img << endl;
	//		//Sleep(1000000000);
	//		continue;
	//		//return -1;
	//	}
	//	vector<Mat> mats = a.segmentLetters(img);
	//	for (Mat mat : mats) {
	//		//myFile << mat.size() << endl;
	//		resize(mat, mat, Size(20, 30), 0, 0, INTER_NEAREST);
	//		//imwrite("LettersDK\\1 (" + to_string(fileName) + ").png", mat);
	//		imwrite("report\\1 (" + to_string(fileName) + ").png", mat);
	//		Mat singleRow = mat.clone().reshape(0, 1);
	//		/* Train file Morteza wanted */
	//		myFile << singleRow << endl;
	//		trainingLetters.push_back(singleRow);
	//		/* Create Labels */
	//		//if (find(begin(zero), end(zero), fileName) != end(zero)) {
	//		//	labels.push_back(0);
	//		//	//labels.at<int>(fileName) = 8;
	//		//} else if (find(begin(one), end(one), fileName) != end(one)) {
	//		//	labels.push_back(1);
	//		//} else if (find(begin(two), end(two), fileName) != end(two)) {
	//		//	labels.push_back(2);
	//		//} else if (find(begin(three), end(three), fileName) != end(three)) {
	//		//	labels.push_back(3);
	//		//} else if (find(begin(four), end(four), fileName) != end(four)) {
	//		//	labels.push_back(4);
	//		//} else if (find(begin(five), end(five), fileName) != end(five)) {
	//		//	labels.push_back(5);
	//		//} else if (find(begin(six), end(six), fileName) != end(six)) {
	//		//	labels.push_back(6);
	//		//} else if (find(begin(seven), end(seven), fileName) != end(seven)) {
	//		//	labels.push_back(7);
	//		//} else if (find(begin(eight), end(eight), fileName) != end(eight)) {
	//		//	labels.push_back(8);
	//		//} else if (find(begin(nine), end(nine), fileName) != end(nine)) {
	//		//	labels.push_back(9);
	//		//} else {
	//		//	labels.push_back(-1);
	//		//}
	//		fileName++;
	//	}
	//}

	/* when training data is classified in folders */
	string folderReal[] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f","g","j","p","r","v","w","x","z_garbage" };
	int folder[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,-1 };
	for (int i = 0; i < (sizeof(folder)/sizeof(*folder)); i++){
		for (int j = 1; j < 15; j++) {
			String p = trainingLettersPath + folderReal[i] + "\\1 (" + to_string(j) + ").png";
			//cout << p << endl;
			Mat img = imread(p, IMREAD_GRAYSCALE);
			if (img.empty()) {
				cout << "Could not open or find the image " << img << endl;
				//Sleep(1000000000);
				continue;
				//return -1;
			}
			Mat singleRow = img.clone().reshape(0, 1);
			trainingLetters.push_back(singleRow);

			/* Create Labels */
			labels.push_back(folder[i]);
		}
	}
	/* Change Mat type to what SVM wants */
	trainingLetters.convertTo(trainingLetters, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);

	Ptr<TrainData> t = TrainData::create(trainingLetters, ROW_SAMPLE, labels);
	m.machine->train(t);
	/*cout << "trainAuto: " << m.machine->trainAuto(t, 10, SVM::getDefaultGrid(SVM::C),
		SVM::getDefaultGrid(SVM::GAMMA),
		SVM::getDefaultGrid(SVM::P),
		SVM::getDefaultGrid(SVM::NU),
		SVM::getDefaultGrid(SVM::COEF),
		SVM::getDefaultGrid(SVM::DEGREE), false) << endl;*/

	m.machine->save("trainedLettersSVM.xml");
	cout << "train?: " << m.machine->isTrained() << "\n";
	//	 << endl;
	/* test the SVM */	// a lot easier to compare 'labels' and 'results' Mats in Image Watch
	/*for (int i = 0; i < numberOfLetterPics; i++)
	{
		String p = path + to_string(i) + ").png";
		cout << p << ": " << m.machine->predict(trainingLetters.row(i)) << endl;
	}*/

	/* calc error rate */ //don't think this works
	//Mat results;
	////cout << "Error: " << m.machine->calcError(t, true, results) << endl;
	///* or */
	//m.machine->predict(trainingLetters, results);
	//results.convertTo(results, CV_32SC1);
	//labels.convertTo(labels, CV_32SC1);
	////trainingLetters.convertTo(trainingLetters, CV_32FC1);
	//int correctResults = 0;
	////http://stackoverflow.com/questions/8377091/what-are-the-differences-between-cv-8u-and-cv-32f-and-what-should-i-worry-about
	//for (int j = 0; j < results.rows; j++) {
	//	//cout << results.cols << endl;
	//	//cout << results.rows << endl;
	//	//cout << "results: " << results.at<int>(j) << "\tlabels: " << labels.at<int>(j) << endl;
	//	if (results.at<int>(j) == labels.at<int>(j)) {
	//		correctResults++;
	//	}
	//}
	//cout << correctResults << "/" << results.rows << " are correct!" << endl;

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

	//Mat testLetters;
	string path = "segments2\\positive\\1 (";
	for (int i = 0; i < 180; i++) {
		String p = path + to_string(i * 5+1) + ").jpg";
		cout << p << endl;
		Mat img = imread(p, IMREAD_GRAYSCALE);
		if (img.empty()) {
			cout << "Could not open or find the image " << img << endl;
			//Sleep(1000000000);
			continue;
		}
		vector<Mat> mats = a.segmentLetters(img);
		Mat testLetters;
		for (Mat mat : mats) {
			resize(mat, mat, Size(20, 30), 0, 0, INTER_NEAREST);
			imshow("mat", mat);
			Mat singleRow = mat.clone().reshape(0, 1);
			singleRow.convertTo(singleRow, CV_32FC1);
			testLetters.push_back(singleRow);
		}
		Mat testResult;
		m.machine->predict(testLetters, testResult);
		string plate = "";
		for (int k = 0; k < testResult.rows; k++) {
			float pre = testResult.at<float>(k, 0);
			int n = static_cast<int>(pre);
			cout << pre << n << endl;
			if (n != -1) {
				plate += folderReal[n];
			}
		}
		//imwrite("report\\test\\" + to_string(fileName) + "_" + plate + ".png", img);
		//imwrite("report\\test\\"+ plate + ".png", img);
		fileName++;
	}
	//testLetters.convertTo(testLetters, CV_32FC1);
	//Mat testResult;
	//m.machine->predict(testLetters, testResult);

	Mat outtt;
	//cout << m.machine->calcError(t, true, outtt) << endl;
	/*int correctResults = 0;
	for (int j = 0; j < testResult.rows; j++) {
		if (testResult.at<int>(j) == labels.at<int>(j)) {
			correctResults++;
		}
	}
	cout << correctResults << "/" << testResult.rows << " are correct!" << endl;*/
	Sleep(1000000000);
	myFile.close();
}