#include <iostream>
#include <cmath>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
void calculateGradient(vector<vector<float>>& gradX, vector<vector<float>>& gradY, Mat& gradient, const Mat& input_img)
{
	for (int i{}; i < input_img.rows - 1; i++)
		for (int j{}; j < input_img.cols - 1; j++)
		{
			gradX[i][j] = input_img.at<float>(i, j + 1) - input_img.at<float>(i, j);
			gradY[i][j] = input_img.at<float>(i + 1, j) - input_img.at<float>(i, j);
			gradient.at<float>(i, j) = sqrt(pow(gradX[i][j], 2.0) + pow(gradY[i][j], 2.0));
		}
}
void dectectEdge(Mat& gradient, Mat& output)
{
	float threshold{ 10.0f };
	cout << "Nhap vao nguong: ";
	cin >> threshold;
	for (int i{}; i < gradient.rows - 1; i++)
		for (int j{}; j < gradient.cols - 1; j++)
		{
			if (gradient.at<float>(i, j) >= threshold)
				output.at<uchar>(i, j) = 255;
			else output.at<uchar>(i, j) = 0;
		}

}
/*Mat convertTo_CV_8U(Mat& input_img)
{
	double minValue{}, maxValue{};
	Point2i minLoc, maxLoc;
	minMaxLoc(input_img, &minValue, &maxValue, &minLoc, &maxLoc);
	Mat output;
	input_img.convertTo(output, CV_8U, 256.0 / (maxValue - minValue + 1), -minValue / (256.0 / (maxValue - minValue + 1)));
	for (int i{}; i < input_img.rows - 1; i++)
		for (int j{}; j < input_img.cols - 1; j++)
		{
			cout << output.at<uchar>(i, j) << " ";
		}
	return output;
}*/
int main(int argc, char* argv[])
{
	Mat input_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Couldn't open image................." << endl;
		return 1;
	}
	Mat input_img_f;
	input_img.convertTo(input_img_f, CV_32F);
	vector<vector<float>> gradientX(input_img.rows, vector<float>(input_img.cols, 0));
	vector<vector<float>> gradientY(input_img.rows, vector<float>(input_img.cols, 0));
	Mat gradientValue(input_img.rows, input_img.cols, CV_32F);
	calculateGradient(gradientX, gradientY, gradientValue, input_img_f);

	Mat output_img(input_img.clone());
	dectectEdge(gradientValue, output_img);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("Edge Detection", WINDOW_AUTOSIZE);
	imshow("Edge Detection", output_img);
	//namedWindow("Gradient Dectection", WINDOW_AUTOSIZE);
	//imshow("Gradient Dectection", convertTo_CV_8U(gradientValue));
	waitKey();
	return 0;
}