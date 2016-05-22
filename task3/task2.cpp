#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv;




	RNG rng(12345);

	const char* winName = "Image";
	const char* trackbarName = "Image index";
	string images[] = { "2715DTZ.jpg", "3028BYS.JPG", "3154FFY.JPG",
					   "3266CNT.JPG", "3732FWW.JPG", "5445BSX.JPG",
					   "7215BGN.JPG", "8995CCN.JPG", "9588DWV.jpg",
					   "9773BNB.jpg", "DSC_0562.jpg", "DSC_0566.jpg" };
	const int imagesAmount = 12;
	Mat image[imagesAmount];
	Mat reference;

	int index = 0;
	int cannyThreshold = 80;
	int blurAmount = 3;
	int fastThreshold = 0;

	void onTrackbar(int, void*)
	{
		Mat w, wg, wb, mask, dst; //working matrix, working gray matrix, working binary matrix
		image[index].copyTo(w);

		//edges
		cvtColor(w, wg, CV_BGR2GRAY);
		GaussianBlur(wg, wg, Size(1 + 2 * blurAmount, 1 + 2 * blurAmount), 1.5);
		Canny(wg, wb, cannyThreshold, cannyThreshold * 3);

		//contours
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(wb, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		int saveIndex = 0;
		image[index].copyTo(dst);
		for (int i = 0; i < 1; ++i)
		{
			vector<Point> p = contours[i];

			double perimeter = arcLength(p, true);
			//approximate
			approxPolyDP(p, p, perimeter * 0.002, true);
			RotatedRect rect = minAreaRect(p);

			Mat rotMat = cv::getRotationMatrix2D(rect.center, rect.angle, 1);
			cv::warpAffine(wg, dst, rotMat, dst.size(), cv::INTER_CUBIC);
			
			Mat cropped;
			cv::Size rectSize = rect.size;
			if (rect.angle < -45.) std::swap(rectSize.width, rectSize.height);
			cv::getRectSubPix(dst, rectSize, rect.center, dst);

			if (false) //should draw
			{
				//draw rect
				Point2f verts[4];
				vector<Point> points;
				rect.points(verts);
				for (int j = 0; j < 4; ++j) {
					points.push_back(verts[j]);
					line(dst, verts[j], verts[(j + 1) % 4], Scalar(0, 255, 0));
				}
				//draw poly
				fillConvexPoly(dst, points, Scalar(0, 255, 0, 128));
			}
		}

		//draw features
		/*
		vector<Point2f> corners;
		goodFeaturesToTrack(wg, corners, 0, 0.2, 7);

		for (int k = 0; k < corners.size(); ++k) {
			circle(dst, corners[k], 3, Scalar(0, 0, 255));
		}
		*/

		imshow(winName, dst);
	}

	int main(int argc, char** argv)
	{
		//load all images
		for (int i = 0; i < imagesAmount; ++i) {
			image[i] = imread("images\\" + images[i], CV_LOAD_IMAGE_COLOR);
		}
		reference = imread("reference.jpg");

		namedWindow(winName, WINDOW_FULLSCREEN);
		createTrackbar(trackbarName, winName, &index, imagesAmount - 1, onTrackbar);
		createTrackbar("Threshold", winName, &cannyThreshold, 150, onTrackbar);
		createTrackbar("Blur", winName, &blurAmount, 10, onTrackbar);
		//createTrackbar("FAST", winName, &fastThreshold, 300, onTrackbar);

		//init
		onTrackbar(index, 0);

		waitKey(0);
		return 0;
	}


