//inclusion of opencv library

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include<vector>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    //declaration of image matrix
	Mat img;

	//read input image
	img = imread("oscarSelfie.jpg");

	//displaying image
	imshow("wooohooo1", img);
    
	// Load cascade classifier placed in solution folder

	CascadeClassifier detector;
	CascadeClassifier detector1;

	string cascadeName = "haarcascade_frontalface_alt.xml";
	string cascadeEye = "haarcascade_eye.xml";

	bool loaded = detector.load(cascadeName);
	bool loaded1 = detector1.load(cascadeEye);

	// Parameters of detectMultiscale Cascade Classifier

	int groundThreshold = 2;
	double scaleStep = 1.1;

	//paameters of the following functions have selected by trial and error method

	Size minimalObjectSize(80, 80);
	Size maximalObjectSize(400, 400);
	Size minimalObjectSize1(5, 5);
	Size maximalObjectSize1(40, 40);

	// Vector of returned faces
	vector<Rect_<int> > found;
	vector<Rect_<int> > found1;

	//found is for faces and found1 is for eyes

	// Convert input to greyscale 
	Mat image_grey;

	cvtColor(img, image_grey, CV_BGR2GRAY);

	found.clear();
	found1.clear();

	// Detect faces

	detector.detectMultiScale(image_grey, found, scaleStep, groundThreshold, 0 | 2, minimalObjectSize, maximalObjectSize);
	
	Mat gate = image_grey(cvRect(found[2].x ,found[2].y,found[2].height,found[2].width));
	
	detector1.detectMultiScale(gate, found1, scaleStep, groundThreshold, 0 | 2, minimalObjectSize1, maximalObjectSize1);
	
	//faces are detected and rectangles are drawn

	if (found.size() > 0) {
		for (int i = 0; i <= found.size() - 1; i++) {
			rectangle(img, found[i].br(), found[i].tl(), Scalar(0, 255, 0), 1, 8, 0);
			}
	}

	//by trial and error method it is found that found[2] encloses the face of ellen hence for detection of ellen's eyes found[2] is used;
	
	if (found1.size() > 0) {
		for (int i = 0; i < 2; i=i+1) {
			rectangle(img, Point(found[2].x +found1[i].x, found[2].y +found1[i].y), Point(found[2].x + found1[i].x+ found1[i].width, found[2].y + found1[i].y+ found1[i].height), Scalar(255, 0, 0), 2, 8, 0);
			
			Vec3b bgrPixel = img.at<Vec3b>(found[2].x + found1[i].x + found1[i].width / 2, found[2].y + found1[i].y + found1[i].height / 2);
			
			//the bgr values of the centroid of both the eyes are printed
			cout << "BGR Values:" << bgrPixel<<endl;

			//at the centroid of her eyes 'x' marks is printed
			putText(img, "X", cvPoint(found[2].x + found1[i].x + found1[i].width / 3, found[2].y + found1[i].y + found1[i].height /1.5),
				FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 250), 1, CV_AA);
		}
	}

	//Show the results
    imshow("wooohooo", img);

	waitKey(0);
	return 0;
}