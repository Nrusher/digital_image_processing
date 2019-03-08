#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>  

using namespace cv;
using namespace std;

void tic(double &t)
{
	t = (double)getTickCount();
}

double toc(double &t)
{
	return ((double)getTickCount() - t) / getTickFrequency();
}
unsigned char transform_table[3][255];

unsigned char float_u8_limit(float s)
{
	if (s > 255)
	{
		return 255;
	}
	else if (s < 0)
	{
		return 0;
	}
	else
	{
		return (unsigned char)round(s);
	}
}

void negative_transform(Mat& src,Mat& dst)
{	
	static bool flag = false;
	static Mat look_up_table(1, 256, CV_8U);
	uchar* p = look_up_table.ptr();

	if (flag == false)
	{
		for (int i = 0; i < 256; i++)
		{
			p[i] = 255 - i;
		}
		flag = true;
	}

	LUT(src, look_up_table, dst);

}

void log_transform(Mat& src, Mat& dst, float c, float n)
{
	static float c_s;
	static float n_s;
	static Mat look_up_table(1, 256, CV_8U);
	uchar* p = look_up_table.ptr();
	float s;

	if ((fabs(c_s - c) > 0.0001) || (fabs(n_s - n) > 0.0001))
	{
		for (int i = 0; i < 256; i++)
		{
			s = c * log(i) / log(n);
			p[i] = float_u8_limit(s);
		}

		c_s = c;
		n_s = n;
	}

	LUT(src, look_up_table, dst);

}

void gamma_transform(Mat& src, Mat& dst,float c, float gama)
{
	static float c_s;
	static float gama_s;
	static Mat look_up_table(1, 256, CV_8U);
	uchar* p = look_up_table.ptr();
	float s;

	if ((fabs(c_s - c) > 0.0001) || (fabs(gama_s - gama) > 0.0001))
	{
		for (int i = 0; i < 256; i++)
		{
			s = c * pow(i,gama);
			p[i] = float_u8_limit(s);
		}
	}

	LUT(src, look_up_table, dst);

}

int main(void)
{
	Mat src = Mat::ones(Size(5,5),CV_8UC1);

	Mat result = Mat::zeros(Size(5, 5), CV_8UC1);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			src.at<unsigned char>(i,j) = i * 5 + j;
		}
	}

	cout << "src:" << endl;
	cout << src << endl;

	negative_transform(src, result);
	cout << "negative_transform:" << endl;
	cout << result << endl;

	log_transform(src, result,1,1.2);
	cout << "log_transform:" << endl;
	cout << result << endl;

	gamma_transform(src, result, 1, 1.1);
	cout << "gamma_transform:" << endl;
	cout << result << endl;

	double t;

	src = imread("intensity-Transformation-1.tif", IMREAD_GRAYSCALE).clone();
	result = src.clone();
	imshow("src", src);
	negative_transform(src, result);
	imshow("negative_transform", result);
	log_transform(src, result, 1, 1.2);
	imshow("log_transform", result);
	gamma_transform(src, result, 1, 1.1);
	imshow("gamma_transform", result);

	waitKey();
}


