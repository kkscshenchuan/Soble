// Soble.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "math.h"
#include "opencv.hpp"

using namespace std;
using namespace cv;

const double π = 3.14;
int main()
{
	Mat Image, grayImage,SobleImage;   //SobleImage表示结果图
	Image = imread("Lena.png");
	namedWindow("原图",1);
	imshow("原图", Image);

    cvtColor(Image, grayImage, COLOR_RGB2GRAY);
	SobleImage = grayImage.clone();

	int width = Image.cols-2; //图片的宽
	int height = Image.rows-2;//图片的宽

	//创建动态二维数组，并将数组中所有的值赋值为0,用来存储每个点的梯度信息
	vector<vector<double>> Gradient(height, vector<double>(width,0));

	double Gx = 0;   //横向梯度值
	double Gy = 0;   //纵向梯度值
	int px = 0;
	int py = 0;
	int pixel = 0;

	for (int i = 1; i < height; i++)
	{
		uchar *p = grayImage.ptr<uchar>(i-1);  //获取第i-1行的指针
		uchar *q = grayImage.ptr<uchar>(i);
		uchar *r = grayImage.ptr<uchar>(i+1);

		uchar *m = SobleImage.ptr<uchar>(i); //获取结果图第i行指针
		for (int j = 1; j < width; j++)  
		{
			Gx = (p[j - 1] + 2 * q[j - 1] + r[j - 1]) - (p[j + 1] + 2 * q[j + 1] + r[j + 1]);//计算横向梯度值
			Gy = (p[j - 1] + 2 * p[j] + p[j + 1]) - (r[j - 1] + 2 * r[j] + r[j + 1]);     //计算纵向梯度值

			px = abs(Gx)*abs(Gx);
			py = abs(Gy)*abs(Gy);
			pixel = sqrt(px + py);   //计算
			m[j] = pixel;
			if (Gx == 0)
			{
				//Gradient[i][j] = π/2;
				Gradient[i][j] = 0;
			}
			else
			{
				if (Gy == 0)
				{
					Gradient[i][j] = 0;
				}
				else
				{
					Gradient[i][j] = atan(Gy / Gx);
				}
			}
			//cout << Gradient[i][j];   //显示每个点的梯度值
		}
	}
	namedWindow("sobel算子结果图",1);
	imshow("sobel算子结果图", SobleImage);
	waitKey(0);
    return 0;
}

