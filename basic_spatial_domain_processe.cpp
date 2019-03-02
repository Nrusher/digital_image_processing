#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>  

using namespace cv;
using namespace std;

int main(void)
{
	Mat src = Mat::ones(Size(5,5),CV_32FC1);

	Mat filter_result = Mat::zeros(Size(5, 5), CV_32FC1);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			src.at<float>(i,j) = i * 5 + j;
		}
	}

	Mat kernel = (Mat_<float>(3, 3) << 0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5);

	filter2D(src, filter_result,-1,kernel,Point(1,1), 0,BORDER_CONSTANT);

	cout << "src:" << endl;
	cout << src << endl;

	cout << "kernel:" << endl;
	cout << kernel << endl;

	cout << "filter result:" << endl;
	cout << filter_result << endl;

	waitKey();
}
