//#include <stdio.h>
//#include <iostream>
//#include "opencv2/core.hpp"
//#include "opencv2/features2d.hpp"
//#include "opencv2/xfeatures2d.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <fstream>
//#include <string>
//#include <stdlib.h>
//#include <opencv2/ml.hpp>
//
//using namespace cv;
//using namespace std;
//using namespace cv::xfeatures2d;
//using namespace cv::ml;
//
///* maybe helpful:
//https://gilscvblog.com/2013/08/18/a-short-introduction-to-descriptors/ */
//
///*search 'del' to find stuff to delete (code used for bug testing)*/
//
///* Questions:
//How to limit the number of features? */
//
///* Function headers */
////void trainCreateFile(int start, int stop);
//void trainCreateMem(int start, int stop);
//void machine();
//
///* where the contours are located */
//string dir1 = "C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\ContoursM\\";
//
///* number of contour files created in task2 */
//const int numOfContours = 283;
//ofstream myfile;
//
///** @function main */
//int main(){
//	/* Create train.txt or do it in memory*/	//TODO trainCreateFile() incomplete
//	//trainCreateFile(0, 283);
//
//	//del
//	myfile.open("train.txt");
//
//	trainCreateMem(0, 10);
//
//	/* Start the machine learning! */
//	machine();
//
//	myfile.close();
//	return 0;
//}
//
////void trainCreateFile(int start, int stop) {
////	/* images that are numberplates */
////	int posPlate[] = { 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 };
////	/* Open train.txt */
////	ofstream myfile;
////	myfile.open("train.txt");
////	/* how to write to file: */
////	//	myfile << "Writing this to a file.\n";
////
////	for (int i = 0; i <= numOfContours; ++i) {
////		string path = dir1 + std::to_string(i) + ".jpg";
////		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
////		if (!img_1.data) {
////			cout << " --(!) Error reading image " << path << endl;
////		}
////		int minHessian = 400;
////		
////		Ptr<SURF> detector = SURF::create(minHessian);
////		vector<KeyPoint> keypoints_1;
////		Mat descriptor_1;
////		detector->detect(img_1, keypoints_1);
////		//SurfDescriptorExtractor detector(20);
////		detector->compute(img_1, keypoints_1, descriptor_1);
////		cout << descriptor_1.total() << endl;
////		waitKey(0);
////		// check if i is in posPlate (if image is numberplate)	http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
////		if (find(begin(posPlate), end(posPlate), i) != end(posPlate)) {
////			myfile << descriptor_1 << ", [1]\n";
////		}
////		else {
////			myfile << descriptor_1 << ", [0]\n";
////		}
////
////		/* -- Draw keypoints */
////		Mat img_keypoints_1;
////		drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
////		/* -- Show detected (drawn) keypoints */
////		imshow("Keypoints 1", img_keypoints_1);
////	}
////
////	/* close train.txt */
////	myfile.close();
////}
//
//const int num_files = 2;
////int labels[numOfContours];
//int labels[num_files];
//int img_area = 64*4;
//Mat training_mat(num_files, img_area, CV_32FC1);
//
//void trainCreateMem(int start, int stop) {
//	/* images that are numberplates */
//	int posPlate[] = { 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 };
//	int k = -1;
//
//	for (int i = start; i <= stop; ++i) {
//
//		if (i == 1 || i == 8 /*|| i == 9*/) {
//			k++;
//			string path = dir1 + std::to_string(i) + ".jpg";
//			Mat img_1 = imread(path, IMREAD_GRAYSCALE);
//			if (!img_1.data) {
//				cout << " --(!) Error reading image " << path << endl;
//			}
//			int minHessian = 1000;
//
//			Ptr<SURF> detector = SURF::create(minHessian);
//			vector<KeyPoint> keypoints_1;
//
//			Mat descriptor_1;
//			detector->detect(img_1, keypoints_1);
//
//			//del 
//			//int si = keypoints_1.size();
//			//myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";
//
//			detector->compute(img_1, keypoints_1, descriptor_1);
//
//			//del
//			//myfile << descriptor_1 << "\n";
//
//			//http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
//			//Mat img_mat;
//			//int ii = 0; // Current column in training_mat
//			//for (int u = 0; u<img_mat.rows; u++) {
//			//	for (int j = 0; j < img_mat.cols; j++) {
//			//		training_mat.at<float>(i, ii++) = img_mat.at<uchar>(u, j);
//			//	}
//			//}
//
//			int ii = 0; // Current column in training_mat
//			for (int u = 0; u<descriptor_1.rows; u++) {
//				for (int j = 0; j < descriptor_1.cols; j++) {
//					//cout << "u = " << u << ", j = " << j << ", i = " << k << ", ii = " << ii << ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols << endl;
//					training_mat.at<float>(k, ii++) = descriptor_1.at<float>(u, j);
//				}
//			}
//
//			//del
//			//myfile << "training_mat: " << descriptor_1 << "\n";
//
//			// check if i is in posPlate (if image is numberplate)	http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
//			if (find(begin(posPlate), end(posPlate), i) != end(posPlate)) {
//				//myfile << descriptor_1 << ", [1]\n";
//				labels[k] = 1;
//			}
//			else {
//				//myfile << descriptor_1 << ", [0]\n";
//				labels[k] = 0;
//			}
//		}
//	}
//}
//
//Mat predictResults;
//
//void machine() {	//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html
//	//change this!!! (3)
//
//	//del
//	myfile << "ma labels: " << (sizeof(labels) / sizeof(*labels)) << "\n";
//	Mat labelsMat(num_files, 1, CV_32SC1, labels);
//	Ptr<SVM> svm = SVM::create();
//	svm->setType(SVM::C_SVC);
//	svm->setKernel(SVM::LINEAR);
//	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	svm->train(training_mat, ROW_SAMPLE, labelsMat);
//	
//	//del
//	myfile << "train?: " << svm->isTrained() << "\n";
//	myfile << "row: " << training_mat.rows << "\n";
//	myfile << "col: " << training_mat.cols << "\n";
//
//	//svm->save("mySVM.xml");
//	
//	/* even if I */
//	/*Ptr<SVM> svm1 = SVM::create();
//	svm1->save("mySVM.xml");*/
//}