#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
using namespace cv::ml;

/* links in the text:
http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html
*/

/*search 'del' to find stuff to delete (code used for bug testing)*/

/* Function headers */
void trainCreateMem(int start, int stop);
void testCreateMem(int start, int stop);
void machine();

/* where the contours are located */
string dir1 = "images\\";

/* number of contour files created in task2 */
/*train*/
const int numOfContours = 10;
int labels[numOfContours];
int num_features = 8;
int img_area = 64 * num_features;
Mat training_mat(numOfContours, img_area, CV_32FC1);

ofstream myfile;

/** @function main */
int main() {
	myfile.open("train.txt");	//currently used for debugging

	trainCreateMem(0, numOfContours);
	/* Start the machine learning! */
	machine();

	myfile.close();
	return 0;
}

/*test*/		//{ 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 }
int testStart = 12;
int testStop = 40;
int numOfContoursTest = testStop-testStart;
Mat test_mat(numOfContoursTest, img_area, CV_32FC1);

/* start has to be 0*/
void trainCreateMem(int start, int stop) {
	/* images that are numberplates */
	int posPlate[] = { 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 };
	int k = -1;
	for (int i = start; i < stop; ++i) {
		k++;
		string path = dir1 + std::to_string(i) + ".jpg";
		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
		if (!img_1.data) {
			cout << " --(!) Error reading image " << path << endl;
		}
		int minHessian = 500;

		Ptr<SURF> detector = SURF::create(minHessian);
		//Ptr<FeatureDetector> detector(new DynamicAdaptedFeatureDetector (100, 110, 10, new FastAdjuster(20,true)));

		vector<KeyPoint> keypoints_1;

		Mat descriptor_1;
		detector->detect(img_1, keypoints_1);
		KeyPointsFilter::retainBest(keypoints_1, num_features);
		//del
		int si = keypoints_1.size();
		/*while (si < num_features) {
			keypoints_1.push_back();
		}*/
		//myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";

		detector->compute(img_1, keypoints_1, descriptor_1);
		//myfile << descriptor_1 << "\n";
		//myfile << "row = " << descriptor_1.rows << ", col = " << descriptor_1.cols << "\n";
		//http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
		int ii = 0; // Current column in training_mat
		for (int u = 0; u<descriptor_1.rows; u++) {
			for (int j = 0; j < descriptor_1.cols; j++) {
				//cout << "u = " << u << ", j = " << j << ", i = " << i << ", ii = " << ii /*<< ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols */<< endl;
				training_mat.at<float>(k, ii++) = descriptor_1.at<float>(u, j);
			}
		}

		// check if i is in posPlate (if image is numberplate)	http://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
		if (find(begin(posPlate), end(posPlate), i) != end(posPlate)) {
			labels[i] = 1;
		}
		else {
			labels[i] = 0;
		}
	}
}

void testCreateMem(int start, int stop) {
	int k = -1;
	for (int i = start; i < stop; ++i) {
		k++;
		string path = dir1 + std::to_string(i) + ".jpg";
		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
		if (!img_1.data) {
			cout << " --(!) Error reading image " << path << endl;
		}
		int minHessian = 500;

		Ptr<SURF> detector = SURF::create(minHessian);

		vector<KeyPoint> keypoints_1;

		Mat descriptor_1;
		detector->detect(img_1, keypoints_1);
		KeyPointsFilter::retainBest(keypoints_1, num_features);
		//del
		int si = keypoints_1.size();
		//myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";

		detector->compute(img_1, keypoints_1, descriptor_1);
		//myfile << descriptor_1 << "\n";
		//myfile << "row = " << descriptor_1.rows << ", col = " << descriptor_1.cols << "\n";
		int ii = 0; // Current column in training_mat
		for (int u = 0; u<descriptor_1.rows; u++) {
			for (int j = 0; j < descriptor_1.cols; j++) {
				//cout << "u = " << u << ", j = " << j << ", i = " << i << ", ii = " << ii /*<< ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols */<< endl;
				test_mat.at<float>(k, ii++) = descriptor_1.at<float>(u, j);
			}
		}
	}
}

Mat predictResults;

void machine() {	//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html

	Mat labelsMat(numOfContours, 1, CV_32SC1, labels);
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(training_mat, ROW_SAMPLE, labelsMat);

	//myfile << "train?: " << svm->isTrained() << "\n";
	//myfile << training_mat << "\n";
	//myfile << "row: " << training_mat.rows << "\n";
	//myfile << "col: " << training_mat.cols << " => 64*numOfFeaturePoints\n";

	/*this does not work :(*/
	//svm->save("mySVM.xml");

	/*try to predict*/
	testCreateMem(testStart, testStop);
	Mat results;
	svm->predict(test_mat, results);
	myfile << results << "\n";
}