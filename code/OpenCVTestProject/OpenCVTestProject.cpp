//most frequent C++ header files: not all are used here
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

#include <Mort.h>
#include <ANPR.h>

//namespace in C++ is like package name in Java
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

std::string testImages[] = {
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\DSC_0566.jpg",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\2715DTZ.jpg",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\3028BYS.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\3154FFY.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\3266CNT.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\3732FWW.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\5445BSX.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\7215BGN.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\8995CCN.JPG",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\9588DWV.jpg",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\9773BNB.jpg",
	"C:\\Users\\mikke_000\\Dropbox\\SDU\\FF501\\repo\\Automatic-Vehicle-Ticketing-System-Using-Computer-Vision-Techniques\\code\\images\\DSC_0562.jpg"
};

int main(int argc, const char * argv[])
{
	//Mort m;
	//m.OWN();

	Mat image = imread(testImages[0]);
	ANPR a;

	for (Mat segment : a.segment(image))
	{
		imshow("segment", segment);
		waitKey(0);
	}
}