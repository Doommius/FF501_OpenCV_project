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

/* maybe helpful:
https://gilscvblog.com/2013/08/18/a-short-introduction-to-descriptors/ */

/*search 'del' to find stuff to delete (code used for bug testing)*/

/* Questions:
How to limit the number of features? 
-because you find a varying amount of features per picture, the descriptors are not the same length */

/* Function headers */
//void trainCreateFile(int start, int stop);
void trainCreateMem(int start, int stop);
void machine();

/* where the contours are located */
string dir1 = "images\\";

/* number of contour files created in task2 */
const int numOfContours = 6;
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

int labels[numOfContours];
/* if i knew the amuount of features found it would be num_features*/
int num_features = 5;
int img_area = 64 * num_features;
Mat training_mat(numOfContours, img_area, CV_32FC1);

void trainCreateMem(int start, int stop) {
	/* images that are numberplates */
	int posPlate[] = { 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 };

	for (int i = start; i < stop; ++i) {
		string path = dir1 + std::to_string(i) + ".jpg";
		Mat img_1 = imread(path, IMREAD_GRAYSCALE);
		if (!img_1.data) {
			cout << " --(!) Error reading image " << path << endl;
		}
		int minHessian = 10000;

		Ptr<SURF> detector = SURF::create(minHessian);
		vector<KeyPoint> keypoints_1;

		Mat descriptor_1;
		detector->detect(img_1, keypoints_1);

		//del 
		int si = keypoints_1.size();
		myfile << i << ".jpg:  \t amount of keypoints = " << si << "\n";

		detector->compute(img_1, keypoints_1, descriptor_1);

		//http://stackoverflow.com/questions/14694810/using-opencv-and-svm-with-images
		int ii = 0; // Current column in training_mat
		for (int u = 0; u<descriptor_1.rows; u++) {
			for (int j = 0; j < descriptor_1.cols; j++) {
				cout << "u = " << u << ", j = " << j << ", i = " << i << ", ii = " << ii 
					/*<< ", descriptor_1.rows = " << descriptor_1.rows << ", descriptor_1.cols = " << descriptor_1.cols */
					<< endl;
				training_mat.at<float>(i, ii++) = descriptor_1.at<float>(u, j);
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

Mat predictResults;

void machine() {	//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html

	Mat labelsMat(numOfContours, 1, CV_32SC1, labels);
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(training_mat, ROW_SAMPLE, labelsMat);

	//del
	//why does this give false?
	myfile << "train?: " << svm->isTrained() << "\n";

	//myfile << training_mat << "\n";
	myfile << "row: " << training_mat.rows << "\n";
	myfile << "col: " << training_mat.cols << " => 64*numOfFeaturePoints\n";

	//svm->save("mySVM.xml");

	/* even if I try to save an empty svm, it doesn't seem to work */
	/*Ptr<SVM> svm1 = SVM::create();
	svm1->save("mySVM.xml");*/
}