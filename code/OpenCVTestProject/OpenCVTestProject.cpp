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



void runVideo()
{
	//Mort m;
	//m.OWN();

	/*Mat image = imread(testImages[0]);
	ANPR a;

	for (Mat segment : a.segment(image))
	{
	imshow("segment", segment);
	waitKey(0);
	}*/

	const int divFactor = 2;

	VideoCapture capture("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\video_2.mp4");
	Mat frame;

	if (!capture.isOpened())
		throw "Error opening file!";

	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH) / divFactor;
	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT) / divFactor;
	//VideoWriter videoOut("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\video_2_canny.avi", CV_FOURCC('M','J','P','G'), 30, Size(frameWidth, frameHeight));

	//namedWindow("video", CV_WINDOW_AUTOSIZE);

	ANPR a;
	int count = 0;
	while (true)
	{
		capture >> frame;

		if (frame.empty()) break;

		//resize the input frame a bit
		resize(frame, frame, Size(1920 / divFactor, 1080 / divFactor));

		//segment the image using our own procedure
		vector<Rect> rects = a.segment(frame);

		//go through each segment
		for (Rect rect : rects)
		{
			//draw each rectangle
			Mat img; //the 'working' matrix, the frame should preferrably be left untouched
			img = frame(rect);
			/*rectangle(img, rect.tl(), rect.br(), Scalar(0, 255, 0));

			//draw the keypoints
			drawKeypoints(img, kp, img, Scalar(0, 0, 255));*/
			//get 12 features from each segment
			cvtColor(img, img, CV_BGR2GRAY);
			equalizeHist(img, img);
			vector<KeyPoint> kp = a.getKeypoints(img, 12);
			if (kp.size() == 12)
			{
				imwrite("..\\images\\segments2\\" + std::to_string(count++) + ".jpg", img);
				cout << count << endl;
			}
		}

		//imshow("video", img);
		//videoOut << frame;
		//if (waitKey(1) == 27) break;
	}
}

