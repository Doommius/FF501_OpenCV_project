#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat srcRef; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
Mat maskRef;
string contourDir = "C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\contours\\";
string dir = "C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\";
int filesNum = 12;

/// Function header
void srcContour();
void srcRefContour();

int main(){
	srcRef = imread(dir+"\\reference.jpg");
	cvtColor(srcRef, srcRef, CV_BGR2GRAY);
	srcRefContour();
	for (int j = 1; j <= filesNum; j++) {
		//string url = dir +"1\\1 ("+ std::to_string(j) + ").JPG";
		string url = dir + std::to_string(j) + ".JPG";
		cout << url << endl;
		src = imread(url);
		cvtColor(src, src_gray, CV_BGR2GRAY);
		//char* source_window = "Source";
		//namedWindow(source_window, CV_WINDOW_AUTOSIZE);
		//imshow(source_window, src);

		srcContour();
		waitKey(1);
	}
	return(0);
}

void srcRefContour() {
	Canny(srcRef, srcRef, 100, 200);
	vector< vector<Point> > contoursRef;
	findContours(srcRef, contoursRef, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	maskRef = Mat::zeros(srcRef.rows, srcRef.cols, CV_8UC1);
	drawContours(maskRef, contoursRef, 0, Scalar(255), CV_FILLED);

	//imshow("df", maskRef);
}

void srcContour(){
	Mat canny_output;
	vector<vector<Point> > contours;
	//vector<Vec4i> hierarchy;

	/*with blur*/
	//GaussianBlur(src_gray, canny_output, Size(7, 7), 1.5, 1.5);
	//Canny(canny_output, canny_output, thresh, thresh * 2, 3);

	/*without blur*/
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);

	/*CV_RETR_CCOMP retrieves all of the contours and organizes them into a two-level hierarchy. At the top level, there are external boundaries of the components. 
	At the second level, there are boundaries of the holes. If there is another contour inside a hole of a connected component, it is still put at the top level.
	CV_RETR_TREE retrieves all of the contours and reconstructs a full hierarchy of nested contours.*/
	findContours(canny_output, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	double smallest = 200;
	Mat contourRegionSmall;
	for (int i = 0; i < contours.size(); i++) {
		Rect roi = boundingRect(contours[i]);
		
		// Create a mask for each contour to mask out that region from image.
		Mat mask = Mat::zeros(src_gray.size(), CV_8UC1);
		drawContours(mask, contours, i, Scalar(255), CV_FILLED); 
		Mat contourRegion;
		Mat imageROI;
		src_gray.copyTo(imageROI, mask);
		contourRegion = imageROI(roi);
		
		//http://docs.opencv.org/3.1.0/d5/d45/tutorial_py_contours_more_functions.html#gsc.tab=0
		double match = matchShapes(maskRef, contourRegion, 1, 0.0);
		/*for saving all*/
		//std::string fileName = contourDir + std::to_string(match) + ".jpg";
		//imwrite(fileName, contourRegion);

		/*for saving best match*/
		if (match < 1 && (roi.width > 150 && roi.height > 30)) {
			if (match < smallest) {
				smallest = match;
				contourRegionSmall = contourRegion;
			}
		}
	}
	std::string fileName = contourDir + std::to_string(smallest) + ".jpg";
	imwrite(fileName, contourRegionSmall);
}