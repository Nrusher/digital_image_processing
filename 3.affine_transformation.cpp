#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>  

using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("sudu.jpg", IMREAD_GRAYSCALE);
	pyrDown(src, src);
	cout << src.size() << endl;
	imshow("src",src);


	Mat transformation_pic = Mat::zeros(src.size(), CV_8UC1);
	Mat transformation_table = (Mat_<double>(2, 3) << 0.6, 0.1, 100, 0.1, 0.6, 100);
	warpAffine(src, transformation_pic, transformation_table, transformation_pic.size(),1,0,Scalar(255));
	imshow("transformation_pic", transformation_pic);

	Mat bin = Mat::zeros(src.size(), CV_8UC1);
	threshold(transformation_pic, bin, 250, 255, THRESH_BINARY);
	bitwise_not(bin, bin);
	imshow("bin", bin);

	Mat ans = Mat::zeros(src.size(), CV_8UC1);
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<vector<Point>> approxes;
	findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	approxes = contours;
	approxPolyDP(contours[0], approxes[0], arcLength(contours[0], true)*0.02,true);

	Point2f real_pos[3];
	Point2f dst_pos[3] = { Point2f(0,0),Point2f(0,300),Point2f(300,300)};

	for (int i = 0; i < 3; i++)
	{
		real_pos[i] = approxes[0][i];
	}

	Mat ans_table = getAffineTransform(real_pos, dst_pos).clone();

	warpAffine(transformation_pic, ans, ans_table, transformation_pic.size(), INTER_CUBIC, 0, Scalar(255));
	imshow("ans", ans);
	waitKey();
}