int main(int argc, const char * argv[])
{	
	ANPR a;
	MySVM m, ocr;
	bool train = false;
	const int numKeypoints = 20;

	Ptr<TrainData> t;

	if (train)
	{
		Mat samples;
		int posAddedSamples = 0, negAddedSamples = 0;

		//the following two for loops are for incremental images
		for (int i = 1; i <= 1175; i++)
		{
			Mat img = imread("..\\images\\segments2\\positive\\pos (" + to_string(i) + ").jpg", IMREAD_GRAYSCALE);
			vector<KeyPoint> kp = a.getKeypoints(img, numKeypoints);
			if (kp.size() != numKeypoints)
			{
				std::cout << "kp size != numKeypoints for " << "pos: " << i << endl;
				continue;
			}
			Mat des = a.getDescriptors(img, kp);
			des = des.reshape(0, 1); //reshape to single row
			samples.push_back(des); //add to results
			posAddedSamples++;
			std::cout << "pos: " << i << endl;
		}

		for (int i = 1; i <= 1426; i++)
		{
			Mat img = imread("..\\images\\segments2\\neg (" + to_string(i) + ").jpg", IMREAD_GRAYSCALE);
			vector<KeyPoint> kp = a.getKeypoints(img, numKeypoints);
			if (kp.size() != numKeypoints)
			{
				std::cout << "kp size != numKeypoints for " << "neg: " << i << endl;
				continue;
			}
			Mat des = a.getDescriptors(img, kp);
			des = des.reshape(0, 1); //reshape to single row
			samples.push_back(des); //add to results
			negAddedSamples++;
			std::cout << "neg: " << i << endl;
		}


		/*for (int i = 0; i < positivesAmount; i++)
		{
			Mat img = imread(positivesPath[i], IMREAD_GRAYSCALE);
			equalizeHist(img, img);
			vector<KeyPoint> kp = a.getKeypoints(img, numKeypoints);
			if (kp.size() != numKeypoints)
			{
				std::cout << "kp size != numKeypoints for " << "pos: " << i << " = " << positivesPath[i] << endl;
				continue;
			}
			Mat des = a.getDescriptors(img, kp);
			des = des.reshape(0, 1); //reshape to single row
			samples.push_back(des); //add to results
			posAddedSamples++;
			std::cout << "pos: " << i << " = " << positivesPath[i] << endl;
		}

		for (int i = 0; i < negativesAmount; i++)
		{
			Mat img = imread(negativesPath[i], IMREAD_GRAYSCALE);
			equalizeHist(img, img);
			vector<KeyPoint> kp = a.getKeypoints(img, numKeypoints);
			if (kp.size() != numKeypoints)
			{
				std::cout << "kp size != numKeypoints for " << "neg: " << i << " = " << negativesPath[i] << endl;
				continue;
			}
			Mat des = a.getDescriptors(img, kp);
			des = des.reshape(0, 1); //reshape to single row
			samples.push_back(des); //add to results
			negAddedSamples++;
			std::cout << "neg: " << i << " = " << negativesPath[i] << endl;
		}*/

		Mat labels(1, posAddedSamples + negAddedSamples, CV_32S);
		for(int i = 0; i < posAddedSamples; i++)
			labels.at<int>(i) = 1; //is a numberplate
		for (int i = posAddedSamples; i < posAddedSamples + negAddedSamples; i++)
		labels.at<int>(i) = 0; //is not a numberplate
		t = TrainData::create(samples, ROW_SAMPLE, labels);
		
	
		//cout << "trainAuto: " << m.machine->trainAuto(t, 2) << endl;

		bool hyperParameterPlayground = false;
		do
		{
			m.create();
			m.machine->setKernel(SVM::KernelTypes::RBF);
			m.machine->setType(SVM::Types::C_SVC);
			double c = 2.5;
			double gamma = 0.50625;
			m.machine->setC(c);
			m.machine->setGamma(gamma);
			m.machine->train(t);

			cout << "C: " << m.machine->getC() << endl;
			cout << "g: " << m.machine->getGamma() << endl;

			//calc error rate
			Mat out;
			std::cout << "Error: " << m.machine->calcError(t, false, out) << endl;
		} while (hyperParameterPlayground);

		//m.machine->save("detect_SVM.xml");
	}
	else
	{
		m.machine = SVM::create();
		m.machine = SVM::load<SVM>("detect_SVM-20-64.xml");
	}

	ocr.machine = SVM::create();
	ocr.machine = SVM::load<SVM>("trainedLettersSVM.xml");

	//m.machine->save("detect_SVM-20-64.xml");

	std::cout << "Trained: " << m.machine->isTrained();

	//now test the SVM
	/*for (int i = 0; i < segmentImagesAmount; i++)
	{
		Mat img = imread(segmentImagesPath[i], IMREAD_GRAYSCALE);
		equalizeHist(img, img);
		vector<KeyPoint> kp = a.getKeypoints(img, numKeypoints);
		Mat des = a.getDescriptors(img, kp);
		des = des.reshape(0, 1); //reshape to single row
		std::cout << segmentImagesPath[i] << ": " << m.machine->predict(des) << endl;
	}*/
	string folderReal[] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","J","P","R","V","W","X","z_garbage" };
	vector<string> log;
	VideoCapture capture("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\video_3_2.mp4");
	Mat frame;
	const int divFactor = 2;
	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH) / divFactor;
	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT) / divFactor;
	VideoWriter videoOut("C:\\Users\\mikke_000\\Desktop\\Nummerplader - edited\\thing1.avi", CV_FOURCC('M','J','P','G'), 30, Size(frameWidth, frameHeight));
	while (true)
	{
		capture >> frame;

		if (frame.empty()) break;

		//resize the input frame a bit
		resize(frame, frame, Size(1920 / divFactor, 1080 / divFactor));

		Mat img, dest, grayInput; //the 'working' matrix, the frame should preferrably be left untouched
		frame.copyTo(dest);
		cvtColor(frame, img, CV_BGR2GRAY);
		cvtColor(frame, grayInput, CV_BGR2GRAY);
		equalizeHist(img, img);

		vector<Rect> rects = a.segment(frame);

		for (Rect rect : rects)
		{
			if (rect.area() > frame.size().area() / 4 ) continue;
			//draw each rectangle
			Mat temp = img(rect);
			vector<KeyPoint> kp = a.getKeypoints(temp, numKeypoints);

			if (kp.size() == numKeypoints)
			{
				Mat des = a.getDescriptors(img, kp);
				des = des.reshape(0, 1); //reshape to single row
				int res = m.machine->predict(des);
				if (res == 1)
				{
					//timmy code

					vector<Mat> mats = a.segmentLetters( grayInput(rect) );
					Mat testLetters;
					for (Mat mat : mats) {
						resize(mat, mat, Size(20, 30), 0, 0, INTER_NEAREST);
						Mat singleRow = mat.clone().reshape(0, 1);
						singleRow.convertTo(singleRow, CV_32FC1);
						testLetters.push_back(singleRow);
					}
					if (testLetters.rows == 0) continue;
					Mat testResult;
					ocr.machine->predict(testLetters, testResult);
					string plate = "";
					for (int k = 0; k < testResult.rows; k++) {
						float pre = testResult.at<float>(k, 0);
						int n = static_cast<int>(pre);
						if (n != -1) {
							plate += folderReal[n];
						}
					}

					if (plate.size() != 7) continue;

					//check for correct format
					bool formatCorrect = true;
					for (int i = 0; i < plate.size(); i++)
					{
						char c = plate.at(i);
						if (i < 2)
						{
							if (c < 'A' || c > 'Z')
							{
								formatCorrect = false;
								break;
							}
						}
						else
						{
							if (c < '0' || c > '9')
							{
								formatCorrect = false;
								break;
							}
						}
					}

					if (!formatCorrect) continue;
					
					cout << plate << endl;

					string allowed[] = {"AV48475", "AR96492"};
					bool found = false;
					for (string p : allowed)
					{
						found |= (p.compare(plate) == 0);
					}
					
					//only add to the log, if it wasn't the last
					if (log.size() <= 0)
					{
						log.push_back(plate);
					}
					else if (log.back().compare(plate) != 0)
					{
						log.push_back(plate);
					}

					rectangle(dest, rect.tl(), rect.br(), (found) ? Scalar(0, 255, 0) : Scalar(0, 0, 255));
					putText(dest, plate, rect.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));

				}
				else
				{
					rectangle(dest, rect.tl(), rect.br(), Scalar(0, 0, 255));
				}
			}
		}

		//putText(dest, log, Point(20, 20), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
		for (int i = 0; i < log.size(); i++)
		{
			string s = log.at((log.size() - 1) - i);
			putText(dest, s, Point(21, 21 + 15 * i), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
			putText(dest, s, Point(20, 20 + 15 * i), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
		}

		//videoOut << dest;
		imshow("video", dest);
		if (waitKey(1) == 27) break;
	}

	return 0;
}