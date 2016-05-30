// most frequent C++ header files : not all are used here
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <functional>
#include <mutex>
#include <atomic>

//most frequent C header files: not all are used here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//OpenCV batch header files
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

//namespace in C++ is like package name in Java
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

class ANPR
{
public:
	ANPR();
	~ANPR();
	Ptr<SURF> fd;
	vector<Rect> segment(Mat);
	vector<Mat> segmentLetters(Mat input);
	vector<KeyPoint> getKeypoints(Mat, int);
	Mat getDescriptors(Mat, vector<KeyPoint>);
	void processImages();
	//void exportTrainFile(vector<)
};

