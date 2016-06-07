#include "ANPR.h"

ANPR::ANPR()
{
	ANPR::fd = SURF::create(100, 4, 3, false);
}

vector<KeyPoint> ANPR::getKeypoints(Mat img, int max)
{
	vector<KeyPoint> output;

	//run our detector on the given image
	this->fd->detect(img, output);

	//may have gotton more then we asked for, so keep the best
	KeyPointsFilter::retainBest(output, max);

	return output;
}

Mat ANPR::getDescriptors(Mat img, vector<KeyPoint> keypoints)
{
	Mat output;
	this->fd->compute(img, keypoints, output);
	return output;
}

//segments an image into individual images
vector<Rect> ANPR::segment(Mat input)
{
	Mat img;
	input.copyTo(img);

	int biAmount = 21;
	//	bilateralFilter(input, img, biAmount, biAmount * 2, biAmount / 2);

	cvtColor(img, img, CV_BGR2GRAY); //convert to grayscale
	//TODO: maybe do some filtering

	//equalize histogram for potential greater contrasts
	equalizeHist(img, img);

	double mean = *cv::mean(img).val;
	double sigma = 0.33;
	double lower = std::fmax(0, (1.0 - sigma) * mean);
	double upper = std::fmin(255, (1.0 + sigma) * mean);

	//threshold(img, img, 0, 255, THRESH_BINARY + THRESH_OTSU); //threshold the image
	Canny(img, img, lower, upper);

	//Mat elm = getStructuringElement(MORPH_RECT, Size(17, 6)); //wide kernel
	//morphologyEx(img, img, MORPH_CLOSE, elm); //morphological closure

	//find contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	const double error = 0.4;
	const double aspect = 504.0 / 120.0;

	const double min = 15 * 15 * aspect;
	const double max = 1250 * 1250 * aspect;

	const double rmin = aspect - aspect * error;
	const double rmax = aspect + aspect * error;

	const double areaMin = 3000 / ((1920 * 1080) / input.size().area());
	const double areaMax = 30000 / ((1920 * 1080) / input.size().area());

	vector<Rect> out;
	for (int i = 0; i< contours.size(); i++)
	{
		
		if (contours[i].size() >= 20)
		{
			Rect rect = boundingRect(Mat(contours[i]));

			int area = rect.area();
			double r = (double)rect.size().width / (double)rect.size().height;

			if (r > rmin && r < rmax/* && area > areaMin && area < areaMax*/)
			{
				out.push_back(rect);
			}

		}
	}

	return out;
}

void ANPR::processImages()
{
	/*// for some effin reason does c++ complain of linker errors when this is enabled
	for (int i = 0; i < baseImagesAmount; i++)
	{
		Mat img = imread(baseImagesPath[i]);
		vector<Rect> rects = this->segment(img);

		int c = 0;
		for (Rect rect : rects)
		{
			vector<KeyPoint> kp = this->getKeypoints(img(rect), 12);
			if (kp.size() == 12)
				imwrite("..\\images\\segments\\" + baseImagesName[i] + "_" + std::to_string(c++) + ".jpg", img(rect));
		}
	}*/
}

//http://answers.opencv.org/question/20012/sort-bounding-boxes-in-x-axis-of-a-image-in-order/
bool compare_rect(const Rect &a, const Rect &b) {
	return a.x < b.x;
}

vector<Mat> ANPR::segmentLetters(Mat input) {
	//del
	//int fileName = 0;

	Mat img;
	input.copyTo(img);

	//del
	//imwrite("report\\" + to_string(fileName) + " input.png", img);
	//fileName++;
	//imshow("a", img);

	/* improve lighting */
	//Enter the alpha value [1.0-3.0]
	//Enter the beta value [0-100]
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			img.at<uchar>(y, x) = saturate_cast<uchar>(1.5*(img.at<uchar>(y, x)) + 30);
			input.at<uchar>(y, x) = saturate_cast<uchar>(1.5*(input.at<uchar>(y, x)) + 30);
		}
	}

	//del
	//imwrite("report\\" + to_string(fileName) + " saturate.png", img);
	//fileName++;
	//imshow("aa", img);

	//adaptiveThreshold(input, input, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 17, 0);
	//medianBlur(input, input, 3);

	threshold(img, img, 0, 255, THRESH_BINARY + THRESH_OTSU);
	threshold(input, input, 0, 255, THRESH_BINARY + THRESH_OTSU);

	//del
	//imwrite("report\\" + to_string(fileName) + " threshold.png", input);
	//fileName++;
	//imshow("aaa", img);

	double mean = *cv::mean(img).val;
	double sigma = 0.33;
	double lower = std::fmax(0, (1.0 - sigma) * mean);
	double upper = std::fmin(255, (1.0 + sigma) * mean);
	Canny(img, img, lower, upper);

	//del
	//imwrite("report\\" + to_string(fileName) + " canny.png", img);
	//fileName++;
	//imshow("aaaaa", img);

	//find contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<Rect> out;
	vector<Mat> outMat;
	for (int i = 0; i< contours.size(); i++) {
		if (contours[i].size() >= 1) {
			Rect rect = boundingRect(Mat(contours[i]));
			//cout << rect.area() << endl;
			if (rect.area() > 150 && rect.area() < 800) {
				//rectangle(input, rect.tl(), rect.br(), Scalar(0, 255, 0));
				//imshow("fag", input);
				out.push_back(rect);
			}
		}
	}

	//del
	//imwrite("report\\" + to_string(fileName) + " contours.png", img);
	//fileName++;
	//imwrite("report\\" + to_string(fileName) + " boundingRectOnInput.png", input);
	//fileName++;
	//waitKey(0);

	sort(out.begin(), out.end(), compare_rect);
	for (Rect rect : out) {
		Mat contourRegion = input(rect);
		outMat.push_back(contourRegion);
	}

	return outMat;
}


ANPR::~ANPR()
{
}
