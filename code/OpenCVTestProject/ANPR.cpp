#include "ANPR.h"

ANPR::ANPR()
{
	ANPR::fd = SURF::create(400);
	
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

	int biAmount = 0;
	//bilateralFilter(input, img, biAmount, biAmount * 2, biAmount / 2);

	cvtColor(img, img, CV_BGR2GRAY); //convert to grayscale
	//TODO: maybe do some filtering

	//equalize histogram for potential greater contrasts
	equalizeHist(img, img);

	double mean = *cv::mean(img).val;
	double sigma = 0.33;
	double lower = std::fmax(0, (1.0 - sigma) * mean);
	double upper = std::fmin(255, (1.0 + sigma) * mean);

	threshold(img, img, 0, 255, THRESH_BINARY + THRESH_OTSU); //threshold the image
	//Canny(img, img, lower, upper);

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

	const double areaMin = 5000 / ((1920 * 1080) / input.size().area());
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

ANPR::~ANPR()
{
}
