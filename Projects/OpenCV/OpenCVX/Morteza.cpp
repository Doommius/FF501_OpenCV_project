//#include <iostream>
//#include <fstream>
//#include <string>
//#include <thread>
//#include <functional>
//#include <mutex>
//#include <atomic>
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>
//#include <opencv2/ml.hpp>
//
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//using namespace cv::ml;
//
//
////Enter the alpha value [1.0-3.0]
////Enter the beta value [0-100]
//void myContrastBrightness(Mat&, double, int);
//int getDescriptors();
//void createTraining(int s);
//void machine(int s);
//
///* where the contours are located */
////string dir1 = "imagesM\\1 (";
//string dir1 = "images\\";
//int minHessian = 700;
//ofstream myfile;
//
//int num_features = 15;
///*train*/
//const int numOfContours = 12;	//number of files
//int img_area = 64 * num_features;
//
//int testStart = 41;
//int testStop = 81/*numOfContours*/;
//int numOfContoursTest = testStop-testStart;
////Mat test_mat(numOfContoursTest, img_area, CV_32FC1);	//Don't know how many countours are extracted
//
//vector<vector<float>> vect_totalStuff;
/////*testMikkel*/		//{ 12, 38, 39, 60, 61, 77, 78, 98, 99, 120, 122, 155, 175, 176, 208, 247, 278, 279 }
/////*testMorteza*/		//{ 7, 13, 31, 42, 51, 62, 79, 92, 111, 157 }
/////*testMM*/		//{ 4, 14, 24, 48, 59, 69, 87, 99, 127, 152, 167, 169, 182, 189, 220, 238, 249, 272, 282, 296, 349, 357, 367, 372, 394, 416, 424, 434, 446, 454, 475, 485, 502, 529, 543, 564, 581, 597, 619, 634, 647, 665, 691, 706, 712, 721, 747, 762, 768, 784, 796, 807, 830, 860, 876, 899, 918, 936, 988, 1011, 1018, 1038, 1049, 1061, 1143, 1144, 1155, 1168, 1182, 1196, 1201, 1211, 1229, 1238, 1255 }
/////*copy188*/			//{8, 19, 38, 50, 71, 90, 104, 120, 166, 183}
//
//int main(){
//	myfile.open("train.txt");
//	int s = getDescriptors();
//	myfile << s << endl;
//	createTraining(s);
//	machine(s);
//	myfile.close();
//	return 0;                                         
//}
//
///* Pictures are written to imagesMM */
//int getDescriptors() {
//	int totalSize = 0;
//	ofstream w;
//	w.open(string("descriptors")+ string(".txt"));
//	//STEP 1: loading image
//	for (int iii = 1; iii <= numOfContours; iii++) {
//		cout << iii << endl;
//		//Mat org_img = imread("C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\2\\1 (" + to_string(iii) + ").jpg", IMREAD_COLOR);
//		Mat org_img = imread("C:\\Users\\zlyza\\Desktop\\Biggest Project\\images\\" + to_string(iii) + ".jpg", IMREAD_COLOR);
//		if (org_img.empty()) {                              
//			cout << "Could not open or find the image" << endl;
//			//return -1;
//		}
//
//		//STEP 2: fltering/smoothing image to reduce noise
//		Mat img;
//		//bilateralFilter(org_img, img, 21, 21 * 2, 21 / 2);                 //setting diameter, sigma color and sigma space to their recommended values
//
//		//STEP 3: converting BGR to gray scale
//		cvtColor(org_img, img, CV_BGR2GRAY, 1);
//
//		//STEP 4: converting gray image to binary (black & white) one
//		threshold(img, img, 128, 255, THRESH_BINARY);
//
//		//STEP 5: transforming iamge to remove holes
//		Mat elm = getStructuringElement(MORPH_RECT, Size(4, 4));         //setting kernel size to these values is by trial and error
//		morphologyEx(img, img, MORPH_CLOSE, elm);                      //tends to remove black holes;
//																	   //this is because digits in number plate are black and we are looking for plate
//		//STEP 6: finding contours
//		vector<vector<Point>> contours;
//		vector<Vec4i> hierarchy;
//		findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//		//STEP 7: draw contours
//		Mat contour_img = org_img.clone();
//		drawContours(contour_img, contours, -1, Scalar(0, 0, 255), 2);
//
//		//STEP 8: fiting a rectangle around a contour
//		vector<Rect> boundRects;
//		for (short i = 0; i < contours.size(); i++) {
//			if (contours[i].size() >= 20) {                                      //setting this cutoff for contour area is by trial and error. You could also set an upper bound like <= 50!
//				boundRects.push_back(boundingRect(Mat(contours[i])));
//			}
//		}
//
//		short i = 0;
//		//STEP 9: drawing rectangles around contours
//		i = 0;
//		for (Rect rect : boundRects) {
//			Mat rect_img = org_img.clone();
//			rectangle(rect_img, rect.tl(), rect.br(), Scalar(255, 0, 0), 2);
//			imwrite(string("imagesMM\\object") + to_string(iii) + "_" + to_string(i) + string(".png"), org_img(rect));
//			i++;
//		}
//
//		//STEP 10: increasing contrast and brightness of image is a goodidea for finding key points at least in number plate area!
//		myContrastBrightness(org_img, 2, 0);
//
//		//STEP 11: finding keypoints
//		Ptr<SURF> detector = SURF::create(400, 4, 3, false, false);           //setting Hessian threshold to 300-500 is recommended, 64-bit descriptor is requested!
//		vector<vector<KeyPoint>> vect_keypoints(boundRects.size());
//		i = 0;
//		for (Rect& rect : boundRects) {
//			detector->detect(org_img(rect), vect_keypoints[i]);
//			i++;
//		}
//
//		//STEP 12: for each rectangle image: filtering out bad key points keeping only 15 good key points
//		for (short i = 0; i < vect_keypoints.size();) {
//			if (vect_keypoints[i].size() >= num_features) {                               //this cutoff value is by error and trial
//				vect_keypoints[i].erase(vect_keypoints[i].begin() + num_features, vect_keypoints[i].end());
//				i++;
//			}
//			//del
//			else {
//				vect_keypoints.erase(vect_keypoints.begin() + i);
//				boundRects.erase(boundRects.begin() + i);
//			}
//		}
//
//		//STEP 13: Draw keypoints
//		vector<Mat> keypoint_imgs(vect_keypoints.size());
//		for (short i = 0; i < vect_keypoints.size(); i++) {
//			drawKeypoints(org_img(boundRects[i]), vect_keypoints[i], keypoint_imgs[i], Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);
//		}
//
//		//STEP 14: finding keypoint descriptors
//		vector<Mat> vect_descriptors;
//		detector->compute(keypoint_imgs, vect_keypoints, vect_descriptors);
//
//		//STEP 15: for each rectangle image: writing key point descriptors into a Mat //file
//		
//		w << "\nContours found: " << vect_descriptors.size() << endl;
//		
//		for (Mat& descs : vect_descriptors){
//			vector<float> vect_stuff;
//			//w << endl;
//			//w << descs.rows
//			//w << "row = " << descs.rows << ", col = " << descs.cols << endl;
//			for (int row = 0; row < descs.rows; row++) {	//col = 64, row = 15
//				for (int col = 0; col < descs.cols; col++){
//					//cout << "row = " << row << ", col = " << col << endl;
//					//w << descs.at<float>(row, col) << " ";
//					vect_stuff.push_back(descs.at<float>(row, col));
//				}
//				//w << endl;
//			}
//			vect_totalStuff.push_back(vect_stuff);
//			//w << endl;
//		}
//
//		/*short k = 0;
//		for (Mat& descs : vect_descriptors) {
//			k++;
//			short ii = 0;
//			for (int u = 0; u<descs.rows; u++) {
//				for (int j = 0; j < descs.cols; j++) {
//					training_mat.at<float>(k, ii++) = descs.at<float>(u, j);
//				}
//			}
//		}
//		myfile << training_mat << "\n";*/
//		
//		w << vect_totalStuff.size() << endl;
//
//		//del
//		//totalSize += vect_totalStuff.size();
//		//totalSize += boundRects.size();
//	}
//	w.close();
//	return totalSize;
//}
//
//vector<int> labels;
//void createTraining(int s) {
//	cout << s << endl;
//	//int labels[s];
//	int posPlate[] = {8, 19, 38, 50, 71, 90, 104, 120, 166, 183};
//
//	for (int i = 1; i <= s; i++) {
//		if (find(begin(posPlate), end(posPlate), i) != end(posPlate)) {
//			//labels[i] = 1;
//			labels.push_back(1);
//		}
//		else {
//			//labels[i] = 0;
//			labels.push_back(0);
//		}
//	}
//}
//
//void machine(int s) {	//http://docs.opencv.org/3.0-rc1/d1/d73/tutorial_introduction_to_svm.html
//	Mat training_mat(s, img_area, CV_32FC1);
//	int j = 0;
//	int u = 0;
//	for (vector<float> total : vect_totalStuff) {
//		for (float tot : total) {
//			training_mat.at<float>(u, j) = tot;
//			j++;
//		}
//		u++;
//	}
//
//	/*for (int u = 0; u<descs.rows; u++) {
//		for (int j = 0; j < descs.cols; j++) {
//			training_mat.at<float>(k, ii++) = descs.at<float>(u, j);
//		}
//	}*/
//
//	Mat labelsMat(s, 1, CV_32SC1);
//	for (int i = 0; i<s; ++i){
//		labelsMat.at<int>(i) = labels.at(i);
//	}
//	//myfile << labelsMat << endl;
//	myfile << training_mat << endl;
//
//	Ptr<SVM> svm = SVM::create();
//	//Ptr<SVM> svm = StatModel::load<SVM>("mySVM.xml");
//
//	svm->setType(SVM::C_SVC);
//	svm->setKernel(SVM::LINEAR);
//	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	svm->train(training_mat, ROW_SAMPLE, labelsMat);
//
//	myfile << "train?: " << svm->isTrained() << "\n";
//	//myfile << "labelsMat = " << labelsMat << endl;
//	//myfile << "labelsMat row: " << labelsMat.rows << "\n";
//	//myfile << "labelsMat col: " << labelsMat.cols << "\n";
//	//myfile << training_mat << "\n";
//	//myfile << "row: " << training_mat.rows << "\n";
//	//myfile << "col: " << training_mat.cols << " => 64*numOfFeaturePoints\n";
//	//svm->save("mySVM.xml");
//
//	/*try to predict*/
//	//testCreateMem(testStart, testStop);
//	//Mat results;
//	//svm->predict(test_mat, results);
//	//double correct = 0;
//	//if (results.rows == labelsMat.rows && results.cols == labelsMat.cols) {
//	//	for (int u = 0; u < labelsMat.rows; u++) {
//	//		for (int j = 0; j < labelsMat.cols; j++) {
//	//			if (results.at<float>(u, j) == labelsMat.at<int>(u, j)) {
//	//				if (labelsMat.at<int>(u, j) == 1) {
//	//					myfile << results.at<float>(u, j) << " " << labelsMat.at<int>(u, j) << " oh baby! \n";
//	//				}
//	//				correct++;
//	//			}
//	//			else {
//	//				myfile << results.at<float>(u, j) << " " << labelsMat.at<int>(u, j) << "\n";
//	//			}
//	//		}
//	//	}
//	//	myfile << correct << " out of " << numOfContoursTest << "\n";
//	//	myfile << "The training machine got " << (correct / numOfContoursTest) * 100 << "% correct \n";
//	//}
//	//else {
//	//	myfile << "labelsMat and results don't match" << "\n";
//	//}
//	//myfile << "results row: " << results.rows << "\n";
//	////myfile << "results col: " << results.cols << "\n";
//	////myfile << labelsMat << results << "\n";
//}
//
////Enter the alpha value [1.0-3.0]
////Enter the beta value [0-100]
////read more on http://goo.gl/8sjB3d
//void myContrastBrightness(Mat& image, double alpha, int beta)
//{
//	for (int y = 0; y < image.rows; y++)
//		for (int x = 0; x < image.cols; x++)
//			for (int c = 0; c < 3; c++)
//				image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//}