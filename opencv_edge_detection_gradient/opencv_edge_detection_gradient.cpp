#include <iostream>
#include <cmath>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
const vector<vector<float>> SobelKernel{ { -1.0f, 0, 1.0f },{ -2.0f, 0, 2.0f },{-1.0f, 0, 1.0f}  } ;
const vector<vector<float>> PrewittKernel{ { -1.0f, 0, 1.0f },{ -2.0f, 0, 2.0f },{ -1.0f, 0, 1.0f } };
void calculateGradient(const Mat& input_img, vector<vector<float>>& gradX, vector<vector<float>>& gradY, Mat& gradient,const vector<vector<float>>& kernel)
{
	int halfSize = kernel.size() / 2;
	for (int i{ halfSize }; i < input_img.rows - halfSize; i++)
		for (int j{ halfSize }; j < input_img.cols - halfSize; j++)
		{
			gradX[i][j] = gradY[i][j] = 0;
			for (int x = { -halfSize }; x <= halfSize; x++)
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					gradX[i][j] += input_img.at<float>(i + x, j + y)*kernel[x + halfSize][y + halfSize];
					gradY[i][j] += input_img.at<float>(i + x, j + y)*kernel[y + halfSize][x + halfSize];
				}
			gradient.at<float>(i, j) = sqrt(pow(gradX[i][j], 2.0) + pow(gradY[i][j], 2.0));
		}
}
void calculateGradientVector(const Mat& input_img ,vector<vector<float>>& gradX, vector<vector<float>>& gradY, Mat& gradient)
{
	for (int i{}; i < input_img.rows - 1; i++)
		for (int j{}; j < input_img.cols - 1; j++)
		{
			gradX[i][j] = input_img.at<float>(i, j + 1) - input_img.at<float>(i, j);
			gradY[i][j] = input_img.at<float>(i + 1, j) - input_img.at<float>(i, j);
			gradient.at<float>(i, j) = sqrt(pow(gradX[i][j], 2.0) + pow(gradY[i][j], 2.0));
		}
}
void selectThreshold_outputImg(Mat& gradient, Mat& output_img)
{
	float threshold{};
	int mode{};
	cout << "\tNhap vao nguong: ";
	cin >> threshold;
	for (int i{}; i < gradient.rows - 1; i++)
		for (int j{}; j < gradient.cols - 1; j++)
		{
			output_img.at<uchar>(i, j) = gradient.at<float>(i, j) >= threshold ? 255 : 0;
		}
	namedWindow("Edge Detection", WINDOW_AUTOSIZE);
	imshow("Edge Detection", output_img);
}
void detectEdge(const Mat& input_img, vector<vector<float>>& gradX, vector<vector<float>>& gradY,Mat& gradient, Mat& output_img)
{
	int modeName{};
	//while (modeName != 5)
	//{
		cout << "HAY CHON CHE DO TINH GRADIENT" << endl;
		cout << "\t1. Tinh Gradient vector" << endl;
		cout << "\t2. Tinh Gradient theo Sobel Kernel" << endl;
		cout << "\t3. Tinh Gradient theo Prewitt Kernel" << endl;
		cout << "\t  -> ";
		cin >> modeName;
		switch (modeName)
		{
		case 1:
			calculateGradientVector(input_img, gradX, gradY, gradient);
			selectThreshold_outputImg(gradient, output_img);
			
			break;
		case 2:
			calculateGradient(input_img, gradX, gradY, gradient, SobelKernel);
			selectThreshold_outputImg(gradient, output_img);
			break;
		case 3:
			calculateGradient(input_img, gradX, gradY, gradient, PrewittKernel);
			selectThreshold_outputImg(gradient, output_img);
			break;

		default: break;
		}
	//}

}
int main(int argc, char* argv[])
{
	Mat input_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Couldn't open image................." << endl;
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------------
	Mat input_img_f;
	input_img.convertTo(input_img_f, CV_32F);
	vector<vector<float>> gradientX(input_img.rows, vector<float>(input_img.cols, 0));
	vector<vector<float>> gradientY(input_img.rows, vector<float>(input_img.cols, 0));
	Mat gradientValue(input_img.rows, input_img.cols, CV_32F);

	Mat output_img(input_img.clone());
	detectEdge(input_img_f, gradientX, gradientY, gradientValue, output_img);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	waitKey();
	return 0;
}
