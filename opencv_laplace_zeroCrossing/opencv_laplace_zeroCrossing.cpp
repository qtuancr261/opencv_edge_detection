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
	Mat Laplace_Mat_f, Laplace_Mat;
	double laplaceMinValue{}, laplaceMaxValue{};
	Laplacian(input_img, Laplace_Mat_f, CV_32F, 3);
	//minMaxLoc(Laplace_Mat_f, &laplaceMinValue, &laplaceMaxValue);
	Laplace_Mat_f.convertTo(Laplace_Mat, CV_8U);
	//namedWindow("Laplacian", WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	imshow("Laplacian", Laplace_Mat);
	waitKey();
	return 0;
}
