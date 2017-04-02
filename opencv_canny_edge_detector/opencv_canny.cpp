#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	Mat input_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Counldn't open image......." << endl;
		return 1;
	}
	//-------------------------------------------------------
	Mat Canny_output;
	int lowerThreshold{ 80 }, upperThreshold{ 180 }, kernelSize{ 3 };
	Canny(input_img, Canny_output, lowerThreshold, upperThreshold, kernelSize);
	imshow(argv[1], input_img);
	imshow("Canny", Canny_output);
	waitKey();
	return 0;
}