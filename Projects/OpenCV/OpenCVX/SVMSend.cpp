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
///* links in the text:
//http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
//http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html
//*/
//
///*search 'del' to find stuff to delete (code used for bug testing)*/
//
///* Function headers */
//void trainCreateMem(int start, int stop);
//void testCreateMem(int start, int stop);
//void machine();
//
///* where the contours are located */
////string dir1 = "imagesM\\1 (";
//string dir1 = "images\\";
//int minHessian = 700;
//
//int num_features = 6;
///*train*/
//const int numOfContours = 40;	//number of files
//int labels[numOfContours];
//int img_area = 64 * num_features;
//Mat training_mat(numOfContours, img_area, CV_32FC1);
//
//ofstream myfile;
//
///** @function main */
//int main() {
//	myfile.open("train.txt");	//currently used for debugging
//
//	trainCreateMem(0, numOfContours);
//	/* Start the machine learning! */
//	machine();
//
//	myfile.close();
//	return 0;
//}
//
///*testMikkel*/		//{ 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 }
///*testMorteza*/		//{ 7, 13, 31, 42, 51, 62, 79, 92, 111, 157 }
///*testMM*/		//{ 4, 14, 24, 48, 59, 69, 87, 99, 127, 152, 167, 169, 182, 189, 220, 238, 249, 272, 282, 296, 349, 357, 367, 372, 394, 416, 424, 434, 446, 454, 475, 485, 502, 529, 543, 564, 581, 597, 619, 634, 647, 665, 691, 706, 712, 721, 747, 762, 768, 784, 796, 807, 830, 860, 876, 899, 918, 936, 988, 1011, 1018, 1038, 1049, 1061, 1143, 1144, 1155, 1168, 1182, 1196, 1201, 1211, 1229, 1238, 1255 }
//int testStart = 41;
//int testStop = 81/*numOfContours*/;
//int numOfContoursTest = testStop-testStart;
//Mat test_mat(numOfContoursTest, img_area, CV_32FC1);
//
///* start has to be 0*/
//void trainCreateMem(int start, int stop) {
//	/* images that are numberplates */
//	int posPlate[] = { 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 };
//	int k = -1;
//	for (int i = start; i < stop; i++) {
//		k++;
//		//string path = dir1 + std::to_string(i) + ").png";
//		string path = dir1 + std::to_string(i) + ".jpg";
//		//cout << path << endl;
//		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
//		if (!img_1.data) {
//			cout << " --(!) Error reading image " << path << endl;
//			myfile << "error reading: " << path << "\n";
//		}
//
//		Ptr<SURF> detector = SURF::create(minHessian, 4, 3, false, false);
//
//		vector<KeyPoint> keypoints_1;
//
//		Mat descriptor_1;
//		detector->detect(img_1, keypoints_1);
//		KeyPointsFilter::retainBest(keypoints_1, num_features);
//		//del
//		//int si = keypoints_1.size();
//		//myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";
//
//		detector->compute(img_1, keypoints_1, descriptor_1);
//		//myfile << descriptor_1 << "\n";
//		//myfile << "row = " << descriptor_1.rows << ", col = " << descriptor_1.cols << "\n";
//		//http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
//		int ii = 0; // Current column in training_mat
//		for (int u = 0; u<descriptor_1.rows; u++) {
//			for (int j = 0; j < descriptor_1.cols; j++) {
//				//cout << "u = " << u << ", j = " << j << ", i = " << i << ", ii = " << ii /*<< ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols */<< endl;
//				training_mat.at<float>(k, ii++) = descriptor_1.at<float>(u, j);
//			}
//		}
//
//		// check if i is in posPlate (if image is numberplate)	http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
//		if (find(begin(posPlate), end(posPlate), i) != end(posPlate)) {
//			labels[i] = 1;
//		}
//		else {
//			labels[i] = 0;
//		}
//	}
//}
//
//void testCreateMem(int start, int stop) {
//	int k = -1;
//	for (int i = start; i < stop; i++) {
//		k++;
//		//string path = dir1 + std::to_string(i) + ").png";
//		string path = dir1 + std::to_string(i) + ".jpg";
//		//cout << path << endl;
//		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
//		if (!img_1.data) {
//			cout << " --(!) Error reading image " << path << endl;
//			myfile << "error reading: " << path << "\n";
//		}
//		
//		Ptr<SURF> detector = SURF::create(minHessian, 4, 3, false, false);
//
//		vector<KeyPoint> keypoints_1;
//
//		Mat descriptor_1;
//		detector->detect(img_1, keypoints_1);
//		KeyPointsFilter::retainBest(keypoints_1, num_features);
//		//del
//		//int si = keypoints_1.size();
//		//myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";
//
//		detector->compute(img_1, keypoints_1, descriptor_1);
//		//myfile << descriptor_1 << "\n";
//		//myfile << "row = " << descriptor_1.rows << ", col = " << descriptor_1.cols << "\n";
//		int ii = 0; // Current column in training_mat
//		for (int u = 0; u<descriptor_1.rows; u++) {
//			for (int j = 0; j < descriptor_1.cols; j++) {
//				//cout << "u = " << u << ", j = " << j << ", i = " << i << ", ii = " << ii /*<< ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols */<< endl;
//				test_mat.at<float>(k, ii++) = descriptor_1.at<float>(u, j);
//			}
//		}
//	}
//}
//
//Mat predictResults;
//
//void machine() {	//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html
//
//	Mat labelsMat(numOfContours, 1, CV_32SC1, labels);
//	Ptr<SVM> svm = SVM::create();
//	//Ptr<SVM> svm = StatModel::load<SVM>("mySVM.xml");
//	svm->setType(SVM::C_SVC);
//	svm->setKernel(SVM::LINEAR);
//	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	svm->train(training_mat, ROW_SAMPLE, labelsMat);
//
//	myfile << "train?: " << svm->isTrained() << "\n";
//	//myfile << "labelsMat = " << labelsMat << endl;
//	myfile << "labelsMat row: " << labelsMat.rows << "\n";
//	//myfile << "labelsMat col: " << labelsMat.cols << "\n";
//	//myfile << training_mat << "\n";
//	//myfile << "row: " << training_mat.rows << "\n";
//	//myfile << "col: " << training_mat.cols << " => 64*numOfFeaturePoints\n";
//
//	//svm->save("mySVM.xml");
//
//	/*try to predict*/
//	testCreateMem(testStart, testStop);
//	Mat results; 
//	svm->predict(test_mat, results);
//
//	double correct = 0;
//	
//	if (results.rows == labelsMat.rows && results.cols == labelsMat.cols) {
//		for (int u = 0; u < labelsMat.rows; u++) {
//			for (int j = 0; j < labelsMat.cols; j++) {
//				if (results.at<float>(u, j) == labelsMat.at<int>(u, j)) {
//					if (labelsMat.at<int>(u, j) == 1) {
//						myfile << results.at<float>(u, j) << " " << labelsMat.at<int>(u, j) << " oh baby! \n";
//					}
//					correct++;
//				}
//				else {
//					myfile << results.at<float>(u, j) << " " << labelsMat.at<int>(u, j) << "\n";
//				}
//			}
//		}
//		myfile << correct << " out of " << numOfContoursTest << "\n";
//		myfile << "The training machine got " << (correct / numOfContoursTest) * 100 << "% correct \n";
//	}
//	else {
//		myfile << "labelsMat and results don't match" << "\n";
//	}
//	myfile << "results row: " << results.rows << "\n";
//	//myfile << "results col: " << results.cols << "\n";
//	//myfile << labelsMat << results << "\n";
//}